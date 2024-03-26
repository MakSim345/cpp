GTest and CMake
How to create a simple hello world application in C++ where GTest is used. Use CmakeLists and ninja. Small example run from command line in windows. Compiler - cl.exe from Visual Studio

"ChatGPT"
Sure, lets create a simple C++ Hello World application using Google Test (GTest), CMake, and Ninja on Windows. We will use the "cl.exe" compiler from Visual Studio.

1. Install Visual Studio with C++ Support:
Make sure you have Visual Studio installed with C++ support. You can download Visual Studio Community Edition for free from the official Microsoft website.

2. Install Ninja:
Download Ninja from the official GitHub repository: Ninja Releases

Extract the ninja.exe file and add its location to your system PATH.

3. Create the Project Structure:
Create a project folder with the following structure:

HelloWorldGTest/
│
├── src/
│   ├── main.cpp
│   └── hello_world.cpp
│
├── test/
│   └── hello_world_test.cpp
│
├── CMakeLists.txt
└── .gitignore

4. Create the Source Files:
File src/main.cpp:

#include <iostream>
#include "hello_world.h"

int main()
{
    HelloWorld hello;
    std::cout << hello.getGreeting() << std::endl;
    return 0;
}


File src/hello_world.cpp:

#include "hello_world.h"

std::string HelloWorld::getGreeting() const
{
    return "Hello, World!";
}

src/hello_world.h:

#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <string>

class HelloWorld
{
public:
    std::string getGreeting() const;
};

#endif // HELLO_WORLD_H
5. Create the Test File:
test/hello_world_test.cpp:

#include "gtest/gtest.h"
#include "hello_world.h"

TEST(HelloWorldTest, GetGreeting)
{
    HelloWorld hello;
    EXPECT_EQ("Hello, World!", hello.getGreeting());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

6. Create the CMakeLists.txt File:
CMakeLists.txt:

cmake_minimum_required(VERSION 3.12)
project(HelloWorldGTest)

set(CMAKE_CXX_STANDARD 14)

# Locate GTest package
find_package(GTest REQUIRED)

# Include GTest headers
include_directories(${GTEST_INCLUDE_DIRS})

# Add source files
set(SOURCE_FILES src/main.cpp src/hello_world.cpp)

# Add executable
add_executable(HelloWorldGTest ${SOURCE_FILES})

# Link with GTest and GTest Main
target_link_libraries(HelloWorldGTest GTest::GTest GTest::Main)


7. Create the .gitignore File:
.gitignore:

build/

8. Build the Project:
Open a command prompt in the project directory and run the following commands:

mkdir build
cd build
cmake -G Ninja ..
ninja

9. Run the Tests:

./HelloWorldGTest

This will execute your GTest and should display a "Hello, World!" greeting message if the test passes.

Make sure to adapt the paths if you organize your files differently. This example assumes a basic structure for simplicity.
