cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME cards_app)
project(${PROJECT_NAME} ASM C CXX)

set(sources
        mainc.cpp
        deck.cpp
        ElectricOven.cpp
        utils.cpp
    )

# include_directories(include)

add_executable( ${PROJECT_NAME} ${sources} )

