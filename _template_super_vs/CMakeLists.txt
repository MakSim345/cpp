cmake_minimum_required(VERSION 3.16) # check the version of CMake

# To use it with Visual Studio use follow:
# call set_visual_studio_2019.bat
# > mkdir build && cd build
# > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..

# Give the name to executable:
# NOTE: ".exe" will be added in win32 automatically.
set(PROJECT_NAME template_super_exe)
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS -pthread)

set (headers
    gen.h
    cTimer.h
    printIntro.h
    RandomNumbers.h
    utils.h
    )

set(sources
    main.cpp
    cTimer.cpp
    printIntro.cpp
    RandomNumbers.cpp
    utils.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} ${headers})
