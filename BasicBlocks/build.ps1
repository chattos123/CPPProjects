<#
.SYNOPSIS
    Automated cross-platform build, configuration, and packaging script for C++ projects.

.DESCRIPTION
    Configures, compiles, and installs CMake targets across GCC/Clang (Ninja or Unix Makefiles)
    and MSVC (Visual Studio 2022 on Windows) in Debug and/or Release configurations.
    Staging paths:
      - Windows: dist/gcc/bin and dist/msvc/bin
      - Linux:   dist/gcc/bin

.PARAMETER Config
    Specifies the build configuration: 'Debug', 'Release', or 'All'. Default is 'All'.

.PARAMETER Toolchain
    Specifies the compiler/generator toolchain: 'Ninja', 'MSVC', 'GCC', 'Both', or 'Auto'. Default is 'Both'.

.PARAMETER CleanOnly
    Cleans all build output directories ('build-*' and 'dist') and exits without building.

.PARAMETER ConfigureOnly
    Runs cmake configure step only (no build/install).

.PARAMETER Help
    Displays help and usage documentation.
#>

param(
    [ValidateSet("Debug", "Release", "All")]
    [string]$Config = "All",

    [ValidateSet("Ninja", "MSVC", "GCC", "Both", "Auto")]
    [string]$Toolchain = "Both",

    [switch]$CleanOnly,
    [switch]$ConfigureOnly,

    [Alias("h")]
    [switch]$Help
)

# -------------------------------------------------------------------
# 1. Handle Help Flag (-h or -Help)
# -------------------------------------------------------------------
if ($Help) {
    Get-Help $MyInvocation.MyCommand.Path -Full
    exit 0
}

# -------------------------------------------------------------------
# 2. Host OS Detection
# -------------------------------------------------------------------
$isLinuxHost = $IsLinux -or ($PSVersionTable.Platform -eq "Unix")

# -------------------------------------------------------------------
# 3. Standalone Clean Routine
# -------------------------------------------------------------------
$foldersToClean = @("build-debug", "build-release", "build-msvc-debug", "build-msvc-release", "dist")

function Perform-Clean {
    Write-Host "=== Cleaning build directories ===" -ForegroundColor Cyan
    foreach ($folder in $script:foldersToClean) {
        if (Test-Path $folder) {
            Write-Host "Removing: $folder" -ForegroundColor Gray
            Remove-Item -Recurse -Force $folder -ErrorAction SilentlyContinue
        }
    }
    if (Test-Path "build.log") {
        Remove-Item -Force "build.log" -ErrorAction SilentlyContinue
    }
}

if ($CleanOnly) {
    Perform-Clean
    Write-Host "=== Clean complete! No build performed. ===" -ForegroundColor Green
    exit 0
}

# -------------------------------------------------------------------
# 4. Standard Build Execution Setup
# -------------------------------------------------------------------
$ErrorActionPreference = "Stop"

# Auto-clean before starting a fresh build
Perform-Clean

# Version stamping
$version = Get-Date -Format "yyyy.MM.dd.HHmm"
Write-Host "`n=== Using version stamp: $version ===" -ForegroundColor Cyan

# -------------------------------------------------------------------
# Helper: Generator Args Builder
# -------------------------------------------------------------------
function Get-CMakeGeneratorArgs($buildType, $targetToolchain) {
    # Check if Ninja is available on system PATH
    $hasNinja = [bool](Get-Command ninja -ErrorAction SilentlyContinue)

    switch ($targetToolchain) {
        "Ninja" {
            if (-not $hasNinja) {
                Write-Warning "Ninja executable not detected in PATH. Falling back to default generator."
                return ""
            }
            return "-G Ninja"
        }
        "MSVC" {
            if ($script:isLinuxHost) {
                throw "MSVC generator is unavailable on Linux."
            }
            return '-G "Visual Studio 17 2022" -A x64'
        }
        "GCC" {
            $gen = if ($hasNinja) { "-G Ninja" } else { '-G "Unix Makefiles"' }

            if ($script:isLinuxHost) {
                return "$gen -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++"
            } else {
                $gccPath = "C:/msys64N/ucrt64/bin/gcc.exe"
                $gxxPath = "C:/msys64N/ucrt64/bin/g++.exe"
                if ((Test-Path $gccPath) -and (Test-Path $gxxPath)) {
                    return "$gen -DCMAKE_C_COMPILER=`"$gccPath`" -DCMAKE_CXX_COMPILER=`"$gxxPath`""
                } else {
                    return "$gen -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++"
                }
            }
        }
        "Auto" {
            return ""
        }
    }
}

# -------------------------------------------------------------------
# Helper: Build Pipeline
# -------------------------------------------------------------------
function Run-Build($buildType, $folder, $targetToolchain) {
    $genArgs = Get-CMakeGeneratorArgs -buildType $buildType -targetToolchain $targetToolchain

    $distSubDirName = if ($targetToolchain -eq "MSVC") { "msvc" } else { "gcc" }
    $distBinAbsPath = Join-Path (Get-Location).Path "dist/$distSubDirName/bin"

    Write-Host "`n=== Configuring $buildType [$targetToolchain] -> $folder ===" -ForegroundColor Yellow
    $cmakeConfigCmd = "cmake $genArgs -B `"$folder`" -DCMAKE_BUILD_TYPE=$buildType -DPROJECT_VERSION=`"$version`""
    Write-Host ">> $cmakeConfigCmd" -ForegroundColor Gray
    Invoke-Expression $cmakeConfigCmd | Tee-Object -FilePath build.log -Append

    if ($ConfigureOnly) {
        Write-Host "=== ConfigureOnly mode: skipping build/install ===" -ForegroundColor Magenta
        return
    }

    Write-Host "`n=== Building $buildType [$targetToolchain] ===" -ForegroundColor Yellow
    $cmakeBuildCmd = "cmake --build `"$folder`" --config $buildType"
    Write-Host ">> $cmakeBuildCmd" -ForegroundColor Gray
    Invoke-Expression $cmakeBuildCmd | Tee-Object -FilePath build.log -Append

    Write-Host "`n=== Installing $buildType [$targetToolchain] -> $distBinAbsPath ===" -ForegroundColor Yellow
    $cmakeInstallCmd = "cmake --install `"$folder`" --config $buildType --prefix `"$distBinAbsPath`""
    Write-Host ">> $cmakeInstallCmd" -ForegroundColor Gray
    Invoke-Expression $cmakeInstallCmd | Tee-Object -FilePath build.log -Append
}

# -------------------------------------------------------------------
# Helper: Dispatch Configurations
# -------------------------------------------------------------------
function Dispatch-Builds($toolchainType, $prefix) {
    if ($Config -eq "Debug" -or $Config -eq "All") {
        Run-Build -buildType "Debug" -folder "$prefix-debug" -targetToolchain $toolchainType
    }
    if ($Config -eq "Release" -or $Config -eq "All") {
        Run-Build -buildType "Release" -folder "$prefix-release" -targetToolchain $toolchainType
    }
}

# -------------------------------------------------------------------
# 5. OS-Aware Toolchain Execution
# -------------------------------------------------------------------
if ($isLinuxHost) {
    if ($Toolchain -eq "MSVC") {
        Write-Error "MSVC is unsupported on Linux. Please use GCC, Ninja, or Auto."
        exit 1
    }
    if ($Toolchain -eq "Both") {
        Write-Host "Linux environment detected: Skipping Windows MSVC target, building GCC only." -ForegroundColor Cyan
        Dispatch-Builds -toolchainType "GCC" -prefix "build"
    } else {
        Dispatch-Builds -toolchainType $Toolchain -prefix "build"
    }
} else {
    # Windows Host
    if ($Toolchain -eq "Both") {
        Dispatch-Builds -toolchainType "GCC" -prefix "build"
        Dispatch-Builds -toolchainType "MSVC" -prefix "build-msvc"
    }
    elseif ($Toolchain -eq "MSVC") {
        Dispatch-Builds -toolchainType "MSVC" -prefix "build-msvc"
    }
    else {
        Dispatch-Builds -toolchainType $Toolchain -prefix "build"
    }
}

Write-Host "`n=======================================================" -ForegroundColor Green
Write-Host "=== Build + Install complete! ===" -ForegroundColor Green
if (-not $isLinuxHost -and ($Toolchain -eq "Both" -or $Toolchain -eq "MSVC")) {
    Write-Host "MSVC binaries staged at: $(Join-Path (Get-Location).Path 'dist/msvc/bin')" -ForegroundColor Green
}
Write-Host "GCC binaries staged at:  $(Join-Path (Get-Location).Path 'dist/gcc/bin')" -ForegroundColor Green
Write-Host "Log file written to:     $(Join-Path (Get-Location).Path 'build.log')" -ForegroundColor Green
Write-Host "=======================================================" -ForegroundColor Green