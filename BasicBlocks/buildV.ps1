param(
    [ValidateSet("Debug","Release","All")]
    [string]$Config = "All",

    [switch]$CleanOnly
)

$ErrorActionPreference = "Stop"

Write-Host "=== Cleaning old build directories ==="
Remove-Item -Recurse -Force build-debug, build-release, dist -ErrorAction SilentlyContinue

if ($CleanOnly) {
    Write-Host "=== CleanOnly requested. No build performed. ==="
    exit 0
}

# Version stamping (auto embed into CMake)
$version = Get-Date -Format "yyyy.MM.dd.HHmm"
Write-Host "=== Using version stamp: $version ==="

function Build-And-Install($buildType, $folder) {
    Write-Host "=== Configuring $buildType build ==="
    $cmakeConfigCmd = "cmake -G Ninja -B $folder -DCMAKE_BUILD_TYPE=$buildType -DPROJECT_VERSION=$version"
    Write-Host ">> $cmakeConfigCmd"
    Invoke-Expression $cmakeConfigCmd | Tee-Object -FilePath build.log -Append

    Write-Host "=== Building $buildType ==="
    $cmakeBuildCmd = "cmake --build $folder"
    Write-Host ">> $cmakeBuildCmd"
    Invoke-Expression $cmakeBuildCmd | Tee-Object -FilePath build.log -Append

    Write-Host "=== Installing $buildType ==="
    $cmakeInstallCmd = "cmake --install $folder --config $buildType"
    Write-Host ">> $cmakeInstallCmd"
    Invoke-Expression $cmakeInstallCmd | Tee-Object -FilePath build.log -Append
}

switch ($Config) {
    "Debug"   { Build-And-Install "Debug" "build-debug" }
    "Release" { Build-And-Install "Release" "build-release" }
    "All"     { 
        Build-And-Install "Debug" "build-debug"
        Build-And-Install "Release" "build-release"
    }
}

Write-Host "=== Build + Install complete! ==="
Write-Host "Distribution folder created at: $((Get-Item .).FullName)\dist"
Write-Host "Log file written to: $((Get-Item .).FullName)\build.log"
