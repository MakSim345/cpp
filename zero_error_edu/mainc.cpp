#include "gen.h"
#include "phone_book.h"
#include "cTimer.h"
#include "divide_by_zero.h"

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
   getchar(); // pause, xyLe...
   nOpenFileToken = 0;
  }
      
  fprintf(fi, "Start time: %d\n", Get1msTime());
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

    int num1, num2;    
    cout << "BBeguTe 2 4ucLa gLq geLeHuq:\n";
    cin >> num1 >> num2;
    try 
    {
        float result =  quotient(num1, num2);
        cout << "4acTHoe paBHo: " << result << endl; 
    }      
    catch (DivideByZeroError err)
    {
        cout << "ERROR: ";
        err.printMesage();
        cout << endl;
        return 1;
    }
  
    return 0;

    //*************MAIN LOOP*****************//
    cout << "Press Ctr-X to exit." << std::endl;
 do 
  {
    //This is simple Windows way:
    Sleep(1000);
    std::cout << "Time GetTickCount:" << GetTickCount() << "\n";
   
    // nResult = produceRND();   
    printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   
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

