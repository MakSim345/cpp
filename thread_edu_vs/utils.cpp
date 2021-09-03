#include "utils.h"

int produceRND(int maxP)
{
    static int nFirstTime = 1;
    int random;

    if (1 == nFirstTime)
    {
        srand(time(NULL));
        nFirstTime = 0;
        // auto nowTime = std::chrono::system_clock::now();                
        // std::time_t sleepTime = std::chrono::system_clock::to_time_t(nowTime);
        // tm my_local_time = *localtime(&sleepTime);
        // srand(time(&sleepTime));
    }
    // random = 1 + (rand() % RND_MAX);
    random = 1 + (rand() % maxP);
    printf("TRACE: =====================> produceRND returns %d\n", random);
    return random;
}

void PrintIntroduction()
{
    int i;
    int nFrame = 59;
    printf ("\t%c", 201);
    for (i=0; i<nFrame; i++)
    {
        printf ("%c", 205);
    }
    
    printf ("%c\n", 187);	
	printf ("\t%c The wait command is used within a computer batch file     %c\n", 186, 186);
	printf ("\t%c and allows the computer to pause the currently running    %c\n", 186, 186);
	printf ("\t%c batch file for an amount of milliseconds .                %c\n", 186, 186);
	printf ("\t%c Usage: 'WAIT 1000' will wait for 1 second.                %c\n", 186, 186);
	printf ("\t%c                                                           %c\n", 186, 186);
	printf ("\t%c                   GE (c) 2007.                            %c\n", 186, 186);

	printf ("\t%c", 200);
	for (i=0; i<nFrame; i++)
    {
	   printf ("%c", 205);
    }
	printf ("%c\n", 188);	
};
