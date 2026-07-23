cmake_minimum_required(VERSION 3.10)
project(calculator LANGUAGES CXX)

# Install into project root instead of Program Files
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# Version stamping passed from build.ps1
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")

# Set output directories for Debug/Release
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

# Add subdirectories for library and app
add_subdirectory(SMathLib)
add_subdirectory(App)
add_subdirectory(DSA)

# Install both targets into a dist/ folder
install(TARGETS App SMathLib DSALib
    RUNTIME DESTINATION dist/bin
    LIBRARY DESTINATION dist/bin
    ARCHIVE DESTINATION dist/lib
)
