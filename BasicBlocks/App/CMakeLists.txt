add_executable(App 
main.cpp
implementation/sHashTester.cpp
implementation/sStackTester.cpp
implementation/sListTester.cpp
implementation/sVectorTester.cpp
implementation/sQueueTester.cpp
implementation/sTuplePairTester.cpp
implementation/sStringTester.cpp
implementation/sDSATester.cpp
)

target_link_libraries(App PRIVATE SMathLib)
target_link_libraries(App PRIVATE DSALib)

target_include_directories(App PRIVATE
    ${CMAKE_SOURCE_DIR}/SMathLib
    ${CMAKE_SOURCE_DIR}/SMathLib/MathOperations/Header
    ${CMAKE_SOURCE_DIR}/DSA/header
    ${CMAKE_SOURCE_DIR}/App/header
    ${CMAKE_SOURCE_DIR}/App/interface
)

# Copy DLLs next to App.exe after build
add_custom_command(TARGET App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SMathLib>
        $<TARGET_FILE_DIR:App>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:DSALib>
        $<TARGET_FILE_DIR:App>
)

