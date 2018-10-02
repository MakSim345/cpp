#include "gen.h"
#include "worker.h"
#include "utils.h"
#include "cTimer.h"
#include "bubble_sort.h"
#include "RandomNumbers.h"

#include <iostream>
#include <algorithm>
#include <vector>

// using namespace std;

void print_vector(std::vector<int>* myvector)
{
    std::vector<int>::iterator it;
    std::cout << "myvector contains:";
    for (it=myvector->begin(); it!=myvector->end(); ++it)
        {
            std::cout << " " << *it;
        }
}

void saveRandomNumbers(int arraySize)
{
    int random_number = 0;
    CRandomNumbers *_myRND = new CRandomNumbers();
    
    std::ofstream myfile;
    myfile.open ("file.txt");
    // myfile << "Writing this to a file.\n";    

    for (int i = 0; i < arraySize; i ++)
    {
        random_number = _myRND->getRandomNumber(0, arraySize-1);
        // cout << i << " - Random number: " << random_number << endl;
        myfile << random_number << std::endl;
    }

    myfile.close();
}

void myfunction (int i) 
{
  std::cout << " " << i;
}


int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 10;
    int random_number = 0;

    printf ("main - start\n");
    CTimer *_time = new CTimer ();

    int myints[] = {32,71,12,45,26,80,53,33};
    std::vector<int> int_vector(myints, myints+8);
    
    std::vector<int> myvector; //  (myints, myints+8);
    std::vector<int>::iterator it;

    CRandomNumbers *_myRND = new CRandomNumbers();
    for (int i = 0; i < arraySize; i ++)
    {
        random_number = _myRND->getRandomNumber(0, arraySize-1);
        // cout << i << " - Random number: " << random_number << endl;
        
        myvector.push_back(random_number);
    }    

    std::cout << "\nVector before sort:" << std::endl;
    print_vector(&myvector);

    std::sort (myvector.begin(), myvector.begin() + arraySize);
    std::cout << "\nVector AFTER sort:" << std::endl;
    print_vector(&myvector);

    std::cout << "\nVector before sort:" << std::endl;
    print_vector(&int_vector);

    std::sort (int_vector.begin(), int_vector.begin() + 4);
    std::cout << "\nVector AFTER sort:" << std::endl;
    print_vector(&int_vector);


    std::cout << "myvector contains:";
    for_each (myvector.begin(), myvector.end(), myfunction);

    // bubble_sort();
    // saveRandomNumbers(arraySize);
    // bubble_sort_optim(arraySize);
    
//*************MAIN LOOP*****************//
std::cout << "\nPress Ctr-X to exit." << std::endl;
do 
{
    //This is simple Windows way:
    Sleep(100);
   
   
   //nResult = produceRND();   
   //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   
   //nResult = produceRND();   
   //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

   // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        RValue = true; 

        NewChar=(unsigned char)_getch();    
        if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
        {
            RValue = true; // END mark
        }     
        if (NewChar == 'd')  // pressed
        {
            if (1 == CaptureModeHex) 
                CaptureModeHex = 1;
            else
                CaptureModeHex = 0;
        }
    }
} while (!RValue);  
printf ("Application complete.\n");
return 0;
}

