cmake_minimum_required(VERSION 3.16) # check the version of CMake


# To use it with Visual Studio use follow:
# call set_visual_studio_2019.bat
# > mkdir build && cd build
# > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..

set(PROJECT_NAME Example)
project(${PROJECT_NAME} C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

enable_testing()

# Specify the binary directory for GoogleTest
set(GTEST_BINARY_DIR ${CMAKE_BINARY_DIR}/googletest)
add_subdirectory(C:/googletest ${GTEST_BINARY_DIR})

set (headers
    gen.h
    example.h
    )

set(sources
    example.cpp
    main.cpp
    )

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})

target_link_libraries(${PROJECT_NAME} gtest) # Link against the GoogleTest library
target_include_directories(${PROJECT_NAME} PUBLIC C:/googletest/include) # Include GoogleTest headers

add_subdirectory (test)
# add_executable( ${PROJECT_NAME} ${sources} )

