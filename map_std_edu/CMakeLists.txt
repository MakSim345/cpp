cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME map_std_exe)

project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS -pthread)

set(sources
        cube_calc.cpp
        error_message.cpp
        main.cpp
        map_tst.cpp
        oven.cpp
        password_generator.cpp
        phone_book_map.cpp
        RandomNumbers.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
