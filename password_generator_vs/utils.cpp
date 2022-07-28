#include "utils.h"
#include "gen.h"
// #include <sys/time.h>

#define RND_MAX 65536

extern long g_lTimeTick;

long getTimeMs()
{
    struct timeval t;
    gettimeofday(&t, 0);
    long retVal = ((t.tv_sec * 1000) + (t.tv_usec/1000.0));
    // std::cout << "Time:" << retVal << "\n";
    return retVal;
}

int produceRND()
{
    static int nFirstTime = 1;
    int random;
 
    if (1 == nFirstTime)
    {
        srand (time (NULL));
        nFirstTime = 0;
    }
    random = 1 + (rand() % RND_MAX);
    return random;
}
 

// End of the class.


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
