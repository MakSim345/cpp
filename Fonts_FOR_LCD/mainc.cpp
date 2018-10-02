#include "gen.h"
#include "utils.h"
#include <math.h>

#include <stdio.h>
#include <string.h>

#include "TCHAR.h"

// #define PRINT_HEX

long g_lTimeTick = 0;

int NewChar=0;
CTRACE t(1,1);

void printChar(char* ReceiveBuffer, int NbrOfReadBytes, int nHexToken)
{	
  unsigned char tmpchr;
  char nVal[1];
  
  
	// t.TRACE("Bytes: \n"); 		
	for (int j=0; j < NbrOfReadBytes; j++)
	  {
	    tmpchr=(unsigned char) ReceiveBuffer[j];
	    if (tmpchr == 0)
	    {
          if (!nHexToken)
	         t.TRACE("-");
          else
          {
	         //t.TRACE("\\0x%X ", tmpchr);
	         t.TRACE("\\0x00 ");
	      }
	    }
	    else // print '*'
	    {
          if (!nHexToken)
	        t.TRACE("*"); 
          else
	        t.TRACE("\\0x%X ", tmpchr);
	    }	     
	   }  
	 t.TRACE("\n"); 
}


int ReadFromFile(int start, int nHex)
{
  FILE * pFile;
  long lSize;
  char * buffer;
  size_t result;
  int m_start = 0;
  
  m_start = start;
  
  lSize = 32;

  pFile = fopen ( "koe.raw" , "rb" );
  if (pFile==NULL)
   {
    fputs ("File error!\n", stderr);
    exit (1);
   }

  // obtain file size:
  //fseek (pFile , 0 , SEEK_END);
  //lSize = ftell (pFile);
  //rewind (pFile);

  // allocate memory to contain the whole file:
  
  buffer = (char*) malloc (sizeof(char)*lSize);
  // buffer = (char*) malloc (32);
  if (buffer == NULL)
  {
    fputs ("Memory error",stderr); 
    exit (2);
  }
  
  // t.TRACE_HEX(buffer, lSize);
  
  // m_start = 4;
  
  fseek(pFile, m_start, SEEK_SET);
  
  // copy the file into the buffer:
  result = fread (buffer, 1, lSize, pFile);
  if (result != lSize) 
  {
    fputs ("Reading error",stderr); 
    exit (3);
  }
  // t.TRACE_HEX(buffer, lSize);  
  printChar(buffer, lSize, nHex);  
  /* the whole file is now loaded in the memory buffer. */
  // terminate
  fclose (pFile);
  free (buffer);
  return 0;
}

void printErrorMsg()
{
 t.TRACE ("Error. Read the help.\n\n");
}

int checkCoords(int nCoords)
{
  if (nCoords < 0)
  {
    t.TRACE ("Coordinate %d is less than 0!. Set to 0.\n", nCoords);
    return 0;
  }
  if (nCoords > 15)
  {
    t.TRACE ("Coordinate %d is more than 15!. Set to 15.\n", nCoords);
    return 15;
  }
  
  return nCoords;  
}

int main(int argc, char *argv[], char *envp[]) 
{
	long LastTimeIn=0;	
	long LastTimeInMS = 0;	
	int RValue = false;
	int Counter=0;	
	int nOpenFileToken = 0;
	char tmpchr;
	int CaptureModeHex = 0;
	int NbrOfReadBytes = 0;
	char ReceiveBuffer[500];
	
	const int nStrLen = 512;
	const int nCharSize = 32;
	char MData[nCharSize];
  
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

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

 int read_position = 0;
 
//**********************************************
 
 int x_pos = 0;
 int y_pos = 0;
 int k = 0;

/*
 x_pos = 31;
 y_pos = 3; 
  
 read_position = (y_pos*nStrLen*nCharSize + x_pos*nCharSize);
 for (int k = 0; k < nCharSize; k++)
 {
   // t.TRACE("%d ", k);
   ReadFromFile(read_position, MData);
   read_position = read_position + nStrLen;
 }
*/

 // printf ("argc = %d\n", argc);
 if (argc > 1)
 {
  if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
  {
   // printf ("help? - no way....\n");
   PrintIntroduction();
   RValue = true;
  }
 
  if ( (strcmp(argv[1], "get") ==0) || (strcmp(argv[1], "Get") ==0) || (strcmp(argv[1], "GET") ==0) )
  {
   if ((argc >= 4) && (argv[2]) >=0 && (argv[3]>=0))
    {
      x_pos = checkCoords(atoi(argv[2]));
      y_pos = checkCoords(atoi(argv[3]));
      
      t.TRACE("Character for coordinates: [%d], [%d]\n", x_pos, y_pos);
      
      read_position = (y_pos*nStrLen*nCharSize + x_pos*nCharSize);
      for (k = 0; k < nCharSize; k++)
       {  
          // t.TRACE ("%d: ", k);
          ReadFromFile(read_position, 0);
          read_position = read_position + nStrLen;
       }
       
      t.TRACE ("Hex for coordinates: [%d], [%d]\n", x_pos, y_pos);
      
      read_position = (y_pos*nStrLen*nCharSize + x_pos*nCharSize);
      for (k = 0; k < nCharSize; k++)
       {
          ReadFromFile(read_position, 1);
          read_position = read_position + nStrLen;
       }
      RValue = true;
    }
    else
    {
      printErrorMsg();
      RValue = true;
    } 
  }
  else
    {
      printErrorMsg();
      RValue = true;
    }
 }
 else // no params:
 {
  printErrorMsg();
  RValue = true;
 }
 
//*************MAIN LOOP*****************//
 do 
 {    
  ++Counter;    
  if (NbrOfReadBytes)
	{
		printf ("NbrOfReadBytes: %d, %s\n", NbrOfReadBytes, ReceiveBuffer);
		if (CaptureModeHex == 1) // Hex binary
		 {
		   for (int j=0; j < NbrOfReadBytes; j++)
		    {
		        tmpchr=(unsigned char)*(ReceiveBuffer-NbrOfReadBytes+j);
	            sprintf(MData,"\\x%X",tmpchr);
		        printf ("%s",MData);
		    }
	     }
	}

  if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
	{
        printf ("Time: %ld.\n",Get1msTimeMS(), 0);
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

