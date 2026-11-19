add_executable(App 
main.cpp
sDSATesters/source/sHashTester.cpp
sDSATesters/source/sStackTester.cpp
sDSATesters/source/sListTester.cpp
sDSATesters/source/sVectorTester.cpp
sDSATesters/source/sQueueTester.cpp
sDSATesters/source/sTuplePairTester.cpp
sDSATesters/source/sStringTester.cpp
sMathTesters/source/sCalcTester.cpp
sMathTesters/source/sComplexTester.cpp
sConcurrencyTester/source/sTCPSocketTester.cpp
TestEngine/source/sMathTester.cpp
TestEngine/source/sDSATester.cpp
TestEngine/source/sCocurrencyTester.cpp
TestFactory/source/STestFactory.cpp
)

target_link_libraries(App PRIVATE SMathLib)
target_link_libraries(App PRIVATE DSALib)
target_link_libraries(App PRIVATE AlgoLib)
target_link_libraries(App PRIVATE Concurrency)

target_include_directories(App PRIVATE
    ${CMAKE_SOURCE_DIR}/SMathLib
    ${CMAKE_SOURCE_DIR}/SMathLib/MathOperations/Header
    ${CMAKE_SOURCE_DIR}/DSA/header
    ${CMAKE_SOURCE_DIR}/Algo/header
    ${CMAKE_SOURCE_DIR}/Algo/Sort/interface
    ${CMAKE_SOURCE_DIR}/Algo/Sort/header
    ${CMAKE_SOURCE_DIR}/Concurrency/Common/header
    ${CMAKE_SOURCE_DIR}/Concurrency/Process/header
    ${CMAKE_SOURCE_DIR}/App/TestFactory/header
    ${CMAKE_SOURCE_DIR}/App/TestEngine/header
    ${CMAKE_SOURCE_DIR}/App/sMathTesters/header
    ${CMAKE_SOURCE_DIR}/App/sDSATesters/header
    ${CMAKE_SOURCE_DIR}/App/sConcurrencyTester/header
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
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Concurrency>
        $<TARGET_FILE_DIR:App>
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:App>/Concurrency/Socket
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Concurrency/Process/config.ini
        $<TARGET_FILE_DIR:App>/Concurrency/Socket/config.ini
)

