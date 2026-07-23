add_library(DSALib SHARED
    source/SStack.cpp
    source/SList.cpp
    source/SVector.cpp
    source/SQueue.cpp
    source/SString.cpp
)

target_include_directories(DSALib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

# Export macro for Windows DLLs
target_compile_definitions(DSALib PRIVATE DSALIB_EXPORTS)
