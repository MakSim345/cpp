cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME yagni_exe)

project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

set (headers
    gen.h
    bread.h
    error_message.h
    factorial.h
    hello.h
    oven.h
    )

set(sources
    main.cpp
    bread.cpp
    error_message.cpp
    factorial.cpp
    hello.cpp
    oven.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} ${headers})
