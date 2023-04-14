cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME app_zero_div)
project(${PROJECT_NAME} ASM C CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS -pthread)

set(sources
        main.cpp
        cTimer.cpp
        divide_by_zero.cpp
        phone_book.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
