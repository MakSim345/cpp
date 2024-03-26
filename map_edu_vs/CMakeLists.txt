cmake_minimum_required(VERSION 3.16) # check the version of CMake

# To use it with Visual Studio use follow:
# call "set_visual_studio_2019.bat"
# > mkdir build && cd build
# > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..

set(PROJECT_NAME app_map)
project(${PROJECT_NAME} ASM C CXX)

set(sources
        main.cpp
        fprint.cpp
        person.cpp
        phone_book_map.cpp
    )

include_directories(include)

add_executable( ${PROJECT_NAME} ${sources} )
