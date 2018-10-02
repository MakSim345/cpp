/*********************************************************************

  timer.h  
  01.10.2004 Initial coding YS 
  
**********************************************************************/

// #include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
 
     
// int _tmain(int argc, _TCHAR* argv[])
int main()
{
    setlocale(LC_ALL, "rus");
    char buff1[500];
    
    ifstream fout1("f1.txt");
    
    if (!fout1.is_open()) // check if file was not open
    {
        cout << "File can't be open or create!\n"; //print error
    }
    
    while(!fout1.eof()) //read file 
    {
        fout1.getline(buff1, 500);
        std::cout << buff1 << endl;
    }
    
    fout1.close(); // close the file
    system("pause");
    return 0;
}

