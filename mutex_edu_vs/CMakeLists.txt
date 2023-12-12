cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME mutex_edu_exe)
project(${PROJECT_NAME} ASM C CXX)

set(CMAKE_CXX_FLAGS -pthread)

set(sources
        main.cpp
        TimerClass.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
