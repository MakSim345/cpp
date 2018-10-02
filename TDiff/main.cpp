#include "gen.h"
#include "utils.h"
#include <sys/timeb.h>
#include "TCHAR.h"

int main(int argc, char *argv[], char *envp[]) 
{
    long LastTimeIn=0;    
    long LastTimeInMS = 0;    
    int RValue = false;
    int Counter=0;  
    int CaptureModeHex = 0;
    int i=0;
    int NewChar=0;
        
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
 
    FILE *file;  
    char load_string[250];
    char file_name [50];

    //printf ("argc = %d\n", argc);

    if (argc > 1)
    {
        if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
        {
            PrintIntroduction();
            return 1;
        }
    }

    sprintf(file_name, "%s", "_txapl.log"); 
    file = fopen(file_name, "r" ); //"r" == read only existing file
     
    if( file != 0 ) 
    {
        long lTimeDiff=0;
        // Get ms value from file and substract it:
        fread(load_string,1,sizeof(load_string), file);
  
        // printf( "The time was %ld\n", load_string);  
        // printf( "The time is  %ld\n", GetTickCount());
        // count time difference:
        lTimeDiff = GetTickCount() - atoi(load_string);
        // printf( "The primary time difference: %ld ms\n", lTimeDiff);
        if (lTimeDiff < 1000)
        {
            printf("Operation took %ld ms.\n", lTimeDiff);
        }
        else
        {
            lTimeDiff = (lTimeDiff/1000);
            printf("Operation took %ld sec.\n", lTimeDiff);  
        }
        fclose(file);
        // remove file !!
        remove ("_txapl.log");
        return 1;   
    }
    else
    {
        // create file and write time there:
        //printf( "The time is %ld\n", GetTickCount());   
        //printf( "File %s does not exist!!!\n", file_name);
  
        sprintf(load_string, "%ld", GetTickCount() );
        strcat(load_string, "\n"); //  
        file = fopen(file_name, "w" ); //"w" == read only existing file
        if( file != 0 ) 
            fwrite(load_string, strlen(load_string)+1, 1, file );                
        else
            printf( "Error during save to file %s\n", file_name);
        fclose(file);
        return 1;   
    }
 
#ifdef WAIT_APPLICATION
  
    i = atoi(argv[1]);
    
    if( ( i >= 100) && (i <= 100000))
    { 
        // printf ( "OK. argument = %d\n", i );
    }
    else
    {
        // RValue = true; // END mark
        if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
        {
            PrintIntroduction();
        }
        return 1;
        // printf ( "ERR. argument = %d\n", i );
    }
#endif WAIT_APPLICATION

//*************MAIN LOOP*****************//
 do 
 {    
  if ((( Get1msTimeMS() - LastTimeInMS)>10-1) || (LastTimeInMS > Get1msTimeMS() ))
    {    
        //printf ("Time: %ld.\n",Get1msTimeMS());
        Counter = Counter + 10;
        if (Counter >= i)
        {
            // printf ("Time: %ld.\n",Get1msTimeMS());
            RValue = true; // END mark
        } 
        LastTimeInMS = Get1msTimeMS();
   }   

#ifdef DOS_MODE    
    if ((( Get1msTime() - LastTimeIn)>100-1) || (LastTimeIn > Get1msTime() ))
    {
        LastTimeIn = Get1msTime();
    }
#endif // DOS_MODE    

// control of endless loop (may be also in monitor.cpp)
    if (kbhit())  // has anything been pressed from keyboard ?
    {       
   
     NewChar=(unsigned char)getch();
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


}while (!RValue);  

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
 // printf ("Application complete.\n");

return 0;
}

