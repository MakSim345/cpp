cmake_minimum_required(VERSION 3.19) # check the version of CMake

set(PROJECT_NAME ExampleTests)
project(${PROJECT_NAME} C CXX)

# GoogleTest requires at least C++14
# set(CMAKE_CXX_STANDARD 14)

set(sources
    exampleTests.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )

target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main
    Example
    )

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    )

