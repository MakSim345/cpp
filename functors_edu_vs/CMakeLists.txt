cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME functors_edu)
project(${PROJECT_NAME} ASM C CXX)

set(sources
        main.cpp
        utils.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
    
# add_executable(main main.cpp
#                    utils.cpp)
