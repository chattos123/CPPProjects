param(
    [ValidateSet("Debug","Release","All")]
    [string]$Config = "All"
)

Write-Host "Cleaning configuration: $Config"

function Clean-Folder($folder) {
    if (Test-Path $folder) {
        Write-Host "Removing $folder ..."
        Remove-Item -Recurse -Force $folder
    } else {
        Write-Host "Folder $folder does not exist, skipping."
    }
}

switch ($Config) {
    "Debug"   { Clean-Folder "build-debug" }
    "Release" { Clean-Folder "build-release" }
    "All"     {
        Clean-Folder "build-debug"
        Clean-Folder "build-release"
        Clean-Folder "dist"
    }
}

Write-Host "Clean completed."