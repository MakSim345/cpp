cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME start_hello_exe)

project(${PROJECT_NAME} ASM C CXX)

# set(CMAKE_CXX_FLAGS -pthread)

set(sources
        main.cpp
        # utils.cpp
    )

# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 14)
add_executable( ${PROJECT_NAME} ${sources} )
