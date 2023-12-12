cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME reference_vs_pointer_edu_exe)
project(${PROJECT_NAME} ASM C CXX)

# try to use GDB - Debug:
set(CMAKE_CXX_FLAGS "-g")

# set(CMAKE_CXX_FLAGS -pthread)

set(sources
        main.cpp
        utils.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
