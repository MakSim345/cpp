cmake_minimum_required(VERSION 2.8) # check the version of CMake

set(PROJECT_NAME app)
project(${PROJECT_NAME} ASM C CXX)

set(sources
        main.cpp
        utils.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
    
# add_executable(main main.cpp
#                    utils.cpp)
