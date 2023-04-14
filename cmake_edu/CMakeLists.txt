cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME ToDoList)
project(${PROJECT_NAME} ASM C CXX)

set(CMAKE_CXX_STANDARD 17)

set(sources
        main.cpp
        ToDo.cpp
    )

include_directories(include)

add_executable( ${PROJECT_NAME} ${sources} )
