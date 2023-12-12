
To use Ninja for Visual Studio compielr:

> cmake -G Ninja -DCMAKE_C_COMLPILER=cl -DCMAKE_CXX_COMPILER=cl ..


How to install google test:

1.
  > git clone https://github.com/google/googletest.git


2.
    > sudo apt-get install libgtest-dev
    > sudo apt-get install cmake # install cmake
    > cd /usr/src/gtest
    > sudo cmake CMakeLists.txt
    > sudo make

    # copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
    > cd lib
    > sudo cp *.a /usr/lib

3.
  > sudo apt-get install libgtest-dev
  > g++ -I /usr/include/gtest -I /usr/src/gtest/ -c /usr/src/gtest/src/gtest-all.cc
  > ar -rv libgtest.a gtest-all.o
  > mv libgtest.a /usr/lib/

