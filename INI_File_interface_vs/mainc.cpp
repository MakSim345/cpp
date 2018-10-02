// dev001.cpp : Defines the entry point for the console application.
//

#include "gen.h"
#include "utils.h"
#include "cfgfile.h"
// #include "commport.h"
//#include "RingBuffer.h"
#include<math.h>

#define STRICT 1 
//#include <windows.h>
//#include <Mmsystem.h>
//#include <iostream.h>
//#include <stdio.h>
#include "iostream"

#include <sys/timeb.h>
//#include <time.h>
//#include <math.h>
//#include <assert.h>

#include "TCHAR.h"

long g_lTimeTick = 0;

int NewChar=0;

CRC_Struct CRC_Calculation (unsigned char * str, int NumbOfChars)
{            
 CRC_Struct CRC_Struct;
 unsigned char CRC;
 int i;

for (i=0; i<NumbOfChars; i++)
{
  CRC = (CRC + (unsigned char)str[i]) % 0xFFFF;
  // TRACE  ("str[%d]=%d CRC = %d / ", i ,(unsigned char) str[i], CRC);
}
//TRACE  ("CRC = %d 0x%X\n", CRC, CRC);
//TRACE  ("CRC>>8 = %d 0x%X\n", (CRC>>8), (CRC>>8));
//TRACE  ("CRC & 255 = %d 0x%X\n", (CRC & 255), (CRC & 255));    
 CRC_Struct.CRC[0]=(CRC >> 8);
 CRC_Struct.CRC[1]=(CRC & 255);
return CRC_Struct;    
}


int main(int argc, char *argv[], char *envp[]) 
{
    long LastTimeIn=0;    
    long LastTimeInMS = 0;    
    int RValue = false;
    int Counter=0;    
    int nSec=0;
    int nOpenFileToken = 0;
    int RingBuffSize= 10;
    int CaptureModeHex = 0;
    unsigned long uResult = 0;
    int NbrOfReadBytes=0;
    int i=0;
    double fPow = 0;
    char ReceiveBuffer[50];
    memset(ReceiveBuffer, '*', 50);

// #define FILE_OUTPUT

#ifdef FILE_OUTPUT
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
   getchar(); // nay3a, xyLe...
   nOpenFileToken = 0;
  }
      
    fprintf(fi, "Start time: %d\n", Get1msTime());
#endif// FILE_OUTPUT

  //*********************TEST MODULE**************
    char *szDeviceName = new TCHAR[50];
  
    //sprintf(szDeviceName, "%s", "Com1");
    CTRACE *log_file;
    log_file = new CTRACE(1,1);

    printf ("BEFORE time: %ld\n", Get1msTimeMS()); 
    printf( "\n"); 
    
    /*
        for (i=0; i<101; i++)
        {
          // printf ("[%d]-%c ", i, ReceiveBuffer[i], ReceiveBuffer[i]);
            fPow = pow(2,i);
            fprintf(fi, "2->%d = %0.0f\n",i, fPow);
            printf("2->%d = %0.0f\n",i, fPow);
        }
        */

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
    char szName[255];
    int iAge=0;
    double fltHieght=0.0;
    bool bMarriage=0;
    int defArr[10];
    int resArr[10];
    // printf ("Set FileNaMe: Logger.ini\n" );
    CFGFile iniWriter(".\\Logger.ini");
    // CFGFile iniWriter;
    //iniWriter.WriteProfileString("Setting", "Name", "jianxx");   
    //iniWriter.WriteProfileInt("Setting", "Age", 27); 
    //iniWriter.WriteProfileFloat("Setting", "Height", 1.82f); 
     
    printf ("Start to read strings from ini file.\n");
    
    iniWriter.GetProfileString("Setting", "Name", "", szName, 0);
    // iniWriter.GetProfileInt("Setting", "Age", 0, &iAge);
    iniWriter.GetProfileInts("Setting", "Age", 4, defArr, resArr);
    iniWriter.GetProfileDouble("Setting", "Height", 0.0, &fltHieght); 
     
    /*
    char *szName = iniReader.ReadString("Setting", "Name", "");   
    int iAge = iniReader.ReadInteger("Setting", "Age", 25); 
    float fltHieght = iniReader.ReadFloat("Setting", "Height", 1.80f); 
    bool bMarriage = iniReader.ReadBoolean("Setting", "Marriage", true); 
    */
    printf ("Name: %s\n", szName);
    // printf ("Age: %d\n", iAge);
    printf ("Height: %f\n", fltHieght);
     
    printf ("Ages:\n");
     
    for (i=0; i<4; i++)
    {
        printf ("\t[%d]: %d\n", i, resArr[i]);
    }
    // delete szName;  

    //printf ("Application complete.\n");
    // return 0; 
    //ChangeBuffer(ReceiveBuffer, 16);
    
        
    for (i=0; i<10; i++)
    {
        printf ("[%d]-%c ", i, ReceiveBuffer[i], ReceiveBuffer[i]);
    }
            
//*************MAIN LOOP*****************//
 do 
 {    
    ++Counter;    
  
    if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
    {    
      
        //uResult = CmPort.WriteToPort("COM-PORT-TEST ",14);
        //ReadFromPort:     
        printf ("Time: %ld. WriteToPort: %ld bytes\n",Get1msTimeMS(), uResult);
        LastTimeInMS = Get1msTimeMS();
    }   
   
    if ((( Get1msTime() - LastTimeIn)>100-1) || (LastTimeIn > Get1msTime() ))
    {    
        //printf ("NO-PENT time: %u, Pa3HocTb: %d\n", t.GetElapsedTimeMks(), (t.GetElapsedTimeMks() - LastTimeInMS));
        LastTimeIn = Get1msTime();
        //RND_Array(1);
    }
    
    // control of endless loop (may be also in monitor.cpp)
    if (kbhit())  // has anything been pressed from keyboard ?
    {       
        RValue = true;
        NewChar=(unsigned char)getch();
        if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
        {
            RValue = true; // END mark
        }
        if (NewChar == 'd')  // CTRL-X   pressed
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
 
 printf ("Application complete.\n");

return 0;
}

/*

#include "iostream"
#include "IniWriter.h"
#include "IniReader.h"
int main(int argc, char * argv[])
{
 CIniWriter iniWriter(".\\Logger.ini");
 iniWriter.WriteString("Setting", "Name", "jianxx");   
 iniWriter.WriteInteger("Setting", "Age", 27); 
 iniWriter.WriteFloat("Setting", "Height", 1.82f); 
 iniWriter.WriteBoolean("Setting", "Marriage", false);  
 CIniReader iniReader(".\\Logger.ini");
 char *szName = iniReader.ReadString("Setting", "Name", "");   
 int iAge = iniReader.ReadInteger("Setting", "Age", 25); 
 float fltHieght = iniReader.ReadFloat("Setting", "Height", 1.80f); 
 bool bMarriage = iniReader.ReadBoolean("Setting", "Marriage", true); 
 
 std::cout<<"Name:"<<szName<<std::endl
   <<"Age:"<<iAge<<std::endl 
   <<"Height:"<<fltHieght<<std::endl 
   <<"Marriage:"<<bMarriage<<std::endl; 
 delete szName;  
 return 1;   
}

    
        */

