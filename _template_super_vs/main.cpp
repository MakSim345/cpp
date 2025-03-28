#include "gen.h"
#include "utils.h"
#include "RandomNumbers.h"
#include "cTimer.h"
#include "printIntro.h"

long g_lTimeTick = 0;

int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int nRandomVal = -1;
    auto mainCounter = 0;
    int msTarget = 1000;

    CTimer *cTimerCtr = new CTimer();

    printf ("main - start\n");
    auto startTime = cTimerCtr->GetElapsedTimeMs();
    // std::cout << "Start: " << cTimerCtr->GetElapsedTimeMs() <<"\n";

#ifdef FILE_OUTPUT
    int nOpenFileToken = 0;
    char *FileNameF = "TimeSt.log";
    FILE *fi = NULL;

    // open the file for input:
    if ( (fi = fopen(FileNameF, "a+") ) != NULL)
    {
    // printf ("file %s was open succesfully\n", FileNameF);
    nOpenFileToken = 1;
    }
    else
    {
    printf ("file %s was not open\n", FileNameF);
    nOpenFileToken = 0;
    }

    // fprintf(fi, "Start time: %d\n", cTimerCtr.GetElapsedTimeMs());

#endif// FILE_OUTPUT

if (argc >= 2)
{
    // i = atoi(argv[1]);
    if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
    {
    // t->PrintIntroduction();
    return 1;
    }
}
    int random_number = 0;
    CRandomNumbers *_myRND = new CRandomNumbers();

    for (int i = 0; i < 2000; i ++)
    {
        std::vector<int> random_numbers;

        for (int j = 0; j < 7; j ++)
        {
            int random_number = _myRND->getRandomNumber(1, 40);
            random_numbers.push_back(random_number);
        }
        std::sort(random_numbers.begin(), random_numbers.end());
        // Print the sorted random numbers
        std::cout << (i + 1) << ": ";
        for (const int& num : random_numbers)
        {
            std::cout << num << " ";
        }
        cout << "\n";
    }

    auto start = std::chrono::steady_clock::now();

    cout << "Press Ctr-X to exit." << std::endl;
    //*************MAIN LOOP****************
    //
    do
    {

        auto now = std::chrono::steady_clock::now();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start)>= std::chrono::milliseconds(msTarget))
        {
            mainCounter++;
            nRandomVal = produceRND();
            printf ("%d - Time: %u. RND: %d\n", mainCounter, cTimerCtr->GetElapsedTimeMs(), nRandomVal);
            printf ("Time: %ld.\n", cTimerCtr->Get1msTimeMS());
            start = now;
        }

        if (nRandomVal == 0) // wait for random ZERO!
        {
            RValue = true;
        }

        // std::string cInTrace("0");
        // std::getline (std::cin, cInTrace);
    } while (!RValue);

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

    auto endTime = cTimerCtr->GetElapsedTimeMs();
    std::cout << "Application complete after " << mainCounter << " iterations. EndTime: " << endTime <<"\n";

return 0;
}

