#include "gen.h" 
#include "utils.h"

extern long g_lTimeTick;
/*
int produceRND()
{
 static int nFirstTime = 1;
 int random;
 
 if (1 == nFirstTime)
 {
  srand ((unsigned)time (NULL));
  nFirstTime = 0;
 }
 random = 1 + (rand() % RND_MAX);
 return random;
}
*/
int produceRND()
{
    // Generate a random number between 0 and 100
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 100);
    return dist(rng);
}

void PrintIntroduction()
{
  int i;
  int nFrame = 59;
  printf ("\t%c", 201);
  for (i=0; i<nFrame; i++)
    printf ("%c", 205);
    
    printf ("%c\n", 187);	
	printf ("\t%c The wait command is used within a computer batch file     %c\n", 186, 186);
	printf ("\t%c and allows the computer to pause the currently running    %c\n", 186, 186);
	printf ("\t%c batch file for an amount of milliseconds .                %c\n", 186, 186);
	printf ("\t%c Usage: 'WAIT 1000' will wait for 1 second.                %c\n", 186, 186);
	printf ("\t%c                                                           %c\n", 186, 186);
	printf ("\t%c                   GE (c) 2007.                            %c\n", 186, 186);

	printf ("\t%c", 200);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
	printf ("%c\n", 188);	

};

CTimer::CTimer() :
    isTimerStarted(false),
    ctrTimer1MsStartM(0),
    ctrTimer1MsDiffM(0)
{
    this->Start();
}

long CTimer::Get1msSinceEpoch()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}

long CTimer::Get1msTimeMS()
{
    // get 1 ms time since the class created.
    // use milliseconds since Epoch to count.
    ctrTimer1MsDiffM = Get1msSinceEpoch() - ctrTimer1MsStartM;
    return ctrTimer1MsDiffM;
}

void CTimer::Start()
{
    startTimeM = std::chrono::high_resolution_clock::now();
    ctrTimer1MsStartM = this->Get1msSinceEpoch();
    isTimerStarted = true;
}

unsigned int CTimer::GetElapsedTimeMs() const
{
    // Returns the elapsed time in number of milliseconds
    //if (!isTimerStarted)
    //{
    //    return 0;
    //}
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (endTime - startTimeM).count();
}

uint64_t CTimer::GetElapsedTimeMks() const
{
    // Returns the elapsed time in number of microseconds
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>
        (endTime - startTimeM).count();
}

