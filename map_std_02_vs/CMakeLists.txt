cmake_minimum_required(VERSION 3.16) # check the version of CMake

# To use it with Visual Studio use follow:
# call set_visual_studio_2019.bat
# > mkdir build && cd build
# > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..

# Give the name to executable:
# NOTE: ".exe" will be added in win32 automatically.
set(PROJECT_NAME map_std_exe)
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS -pthread)

set (headers
    gen.h
    cube_calc.h
    error_message.h
    map_tst.h
    oven.h
    password_generator.h
    phone_book_map.h
    RandomNumbers.h
    )

set(sources
    cube_calc.cpp
    error_message.cpp
    main.cpp
    map_tst.cpp
    oven.cpp
    password_generator.cpp
    phone_book_map.cpp
    RandomNumbers.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} ${headers})
