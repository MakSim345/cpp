CMake edu:

"https://www.johnlamp.net/cmake-tutorial-1-getting-started.html"

1. To use "cl.exe" from Visual Studio:
    - create "CMakeLists.txt"
    - create "build" directory:
        > mkdir build && cd build
    - call "cmake" and give compiler name:
        > cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..
    - run "ninja":
        > ninja





============================================
REF:
"https://habr.com/ru/post/155467/"
"https://dmerej.info/blog/post/chuck-norris-part-1-cmake-ninja/"
"https://ilyas-hamadouche.medium.com/build-your-c-projects-faster-using-ninja-3d7af9b418fc"
