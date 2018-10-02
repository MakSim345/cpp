#include "gen.h" 
#include "utils.h"
#include "dbits.h"
#include "cTimer.h"
    
#define mkdir(path) mkdir(path,0700)
 
struct date
{
    int da_year;   
    char da_day;   
    char da_mon;   
};    

union number
{
    int x;
    float y;
};

int main( int argc, char *argv[] )
{
    int i=0;      
 
// #define YS9039384  
#ifdef YS9039384  
    char* FileNameF = "Result.log";
    FILE *fi = NULL;     
#endif          
        
    long SatelZeroTime;
    int Diff_L;
    int nCtr;
    CTimer *t = new CTimer();

// asm("movw %ax, %bx");  
// printf ("argc = %d\n", argc);

    if (argc >= 2)
    {
        nCtr=atoi(argv[1]);
    }
    else 
    {
        printf ("Please type numbers of variants, more than 0. Program halted.\n");
        return 0;
    }

    SatelZeroTime = t->Get1msTimeMS();
            
    printf ("\nHere %d results of random numbers 7x39:\n-------------\n", nCtr);
    for (i = 0; i<nCtr; )
    {
        Diff_L = ( t->Get1msTimeMS() - SatelZeroTime );
        if (Diff_L > 1010)
        {        
            srand ( time(NULL) );
            SatelZeroTime = t->Get1msTimeMS();
            // srand (t->Get1msTimeMS());
            // TRACE("\nSend: %ld ", t->Get1msTimeMS());
            // TRACE ("\nSend: %ld ", Diff_L);
            RND_Array();
            i++;
        }    
    }

    // memcpy((void *)(buffer), (const void*)&Res, sizeof(Res));
         
#ifdef YS9039384   
    if ( (fi = fopen(FileNameF, "a+") ) != NULL)     
    {
        fclose (fi);    
    }
#endif 

    return 0;   
}
 
