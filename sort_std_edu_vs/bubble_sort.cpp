//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "bubble_sort.h"

void bubble_sort_optim(int arraySize)
{
    const int n = 8;
    // int a[n];
    std::vector<int> a;
    int i = 0;
    int j = 0;
    int counter = 0;
    bool isRepalced= false;

    std::ifstream f("file.txt");
    // randomize();
    
    std::cout << "Before sorting" << std::endl;
    // a.resize(arraySize);
    for  (i=0; i<arraySize; ++i)
    {
        f >> counter;
        a.push_back(counter);
        std::cout << a[i] << " "; 
    }
    std::cout << std::endl;
    // sorting;
    // for  (i=n-1; i>=1; --i)
    do
    {
        isRepalced = false;        
        for (j=0; j < arraySize - 1; ++j)
        {
            if (a[j] > a[j + 1] )
            {
                int foo = a[j];
                a[j] = a[j+1];
                a[j+1] = foo;
                isRepalced = true;
            }
        }
        counter++;
        /*for  (i=0; i<arraySize; ++i)
        {
            cout << a[i] << " ";
        }*/
        std::cout <<" iteration :" << counter << std::endl;
    } while (isRepalced);

    std::cout << "After sorting (with " << counter <<" iterations." << std::endl;
    for  (i=0; i<arraySize; ++i)
    {
        std::cout << a[i] << " ";
    }

}

void bubble_sort()
{
    const int n = 8;
    int a[n];
    int i;
    std::ifstream f("file.txt");

    for  (i=0; i<n; ++i)
    {
        f >> a[i];
        std::cout << a[i] << std::endl; 
    }
    // sorting;
    std::cout << "After sorting" << std::endl;

    for  (i=n-1; i>=1; --i)
    {
        for (int j=0; j < i; ++j)
        {
            if (a[j] > a[j + 1] )
            {
                int foo = a[j];
                a[j] = a[j+1];
                a[j+1] = foo;
            }
        }    
    }

    for  (i=0; i<n; ++i)
    {
        std::cout << a[i] << std::endl;
    }

}
