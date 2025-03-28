#include "gen.h"
#include "printHex.h"
#include "timer_util.h"
#include "trash.h"
#include "my_templates.h"

/*
* Derek Banas
* C++ Tutorial 16 : C++ Threads
* https://www.youtube.com/watch?v=IdwJdJw65tU&list=PLGLfVvz_LVvQ9S8YSV0iDsuEU8v11yP9M&index=19
*/

double acctBalance = 100;
std::vector < unsigned int> primeVectorGlobal;
std::mutex acctLock;
std::mutex vectorLockGlobal;

void doSomeWork( void )
{
    const size_t length = 10;
    for (size_t i = 0; i < length; i++)
    {
        std::cout << "hello from thread " << this_thread::get_id() << "\tdoSomeWork\t" << i << std::endl;
        this_thread::sleep_for(chrono::milliseconds(produceRND(3)));
    }

    return;
}

std::string GetTime()
{
    auto nowTime = std::chrono::system_clock::now();
    std::time_t nowTimeInT = std::chrono::system_clock::to_time_t(nowTime);
    // tm my_local_time = *localtime(&nowTimeInT);
    auto retVal= std::ctime(&nowTimeInT);
    return retVal;
}

void GetMoney(int idP, double withdrawalP)
{
    std::lock_guard <std::mutex> lock(acctLock);

    // put thread to sleep for a random time in seconds:
    std::this_thread::sleep_for(std::chrono::seconds(produceRND(10)));

    std::cout << "Thread #" << idP << " tries to withdrawal $"
              << withdrawalP << " on "
              << GetTime() << "\n";

    if ((acctBalance - withdrawalP) >= 0)
    {
        acctBalance -= withdrawalP;
        std::cout << "New Account Balance is $ " << acctBalance << "\n";
    }
    else
    {
        std::cout << "Not Enough Money in Account!\n";
        std::cout << "Current Balance is $" << acctBalance << "\n";
    }
}

void ExecuteThread(int threadIdP)
{
    std::clock_t start = std::clock();
    std::cout << "Thread " << threadIdP << " started " << start << " \n";
    std::this_thread::sleep_for(chrono::milliseconds(produceRND(3000)));
    std::clock_t duration = std::clock() - start;
    std::cout << "Thread " << threadIdP << " took " << duration << " clock ticks\n";
}


void FindPrimes(unsigned int startP, unsigned int endP)
                // std::vector <unsigned int> &vecP)
{
    for (unsigned int x = startP; x < endP; x++)
    {
        for (unsigned int y = 2; y < x; y++)
        {
            if ((x % y) == 0)
            {
                break;
            }
            else if((y+1) == x)
            {
                vectorLockGlobal.lock();
                primeVectorGlobal.push_back(x);
                vectorLockGlobal.unlock();
            }
        }
    }
}

void FindPrimesWithThreads(unsigned int startP, unsigned int endP, unsigned int numThreadsP)
{
    std::vector <std::thread> threadVector;
    unsigned int threadSpread = endP/numThreadsP;
    unsigned int newEnd = startP + threadSpread - 1;
    for (unsigned int x = 0; x <numThreadsP; x++)
    {
        threadVector.emplace_back(FindPrimes, startP, newEnd);
        startP += threadSpread;
        newEnd += threadSpread;
    }
    for (auto& t : threadVector)
    {
        t.join();
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;

    const size_t length = 10;

    CTimer *_time = new CTimer();
    printf ("main start on time: %ld. \n", _time->GetElapsedTimeMs());

    std::cout << "GetTime: " <<  GetTime() << "\n";
#ifdef TEST_ACCOUNT_YS
    //test thread pool using a bank account:
    const int poolSize = 10;
    std::thread threads[poolSize];
    for ( int i = 0; i <poolSize; i++)
    {
        threads[i] = std::thread(GetMoney, i, 15);
    }

    for (int i = 0; i < poolSize; i++)
    {
        threads[i].join();
    }
#endif

    // use thread for calculate prime numbers:
    std::vector < unsigned int> primeVector;
    std::clock_t startTime = std::clock();

    const uint32_t maxNumberToCalc = 10000000;
    // run in one thread:
    // FindPrimes(1, maxNumberToCalc);
    // For 1000000 - 127 sec.

    // run in multi-threads:
    const uint32_t threadsNumber = 10;
    FindPrimesWithThreads(1, maxNumberToCalc, threadsNumber);
    // For 1000000 - 54 sec., 10 threads

    for (auto vecElement: primeVectorGlobal)
    {
        std::cout << vecElement << "\n";
    }
    //std::cout << "Thread " << threadIdP << " started " << start << " \n";

    std::clock_t duration = std::clock() - startTime;
    std::cout << "Execution time " << " took " << duration/double(CLOCKS_PER_SEC) << " seconds\n";

    //std::thread th1(ExecuteThread, 1);
    //std::thread th2(ExecuteThread, 2);

    //th1.join();
    //th2.join();

    // std::thread th(doSomeWork);

    for (size_t i = 0; i < length; i++)
    {
        // std::cout << "hello from thread " << this_thread::get_id() << "\tMAIN\t" << i << std::endl;
        // this_thread::sleep_for(chrono::milliseconds(200));
    }

    // th.join();

//*************MAIN LOOP*****************//
    cout << "\n$ > Press Any Key to exit." << std::endl;
    do
    {
        //This is simple Windows way:
        Sleep(55);

        //nResult = produceRND();
        //printf ("1-Time: %ld. RND: %d\n", _time->GetElapsedTimeMs(), nResult);

       //nResult = produceRND();
        //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            NewChar=(unsigned char)_getch();
            RValue = true;
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


