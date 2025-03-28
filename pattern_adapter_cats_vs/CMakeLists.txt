cmake_minimum_required(VERSION 3.16) # check the version of CMake

# To use it with Visual Studio use follow:
# call set_visual_studio_2019.bat
# > mkdir build && cd build
# > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..

# Give the name to executable:
# NOTE: ".exe" will be added in win32 automatically.
set(PROJECT_NAME adapter_cats_exe)
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS -pthread)

set (headers
    gen.h
    cat_if.h
    cat_info_printer.h
    cats.h
    home_cat_adapter.h
    tiger.h
    )

set(sources
    main.cpp
    cat_if.cpp
    cat_info_printer.cpp
    cats.cpp
    home_cat_adapter.cpp
    tiger.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} ${headers})
