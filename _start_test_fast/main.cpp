#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

inline float cube(const float s) {return s*s*s;}


void dispBits(unsigned Val, int nPrintRes)
{
    unsigned BIT = 7;
    //unsigned BIT = 15;
    //unsigned   BIT = 30;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;
 
    //if (nPrintRes)
    //    printf ("Val = %d(0x%X)\n", Val, Val);
 
    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? 1 : 0 ;
     
        if (nPrintRes)
            printf ("%d", nBin);
    
        Val<<=1;
     
        if ((c%8 == 0) && nPrintRes)
            printf (" ");       
    }

    //if (nPrintRes)
    //    printf ("\n");
}


int test_foo()
{
    std::cout << "test_foo() function called!\n";
    return 1;
}

void call_other(int t())
{
    std::cout << "call_other called! Now we'll call outside function:\n";
    t();
}

void call_other_empty(int ())
{
    std::cout << "call_other_empty called!\n";    
}

class App
{
public:
    int run()
    {
        std::cout << "Hello cruel world!\n";
        
        
        return 0;
    }
    ~App()
    {
        std::cout << "Good bye!\n";
    }

};

class CubeCalc
{
public:
    CubeCalc()
    {
        std::cout << "Hello! I will calculate a cube for you!\n";
    }
    ~CubeCalc()
    {
        std::cout << "Good bye!\n";
    }
    
    int run()
    {
        std::cout << "Enter cube dimention: ";
        std::cin >> side;
        
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";
/*
        for (int i = 0; i < 1000000; i++)
        {
            long _number = my_rnd->getRandomNumber(100, 10000000);
            int _lenght_name =  my_rnd->getRandomNumber(3, 7);
            std::string _name = my_name->genPass(_lenght_name);

            pb->add_data_to_file(_name, _number);
        }
  */      

        cout << "Cube with side " << side << " is equal to " << calculation(side) << "\n";
        
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";    
        return 1;
    }

private:
    float side; 

    float calculation(float s)
    {
        return s*s*s;
    }

};

void test_array_error()
{
    char strHello[] = "Hello, world!";
    std::cout << "Enter an index: \n>";
     
    int nIndex;
    std::cin >> nIndex;     
    std::cout << "Letter #" << nIndex << " is -" << strHello[nIndex] << "- in " << strHello << std::endl; 
    // std::cout << strHello << std::endl; 
}

int &fun()
{
    static int x = 10;
    return x;
}

bool are_unique_characters(const std::string& str)
{
	std::vector<bool> char_set(256, false);

    // std::string str ("Test string");
    for (unsigned i=0; i<str.length(); ++i)
    {
        std::cout << str.at(i);
    }   

	std::cout << "\nInput str has size: " << str.size() << "\n";
    for (int i = 0; i < str.size(); ++i) 
    {
		int val = str.at(i);
        std::cout << "char - " << val << ": " << str.at(i) << "\n";
		if (char_set[val]) 
        {
			return false;
		}
		char_set[val] = true;
	}
	return true;
}


int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
    //std::auto_ptr <App> app(new App());
    //app->run();    
    
    //test_foo();        
    //call_other(test_foo);
    // test_array_error();
    
    //fun() = 30;
    //cout << fun();
    // are_unique_characters("my_test");
    /*
    int x = 4;
    printf ("%d - 0x%X\n", x);
    dispBits((unsigned)x, 1);
    printf ("\n");

    x = 1 << x;
    // x = x << 1;
    printf ("%d - 0x%X\n", x);
    dispBits((unsigned)x, 1);
    */

    struct S
    {
        long i;
        char c;
    } s;
    
    std::cout << sizeof(*(&s));

    return 1;
}
