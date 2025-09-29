# PowerShell script to build the Mini IP Tool project on Windows

# This script automates the build process for the Mini IP Command Tool project on Windows.
# It assumes that CMake and a compatible C++ compiler (like MSVC) are installed and available in the system PATH.

# Set the build directory
$buildDir = "build"

# Create the build directory if it doesn't exist
if (-Not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir
}

# Navigate to the build directory
Set-Location $buildDir

# Run CMake to configure the project
cmake .. -G "Visual Studio 16 2019"  # Adjust the generator as needed for your version of Visual Studio

# Build the project
cmake --build . --config Release

# Optionally, run tests if needed
# cmake --build . --config Release --target RUN_TESTS

# Navigate back to the original directory
Set-Location .. 

# Indicate that the build process is complete
Write-Host "Build process completed successfully."