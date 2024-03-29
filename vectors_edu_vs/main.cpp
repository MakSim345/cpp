#include "gen.h"
#include "worker.h"
#include "utils.h"
#include "cTimer.h"
#include "map_tst.h"
#include "vector_tst.h"
#include "RandomNumbers.h"
#include <algorithm>
#include <ctime>

class SuperList
{
public:
    SuperList()
    {
        rndNumbersVectorM.push_back(23);
        rndNumbersVectorM.push_back(24);
        rndNumbersVectorM.push_back(25);
        // mRandomNumbers (10, 23);
        // mRandomNumbers{ 10, 20, 30 };
    }
   ~SuperList() = default;

   vector <int>& getMyListUnsafely()
   {
       // call getMyListUnsafely().clear() will erase the list
       return rndNumbersVectorM;
   }

   const vector <int>& getMyListSafely() // rem: const keyword !
   {
       return rndNumbersVectorM;
   }

   int getMySize()
   {
       return rndNumbersVectorM.size();
   }

private:
    vector <int> rndNumbersVectorM;
};

typedef struct {
    long len;
    float *data;
} myDefinedVector;

long vec_len(myDefinedVector *defVectorP)
{
    return defVectorP->len;
}

void combine0(myDefinedVector *defVectorP, float *destP)
{   
    *destP = 1;
    for (int i = 0; i <vec_len(defVectorP); i++ )
    {
        *destP *= defVectorP->data[i];
    }
}

template <class superType>
superType selectMaximumValue (superType valOneP, superType valTwoP)
{
    superType retValMax = valOneP;
    if (valTwoP > retValMax)
        retValMax = valTwoP;

    return retValMax;
}

template <class superType>
superType Add(superType a, superType b)
{
    return a + b;
}

int main(int argc, char *argv[], char *envp[])
{
    long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int Counter=0;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;

    printf ("main - start\n");
    CTimer *_time = new CTimer ();

    if (argc >= 2)
    {
        // i = atoi(argv[1]);
        if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
        {
            // t->PrintIntroduction();
            return 1;
        }
    }

    char* word1 = "Hello";
    char* word2 = "Hello";

    float aFloatArray[SIZE_5000];
    myDefinedVector v = {SIZE_5000, aFloatArray};

    float res;

    for (long i = 0; i < SIZE_5000; i++ )
    {
        aFloatArray[i] = rand();
    }

    combine0(&v, &res);
    /*
    SuperList* mySuperList = new SuperList();
    
    mySuperList->getMyListSafely();
    int a = mySuperList->getMySize();

    mySuperList->getMyListUnsafely().clear();
    a = mySuperList->getMySize();
    */

    if( word1 == word2 )
      {
        printf("equal\n");
      }
    else
      {
        printf("not equal\n");
      }

    vector <int> viRandomNumbers;
    vector <int> mImageArray;

    vector_string();

    cout << "viRandomNumbers: " << viRandomNumbers.empty() << "\n";
    viRandomNumbers.push_back(23);
    CRandomNumbers *rnd_arr = new CRandomNumbers();

    std::cout << "Time Start:" << std::clock() << "\n";
    viRandomNumbers = rnd_arr->getRandomNumbers(0, 1000, 100000, false);
    std::cout << "Time end:" << std::clock() << "\n";
    // vector_string();

    cout << "Result selectMaximumValue(23.6, 45.7): " << selectMaximumValue(23.6, 45.7) << "\n";
    cout << "Result selectMaximumValue(2, 5)      : " << selectMaximumValue(2, 5) << "\n";

    std::cout << "Time Start:" << std::clock() << "\n";
    sort(viRandomNumbers.begin(), viRandomNumbers.end());
    std::cout << "Time END:" << std::clock() << "\n";

    /*
    vector<int>::const_iterator _iterator;
    for(_iterator = viRandomNumbers.begin(); _iterator != viRandomNumbers.end(); ++_iterator)
    {
        // std::cout << (*_iterator) << std::endl;
        std::cout << (*_iterator) << ", ";
    }
    */
    std::cout << std::endl;
    ostringstream sStr;
    map_test();

    int n_total = Add(23, 16);
    long l_total = Add<long>(10245, 35234);
    double d_total = Add(12.60, 35.98);

    //*************MAIN LOOP*****************//
 cout << "Press Ctr-X to exit." << std::endl;
 do
  {
    //This is simple Windows way:
    Sleep(1000);
    //std::cout << "Time GetTickCount:" << GetTickCount() << "\n";

   //nResult = produceRND();
   //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

   //nResult = produceRND();
   //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

    /***************************************
    // This is complicated one-thread way:
    if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
    {
        printf ("Time: %ld.\n",Get1msTimeMS());
        Sleep(100);

        LastTimeInMS = Get1msTimeMS();
    }
    ***************************************/

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

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

printf ("Application complete.\n");
return 0;
}



