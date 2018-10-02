#ifndef _ERATOSPHEN_H_
#define _ERATOSPHEN_H_

#include "gen.h"

class Eratosphen
{
public:
    void inputInfo()
    {
        mResultSum = 0;
        std::cout << "Hello cruel world! \nLet's check Eratosphen numbers...\n";
        cout << "Enter a number:\n";
        cin >> maxValNum;
    }

    int Run()
    {
        sqr_root_n = int(sqrt(maxValNum)) + 1;
  
        // vector<bool> bool_vector(max_val_num + 1,true);
        mBoolVector = vector<bool>(maxValNum + 1, true);
        
        // print_vector(&bool_vector);

        for(i = 2; i <= sqr_root_n; i++)
        {
            if(mBoolVector[i])
            {
                for(j = i*i; j <= maxValNum; j += i)
                {
                    mBoolVector[j]=false;
                    std::cout << "Next false element: " << j << "\n";
                }
            }
        }
        std::cout << "-------------\n";
        for(i = 2; i <= maxValNum; i++)
        {
            if(mBoolVector[i])
            {
                mResultSum += i;
                std::cout << "Next element: " << i << "\n";
            }
        }

        cout << "Result is: " << mResultSum << endl;  
        return 0;
    }
    
    void print_vector(vector<bool>* bVectorP)
    {
        vector<bool>::iterator it;
        cout << "myvector contains:";
        for (it = bVectorP->begin(); it!=bVectorP->end(); ++it)
            {
                cout << " " << *it;
            }
    }    
    
    ~Eratosphen()
    {
        std::cout << "Good bye!\n";
    }

    long double maxValNum;
    long double mResultSum;
    long double i;
    long double j;
    long double sqr_root_n;
    vector<bool> mBoolVector;
};

class Eratosphen_simple : public Eratosphen
{
public:
    
    int Run()
    {
        // vector<bool> bool_vector(max_val_num + 1,true);
        
        mBoolVector = vector<bool>(maxValNum + 1, false);
        
        // print_vector(&bool_vector);
        bool flag = false;

        for(i = 2; i <= maxValNum; i++)
        {
            //std::cout << "Next test element: " << i << "\n";
            for(j = 2; j < i; j++)
            {   
                //std::cout << "Test: "  << i  << " div " << j << ":\n";
                int bb = fmod(i, j);
                if (0 == bb)
                {
                    //std::cout << "ZERO! - break\n";
                    flag = true;
                    break;
                }
                //else                
                // std::cout << "Next false element: " << j << "\n";
            }
            if (!flag)
            {
                // std::cout << "Element " << i << " was added to list\n";
                // bool_vector[i]=true;
                result_vector.push_back(i);
            }
            flag = false;
        }

        print_vector(&result_vector);
        return 0;
    }

    void print_vector(vector<long>* myvector)
    {
        vector<long>::iterator it;
        cout << "ERATOSPHEN array contains:\n";
        for (it=myvector->begin(); it!=myvector->end(); ++it)
            {
                cout << " " << *it;
            }
        cout << "\nERATOSPHEN array END\n";
    }    

private:
    int abb;
    vector<long> result_vector;
};


#endif
