cmake_minimum_required(VERSION 3.15) # check the version of CMake

set(PROJECT_NAME Prostotron)
project(${PROJECT_NAME} C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# enable_testing()
# add_subdirectory (googletest)

set (headers
    mem_cell.h
    memory.h
    processor.h
    utils.h
    gen.h
    )

set(sources
    main.cpp
    mem_cell.cpp
    memory.cpp
    processor.cpp
    utils.cpp
    )

# add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
# add_subdirectory (test)
add_executable( ${PROJECT_NAME} ${sources} )

