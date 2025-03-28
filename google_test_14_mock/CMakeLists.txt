cmake_minimum_required(VERSION 3.16) # check the version of CMake

# To use it with Visual Studio use follow:
# call set_visual_studio_2019.bat
# > mkdir build && cd build
# > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..

# Give the name to executable:
# NOTE: ".exe" will be added in win32 automatically.
set(PROJECT_NAME runTestsMock14)
project(${PROJECT_NAME})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

enable_testing()


# Set the external build directory for Google Test and Google Mock
set(GTEST_BINARY_DIR ${CMAKE_BINARY_DIR}/googletest)
set(GMOCK_BINARY_DIR ${CMAKE_BINARY_DIR}/googlemock)

# Add the GoogleTest and GoogleMock subdirectories from the external build directory
add_subdirectory(C:/googletest ${GTEST_BINARY_DIR})
add_subdirectory(C:/googletest/googlemock ${GMOCK_BINARY_DIR})

# add_subdirectory (googletest) - works only for local subdir, not global!
# Specify the binary directory for GoogleTest: test and mock:
# set(GTEST_BINARY_DIR ${CMAKE_BINARY_DIR}/googletest)
# add_subdirectory(C:/googletest googletest)

# set(GMOCK_BINARY_DIR ${CMAKE_BINARY_DIR}/googlemock)
# add_subdirectory(C:/googletest googlemock)
# add_subdirectory(C:/googletest googlemock)

set(CMAKE_CXX_FLAGS -pthread)

set (headers
        gen.h
        PriceCalculator.h
        ShoppingCart.h
        MockPriceCalculator.h
    )

set(sources
        PriceCalculator.cpp
        ShoppingCart.cpp
        ShoppingCartTest.cpp
    )

add_executable( ${PROJECT_NAME} ${sources} ${headers} )

# target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
# target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})

# Link the executable with GoogleTest and GoogleMock libraries
target_link_libraries(${PROJECT_NAME} gtest gmock_main
    debug ${GTEST_BINARY_DIR}/Debug/gtestd.lib
    optimized ${GTEST_BINARY_DIR}/Release/gtest.lib
    debug ${GMOCK_BINARY_DIR}/Debug/gmockd.lib
    optimized ${GMOCK_BINARY_DIR}/Release/gmock.lib
)

# Include directories for GoogleTest and GoogleMock headers
# target_include_directories(${PROJECT_NAME} PRIVATE C:/path/to/googletest/include)
# target_include_directories(${PROJECT_NAME} PRIVATE C:/path/to/googlemock/include)
# Include GoogleTest headers
target_include_directories(${PROJECT_NAME} PRIVATE C:/googletest/include)
target_include_directories(${PROJECT_NAME} PRIVATE C:/googlemock/include)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

