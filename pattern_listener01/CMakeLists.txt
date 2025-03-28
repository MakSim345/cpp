cmake_minimum_required(VERSION 3.16) # check the version of CMake

set(PROJECT_NAME listener01)
project(${PROJECT_NAME} ASM C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# enable_testing()
# add_subdirectory (googletest)

#set (HEADER_FILES
#    gen.h
#    )

set(SOURCE_FILES
    main.cpp
    )

# Add the executable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

# add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
# add_subdirectory (test)

