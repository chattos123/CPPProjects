# ============================================================
# Algo/CMakeLists.txt
# Shared library build for AlgoLib
# ============================================================

# Create the shared library target
add_library(AlgoLib SHARED
    source/AlgoStub.cpp
    source/ISortAlgorithmExports.cpp
)

# ------------------------------------------------------------
# Include directories
# ------------------------------------------------------------
target_include_directories(AlgoLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/Sort/interface
    ${CMAKE_CURRENT_SOURCE_DIR}/Sort/header
    ${CMAKE_SOURCE_DIR}/DSA/header
)

# ------------------------------------------------------------
# Define export symbol for AlgoLib
# ------------------------------------------------------------
target_compile_definitions(AlgoLib PRIVATE BUILDING_ALGO_DLL)

# ------------------------------------------------------------
# Visibility and linking properties
# ------------------------------------------------------------
set_target_properties(AlgoLib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    INTERFACE_LINK_LIBRARIES ""
)

# ------------------------------------------------------------
# Optional: specify C++ standard and warnings
# ------------------------------------------------------------
target_compile_features(AlgoLib PUBLIC cxx_std_17)
if (MSVC)
    target_compile_options(AlgoLib PRIVATE /W4)
else()
    target_compile_options(AlgoLib PRIVATE -Wall -Wextra -pedantic)
endif()