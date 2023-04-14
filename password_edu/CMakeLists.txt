cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME pass_exe)
project(${PROJECT_NAME} ASM C CXX)

set(CMAKE_CXX_FLAGS -pthread)

set(sources
        main.cpp
        divide_by_zero.cpp
        factorial.cpp
        pass.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
