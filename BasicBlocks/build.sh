#!/usr/bin/env bash

# Exit immediately if a command fails
set -e

# Clean old build directory
rm -rf build

# Configure with Ninja Multi-Config
cmake -G "Ninja Multi-Config" -B build \
  -DCMAKE_C_COMPILER=/c/msys64N/ucrt64/bin/gcc.exe \
  -DCMAKE_CXX_COMPILER=/c/msys64N/ucrt64/bin/g++.exe

# Build Debug
cmake --build build --config Debug

# Build Release
cmake --build build --config Release
