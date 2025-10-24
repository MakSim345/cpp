cmake_minimum_required(VERSION 3.8) # check the version of CMake

# give the name to executable:
set(PROJECT_NAME runGTests04_exe)
project(${PROJECT_NAME} ASM C CXX)

# Locate gtest
find_package (GTest REQUIRED)
include_directories (${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS -pthread)

set (HEADER_FILES
    gen.h
    error_message.h
    parser.h
    utils.h
    )

set(SOURCE_FILES
    error_message.cpp
    parser.cpp
    utils.cpp
    )

set(MAIN_CPP
    main.cpp
    )

# Add test source file(s)
set(TEST_SOURCES
    unit_gtest.cpp
    )

# Add the test executable
add_executable( ${PROJECT_NAME} ${TEST_SOURCES} ${SOURCE_FILES})

# add_executable(main main.cpp
#                    utils.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
