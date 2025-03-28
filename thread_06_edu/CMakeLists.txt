cmake_minimum_required(VERSION 3.16) # check the version of CMake

# give the name to executable:
set(PROJECT_NAME thread_06_exe)
project(${PROJECT_NAME} ASM C CXX)

# Locate gtest:
# find_package (GTest REQUIRED)
# include_directories (${GTEST_INCLUDE_DIRS})

# set(CMAKE_CXX_FLAGS -pthread)

set(sources
    main.cpp
    # semaphore.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} )

# Note: pthread is needed!
# target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
