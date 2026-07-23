cmake_minimum_required(VERSION 3.15)
project(SMathLib LANGUAGES CXX)

add_library(SMathLib SHARED
    SMathLib.cpp
    MathOperations/Source/SComplex.cpp
    MathOperations/Source/SCalculator.cpp
)

target_include_directories(SMathLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/MathOperations/Header
)

target_compile_definitions(SMathLib PRIVATE MATHLIB_EXPORTS)

target_compile_features(SMathLib PUBLIC cxx_std_17)

# Use proper warning flags depending on compiler
if (MSVC)
    target_compile_options(SMathLib PRIVATE /W4)
else()
    target_compile_options(SMathLib PRIVATE -Wall -Wextra)
endif()
