//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "bubble_sort.h"

void bubble_sort_optim(int arraySize)
{
    const int n = 8;
    vector<int> a;
    int i = 0;
    int j = 0;
    int counter = 0;
    bool isRepalced= false;

    ifstream f("file.txt");
    // randomize();
    
    cout << "Before sorting" << endl;
    // a.resize(arraySize);
    for  (i=0; i<arraySize; ++i)
    {
        f >> counter;
        a.push_back(counter);
        cout << a[i] << " "; 
    }
    cout << endl;
    // sorting;
    // for  (i=n-1; i>=1; --i)
    do
    {
        isRepalced = false;        
        for (j=0; j < arraySize - 1; ++j)
        {
            if (a[j] > a[j + 1] )
            {
                /*int foo = a[j];
                a[j] = a[j+1];
                a[j+1] = foo;*/
                swap(a[j], a[j+1]);
                isRepalced = true;
            }
        }
        counter++;
        /*for  (i=0; i<arraySize; ++i)
        {
            cout << a[i] << " ";
        }*/
        cout <<" iteration :" << counter << endl;
    } while (isRepalced);

    cout << "After sorting (with " << counter <<" iterations." << endl;
    for  (i=0; i<arraySize; ++i)
    {
        cout << a[i] << " ";
    }

}

void bubble_sort()
{
    const int n = 8;
    int a[n];
    int i;
    ifstream f("file.txt");

    for  (i=0; i<n; ++i)
    {
        f >> a[i];
        cout << a[i] << endl; 
    }
    // sorting;
    cout << "After sorting" << endl;

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
        cout << a[i] << endl;
    }

}
