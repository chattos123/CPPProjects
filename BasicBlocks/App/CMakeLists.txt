add_executable(App main.cpp)

target_link_libraries(App PRIVATE SMathLib)
target_link_libraries(App PRIVATE DSALib)

target_include_directories(App PRIVATE
    ${CMAKE_SOURCE_DIR}/SMathLib
    ${CMAKE_SOURCE_DIR}/SMathLib/MathOperations/Header
    ${CMAKE_SOURCE_DIR}/DSA/header
)

# Copy DLL next to App.exe after build
add_custom_command(TARGET App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SMathLib>
        $<TARGET_FILE:DSALib>
        $<TARGET_FILE_DIR:App>
)

