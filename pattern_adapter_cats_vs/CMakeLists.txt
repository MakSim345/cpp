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
    polar_bear.h
    polar_bear_adapter.h
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

# ---------------------------------------------------------------
# Google Test (loaded from local directory)
# ---------------------------------------------------------------
# Prevent overriding the parent project compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(C:/googletest googletest_build)

enable_testing()

set(test_sources
    tests/test_adapters.cpp
)

# Re-use production sources (exclude main.cpp to avoid duplicate main)
set(sources_no_main
    cat_if.cpp
    cat_info_printer.cpp
    cats.cpp
    home_cat_adapter.cpp
    tiger.cpp
)

add_executable(adapter_tests ${test_sources} ${sources_no_main} ${headers})
target_include_directories(adapter_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(adapter_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(adapter_tests)