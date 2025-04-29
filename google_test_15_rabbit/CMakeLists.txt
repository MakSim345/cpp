cmake_minimum_required(VERSION 3.18) # check the version of CMake

set(PROJECT_NAME RabbitRace_exe)
project(${PROJECT_NAME} ASM C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

# Set policy to avoid the DOWNLOAD_EXTRACT_TIMESTAMP warning
cmake_policy(SET CMP0135 NEW)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
# add_subdirectory (googletest)

set (HEADER_FILES
    gen.h
    animal.h
    rabbit.h
    random_generator.h
    turtle.h
    winner.h
    )

set(SOURCE_FILES
    animal.cpp
    rabbit.cpp
    random_generator.cpp
    turtle.cpp
    winner.cpp
    )

set(MAIN_CPP
    main.cpp
    )

# Add test source file(s)
set(TEST_SOURCES
    test/exampleTests.cpp
    )

# Add the main executable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${MAIN_CPP})

# Include directories
include_directories()

include(GoogleTest)
# Find Google Test
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(RabbitRaceTests ${TEST_SOURCES} ${SOURCE_FILES})
# add_executable(RabbitRaceTests ${TEST_SOURCES} ${HEADER_FILES} ${SOURCE_FILES})

# Include directories for the test executable
target_include_directories(RabbitRaceTests PRIVATE ${CMAKE_SOURCE_DIR})

# Link Google Test and pthread to the test executable
# target_link_libraries(RabbitRaceTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(RabbitRaceTests PRIVATE gtest_main)
# target_link_libraries(tests gtest gtest_main)

# Add the test to CTest
add_test(
    NAME RabbitRaceTests
    COMMAND RabbitRaceTests
)

# add_subdirectory (test)

