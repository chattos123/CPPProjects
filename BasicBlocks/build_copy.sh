#!/usr/bin/env bash

# Exit immediately if a command fails
set -e

# Clean old build directories
rm -rf build-debug build-release

# -------------------------
# Debug build
# -------------------------
echo "=== Configuring Debug build ==="
cmake -G Ninja -B build-debug \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_COMPILER=/c/msys64N/ucrt64/bin/gcc.exe \
  -DCMAKE_CXX_COMPILER=/c/msys64N/ucrt64/bin/g++.exe

echo "=== Building Debug ==="
cmake --build build-debug

# Copy DLL next to EXE
cp build-debug/bin/Debug/SMathLib.dll build-debug/bin/Debug/App.exe build-debug/

# -------------------------
# Release build
# -------------------------
echo "=== Configuring Release build ==="
cmake -G Ninja -B build-release \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=/c/msys64N/ucrt64/bin/gcc.exe \
  -DCMAKE_CXX_COMPILER=/c/msys64N/ucrt64/bin/g++.exe

echo "=== Building Release ==="
cmake --build build-release

# Copy DLL next to EXE
cp build-release/bin/Release/SMathLib.dll build-release/bin/Release/App.exe build-release/

