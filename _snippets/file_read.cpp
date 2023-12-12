#include <iostream>
#include <fstream>
using namespace std;
     
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
    //std::cout << "\nPress ENTER to exit...\n";
    //cin.get();
    
    // this PAUSE will give a info text - press any key to continue, etc.
    system("PAUSE");

    // this pause is silent. You have to know to press any key.
    // system("pause>0");
    
    return 0;
}

/*
 * A sample C++ code that reads a text file filled with numbers 
 * and copies each value to an int array:
 */

#include <iostream>
#include <fstream>
#include <vector>

int main() 
{
    // Make sure to replace "input.txt" with the actual file name that contains your numbers.
    std::ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) 
    {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<int> numbers; // Using a vector to dynamically store the numbers

    int number;
    while (inputFile >> number) 
    {
        numbers.push_back(number);
    }

    inputFile.close();

    // Copying the values to an int array
    int size = numbers.size();
    int* array = new int[size];
    for (int i = 0; i < size; i++) 
    {
        array[i] = numbers[i];
    }

    // Printing the values in the int array
    for (int i = 0; i < size; i++) 
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    delete[] array; // Don't forget to delete the dynamically allocated array

    return 0;
}
/*------------------------------------------------------*/
int main()
{
    constexpr int aSize = 12;

    ifstream inFile;
    std::string str;
    int number;
    char letter;

    inFile.open("people.txt");
    if(inFile.fail())
    {
        std::cout << std::endl << "File not found!" << std::endl;
    }
    else
    {

        std::cout << "Read from File:" << std::endl;
        while (!inFile.eof() )
        {
            getline(inFile, str);
            std::cout << str << ", ";

            getline(inFile, str);
            number = stoi(str);
            std::cout << number << ", ";

            getline(inFile, str);
            letter = str[0];
            std::cout << letter << std::endl;
        }
        inFile.close();
    }

/* File: "people.txt" 

Jane Rogers
34
J
Joe Peterson
30
J
George P. Burdell
62
G
Jenny Drake
25
J
*/

  /*
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    // Read values from a file and init an array:
    for (size_t i = 0; i < aSize; i++)
    {
      inputFile >> number; // read next value from the file
      answer[i] = number;
    }
    // print resulted array:
    for (size_t i = 0; i < 20; i++)
    {
      std::cout << i << " - " << answer[i] << "\n";
    }

    for (size_t i = aSize-1; i <= 0 ; i--)
    {
        while (!temperatureStack.empty() && temperatureStack.top() <= )
        {
            std::cout << "Remove from stack: " << temperatureStack.top() << "\n";

            temperatureStack.pop();
        }


    }
  */

    printf("Application complete.\n");
    // system("PAUSE"); // only for Visula Studio!
    return 0;
}
