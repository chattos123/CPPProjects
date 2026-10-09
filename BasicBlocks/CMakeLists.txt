cmake_minimum_required(VERSION 3.10)
project(calculator LANGUAGES CXX)

# Install into project root instead of Program Files
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# Version stamping passed from build scripts
if(PROJECT_VERSION)
    add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
endif()

# Set output directories for Debug/Release
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

# Ensure Linux binaries find adjacent .so libraries without manual LD_LIBRARY_PATH
set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# Add subdirectories for library and app
add_subdirectory(SMathLib)
add_subdirectory(DSA)
add_subdirectory(Algo)
add_subdirectory(App)

# Install both targets into a dist/ folder
install(TARGETS App SMathLib DSALib AlgoLib
    RUNTIME DESTINATION dist/bin
    LIBRARY DESTINATION dist/bin
    ARCHIVE DESTINATION dist/lib
)
