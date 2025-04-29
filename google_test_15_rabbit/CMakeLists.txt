cmake_minimum_required(VERSION 3.18) # check the version of CMake

set(PROJECT_NAME RabbitRace_exe)
project(${PROJECT_NAME} ASM C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

enable_testing()
# add_subdirectory (googletest)

set (HEADER_FILES
    app/gen.h
    app/animal.h
    app/rabbit.h
    app/random_generator.h
    app/turtle.h
    app/winner.h
    )

set(SOURCE_FILES
    app/animal.cpp
    app/rabbit.cpp
    app/random_generator.cpp
    app/turtle.cpp
    app/winner.cpp
    )

set(MAIN_CPP
    app/main.cpp
    )

# Add test source file(s)
set(TEST_SOURCES
    test/exampleTests.cpp
    )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${MAIN_CPP})

# Include directories
include_directories()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(RabbitRaceTests ${TEST_SOURCES} ${SOURCE_FILES})
# add_executable(RabbitRaceTests ${TEST_SOURCES} ${HEADER_FILES} ${SOURCE_FILES})

# Include directories for the test executable
target_include_directories(RabbitRaceTests PRIVATE ${CMAKE_SOURCE_DIR})

# Link Google Test and pthread to the test executable
target_link_libraries(RabbitRaceTests ${GTEST_LIBRARIES} pthread)
# target_link_libraries(RabbitRaceTests PRIVATE gtest_main)

# Add the test to CTest
add_test(
    NAME RabbitRaceTests
    COMMAND RabbitRaceTests
)
