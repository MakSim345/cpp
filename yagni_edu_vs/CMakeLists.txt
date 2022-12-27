cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME yagni_exe)

project(${PROJECT_NAME} ASM C CXX)

set(CMAKE_CXX_FLAGS -pthread)

set(sources
        main.cpp
        bread.cpp
        error_message.cpp
        factorial.cpp
        hello.cpp
        oven.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
