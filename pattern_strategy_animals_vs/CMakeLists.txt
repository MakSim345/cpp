cmake_minimum_required(VERSION 3.18) # check the version of CMake

set(PROJECT_NAME app_strategy_exe)
project(${PROJECT_NAME} ASM C CXX)

set(CMAKE_CXX_FLAGS -pthread)

set (headers
    gen.h
    animals.h
    FlyBehaviorIf.h
    utils.h
    )

set(sources
    main.cpp
    animals.cpp
    utils.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )
