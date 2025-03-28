MAY-2024

Multithreading.

=====================================================================
CMake info:
"https://www.johnlamp.net/cmake-tutorial-1-getting-started.html"

1. To use "cl.exe" from Visual Studio:
    - create "CMakeLists.txt"
    - create "build" directory:
        > mkdir build && cd build
    - call "cmake" and give compiler name:
        > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..
    - run "ninja":
        > ninja



