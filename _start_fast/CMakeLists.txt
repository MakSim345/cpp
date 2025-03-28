cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME start_fast_exe)

project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS -pthread)

set (headers
    utils.h
    )

set(sources
    main.cpp
    utils.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} ${headers})
