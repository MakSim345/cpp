cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME ChuckNorris)
project(${PROJECT_NAME} ASM C CXX)

set(sources
        main.cpp
        utils.cpp
        error_message.cpp
        ChuckNorris.cpp
    )

include_directories(include)

add_executable( ${PROJECT_NAME} ${sources} )
    
# add_executable(main main.cpp
#                    utils.cpp)
