#include <iostream>
#include <fstream>
using namespace std;
     
int main()
{
    ofstream outFile;
    float a = 4.3333f;
    float b = 5.0302f;
    std::string fileNameToOpen = "calculations.txt";

    // outFile.open("calculations.txt");
    outFile.open(fileNameToOpen);

    if (!outFile.good()) // can be "if (outFile.fail())"
    {
        std::cout << std::endl << "Can not open file " << fileNameToOpen <<  std::endl;
    }
    else
    {
        // write to a file line by line:
        outFile << "a = " << a << "\n" ;
        outFile << "b = " << b << "\n" ;
        outFile << "a + b = " << a + b << "\n" ;
        outFile << "a * b = " << a * b << "\n" ;
        outFile.close();
        std::cout << "File '" << fileNameToOpen << "' created succesfully" <<  std::endl;
    }

}
