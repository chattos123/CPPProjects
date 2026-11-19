cmake_minimum_required(VERSION 3.16)

set(CONCURRENCY_SOURCES
    Common/source/SConfigParser.cpp
    Process/source/STCPEnvironment.cpp
    Process/source/STCPConnection.cpp
    Process/source/STCPServer.cpp
    Process/source/STCPClient.cpp
)

set(CONCURRENCY_HEADERS
    Common/header/ExportMacro.h
    Common/header/SConfigParser.h
    Process/header/STCPEnvironment.h
    Process/header/STCPConnection.h
    Process/header/STCPServer.h
    Process/header/STCPClient.h
)

add_library(Concurrency SHARED
    ${CONCURRENCY_SOURCES}
    ${CONCURRENCY_HEADERS}
)

add_library(BasicBlocks::Concurrency ALIAS Concurrency)

target_include_directories(Concurrency
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/header
        ${CMAKE_CURRENT_SOURCE_DIR}/Process/header
)

target_compile_definitions(Concurrency
    PRIVATE
        BUILDING_DSA_DLL
)

if(WIN32)
    target_link_libraries(Concurrency PRIVATE ws2_32)
endif()

target_compile_features(Concurrency PUBLIC cxx_std_17)