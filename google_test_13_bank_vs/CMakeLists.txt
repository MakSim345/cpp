cmake_minimum_required(VERSION 3.25) # check the version of CMake

set(PROJECT_NAME struct_exe)
project(${PROJECT_NAME} C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

enable_testing()
add_subdirectory (googletest)

set headers(
    gen.h
)

set(sources
    main.cpp
    )

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})

add_executable( ${PROJECT_NAME} ${sources} )

add_subdirectory (test)
