#include "gen.h"
#include "cTimer.h"
#include "phone_book.h"


int produceRND()
{
    // Generate a random number between 0 and 100
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 100);
    return dist(rng);
}

int main(int argc, char *argv[], char *envp[])
{
    long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int Counter=0;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nRandomVal = -1;

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

/*
    fstream f("text.txt");
    vector <Number> telBook;
    while (true)
    {
        Number t;
        f >> t.name;
        if (f.eof())
            break;
        f >> t.number;
        if (f.eof())
            break;

        telBook.push_back(t);
    }

    while (true)
    {
     string name;
     cout << "Enter name (or :q)\n";
     cin >> name;
     if (name == ":q")
         break;

     for (int i = 0; i < telBook.size(); i++)
     {
        if (telBook[i].name == name)
        {
            cout << name << " - " << telBook[i].number << "\n";
        }
     }
    }
*/
    auto start = std::chrono::steady_clock::now();
    auto mainCounter = 0;
    int msTarget = 100;

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

