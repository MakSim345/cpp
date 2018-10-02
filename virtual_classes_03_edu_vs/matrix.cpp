
#include "matrix.h"

matrix::matrix()
{
    init_alphabet();
    system ("TITLE The Matrix");
    system ("color 0A");
}

void matrix::run_matrix()
{
    for (int i = 0; i<25; i++)
    {
        int a = rand() % matrix_array.size();
        cout << " " << matrix_array[a];
        cout << " ";
    }
    cout << endl;
}

void matrix::init_alphabet()
{
    matrix_array.push_back("q");
    matrix_array.push_back("w");
    matrix_array.push_back("e");
    matrix_array.push_back("r");
    matrix_array.push_back("t");
    matrix_array.push_back("y");
    matrix_array.push_back("u");
    matrix_array.push_back("i");
    matrix_array.push_back("o");
    matrix_array.push_back("p");
    matrix_array.push_back("a");
    matrix_array.push_back("s");
    matrix_array.push_back("d");
    matrix_array.push_back("f");
    matrix_array.push_back("g");
    matrix_array.push_back("h");
    matrix_array.push_back("j");
    matrix_array.push_back("k");
    matrix_array.push_back("l");
    matrix_array.push_back("z");
    matrix_array.push_back("x");
    matrix_array.push_back("c");
    matrix_array.push_back("v");
    matrix_array.push_back("b");
    matrix_array.push_back("n");
    matrix_array.push_back("m");
    matrix_array.push_back("0");
    matrix_array.push_back("1");
    matrix_array.push_back("2");
    matrix_array.push_back("3");
    matrix_array.push_back("4");
    matrix_array.push_back("5");
    matrix_array.push_back("6");
    matrix_array.push_back("7");
    matrix_array.push_back("8");
    matrix_array.push_back("9");
}
