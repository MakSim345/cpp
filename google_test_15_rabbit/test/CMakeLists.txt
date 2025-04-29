cmake_minimum_required(VERSION 3.19) # check the version of CMake

set(PROJECT_NAME RabbitRaceTests)
project(${PROJECT_NAME} C CXX)

# Enable testing
enable_testing()

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

# Find Google Test
find_package(GTest REQUIRED)

set(sources
    exampleTests.cpp
    #../random_generator.h
    #../rabbit.h
    #../turtle.h
    #../winner.h
    )

# Add test source files
add_executable( ${PROJECT_NAME} ${sources} )

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE ../)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)

# Add the test to CTest
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    )

