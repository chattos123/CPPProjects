add_library(DSALib SHARED
    source/SStack.cpp
    source/SList.cpp
    source/SVector.cpp
    source/SQueue.cpp
    source/SCircularQ.cpp
    source/SString.cpp
)

target_include_directories(DSALib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

# Crucial: Define BUILDING_DSA_DLL to trigger __declspec(dllexport) in ExportMacro.h
target_compile_definitions(DSALib PRIVATE BUILDING_DSA_DLL)

# GCC / Clang symbol visibility configuration (matches MSVC dll import/export rules)
set_target_properties(DSALib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)