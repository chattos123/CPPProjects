# CPPProjects

A collection of basic C++ building blocks, example applications, and test harnesses used for learning and experiments.

## Contents

- `App` — sample application and test runners.
- `DSA` — data structures and algorithms implementations.
- `SMathLib` — small math library and related utilities to test small examples.
- `build-*` directories — generated build trees for different configurations (Ninja, MSVC, Release/Debug).

## Requirements

- CMake 3.15 or newer
- A C++17-compatible compiler (MSVC, Clang, or GCC)
- Ninja (optional, recommended for faster builds)

## Building (Ninja)

From the repository root:

```bash
mkdir -p build
cd build
cmake -G Ninja ..
cmake --build . --config Debug
```

## Building (MSVC / Windows)

Using PowerShell from the repo root:

```powershell
cmake -S . -B build-msvc-debug -G "Visual Studio 17 2022" -A x64
cmake --build build-msvc-debug --config Debug
```

## Running

- Example app (Windows): `build\bin\Debug\App.exe`
- Example app (Linux/macOS): `./build/bin/Debug/App`

## Contributing

Contributions, bug reports, and small improvements are welcome. Please open an issue or submit a pull request.

## License

This repository does not include a license file. Add one if you intend to reuse or publish code from here.

