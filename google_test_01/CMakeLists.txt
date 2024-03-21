cmake_minimum_required(VERSION 3.16) # check the version of CMake


# To use it with Visual Studio use follow:
# call set_visual_studio_2019.bat
# > mkdir build && cd build
# > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..

# Give the name to executable:
# NOTE: ".exe" will be added in win32 automatically.
set(PROJECT_NAME runTests01)
project(${PROJECT_NAME})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

enable_testing()
# add_subdirectory (googletest) - works only for local subdir, not global!
# Specify the binary directory for GoogleTest
set(GTEST_BINARY_DIR ${CMAKE_BINARY_DIR}/googletest)
add_subdirectory(C:/googletest ${GTEST_BINARY_DIR})

set(CMAKE_CXX_FLAGS -pthread)

set(sources
        test.cpp
        person.cpp
        counter.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )

target_link_libraries(${PROJECT_NAME} gtest) # Link against the GoogleTest library
target_include_directories(${PROJECT_NAME} PUBLIC C:/googletest/include) # Include GoogleTest headers

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
