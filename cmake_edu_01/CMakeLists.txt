cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME app)
project(${PROJECT_NAME} ASM C CXX)
set(CMAKE_CXX_STANDARD 17)

set(sources
        main.cpp
        utils.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
    
# add_executable(main main.cpp
#                    utils.cpp)
