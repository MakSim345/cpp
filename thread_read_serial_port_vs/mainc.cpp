/* BEGTHRD.C illustrates multiple threads using functions:
 *
 *      _beginthread            _endthread
 *
 *
 * This program requires the multithreaded library. For example,
 * compile with the following command line:
 *     CL /MT /D "_X86_" BEGTHRD.C
 *
 * If you are using the Visual C++ development environment, select the
 * Multi-Threaded runtime library in the compiler Project Settings
 * dialog box.
 *
 */

#include "gen.h"
#include "utils.h"
#include "comm_if.h"
#include "commport.h"

#include <windows.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stddef.h>
#include <stdlib.h>
#include <conio.h>

void thReadSerialPort(void *dummy );
void TheIncrement( void *dummy);
void Bounce( void *ch );
void CheckKey( void *dummy );

BOOL repeat = TRUE;     /* Global repeat flag and video variable */
HANDLE hStdOut;         /* Handle for console window */
CONSOLE_SCREEN_BUFFER_INFO csbi;    /* Console information structure */

double i;
unsigned long uResult = 0;
//long g_lTimeTick = 0;
int DispSync=0;
int MainNewChar=0;
char ReceiveBuffer[500];
int NbrOfReadBytes=0;

CommPort *CPort[4];
CRITICAL_SECTION critsect;

void main()
{
    char ch = 'A';
    int RValue = false;
    long LastTimeInMS = 0;
    unsigned char tmpchr;
    unsigned char IRISbuffer[50];
    int nOpenFileToken = 0;

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

#define USE_OUTPUT_FILE
#ifdef USE_OUTPUT_FILE
	char *FileNameF = "allegro.log";
	FILE *fi = NULL;

    // open the file for input:
    if ( (fi = fopen(FileNameF, "w") ) != NULL) // open empty file for writing.
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

    fprintf(fi, "Start time: %d\n", Get1msTimeMS());
#endif  //USE_OUTPUT_FILE

    InitializeCriticalSection(&critsect);
    // init IRIS message. Emulation of receiving?

    IRISbuffer[0]=0x1F;
    IRISbuffer[1]=0x1E;
    IRISbuffer[2]=0x38;
    IRISbuffer[3]=0x88;
    IRISbuffer[4]=0x7E;

    /* Get display screen's text row and column information. */
    // GetConsoleScreenBufferInfo( hStdOut, &csbi );

    /* Launch CheckKey thread to check for terminating keystroke. */
    //_beginthread( CheckKey, 0, NULL );
    _beginthread( thReadSerialPort, 0, NULL );
	//_beginthread( TheIncrement, 0, NULL );

	LastTimeInMS = Get1msTimeMS();

    /* Loop until CheckKey terminates program. */
 while( repeat )
 {

    if (NbrOfReadBytes)
    {
      // printf ("Main: NbrOfReadBytes: %d\n", NbrOfReadBytes);
        for (int j=0; j < NbrOfReadBytes; j++)
        {
	        tmpchr=(unsigned char) ReceiveBuffer[j];
	        fprintf(fi, "\\0x%X", tmpchr);
			// SendStr(MData,origin,strlen(MData));
			// printf ("%s",MData);
			printf ("\\0x%X",tmpchr);
	    }
	    printf ("\n");
		EnterCriticalSection(&critsect); // lock something...
		NbrOfReadBytes = 0; // clear counter.
		LeaveCriticalSection(&critsect); // unlock it.
		fprintf (fi, "\n");
    }
    if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
	 {
	    // Send_SET_AIR_VALVE_EN_Message(0,1);
	    // uResult = CPort->WriteToPort(IRISbuffer, 5);
	    // uResult= TxData(1, (char*)IRISbuffer, 5);
	    // printf ("Time: %ld. WriteToPort: %ld bytes\n",Get1msTimeMS(), uResult);
	    LastTimeInMS = Get1msTimeMS();
    }
	// control of endless loop (may be also in monitor.cpp)
	//RValue=monitor(DispSync);

  if (kbhit())  // has anything been pressed from keyboard ?
	 {
        MainNewChar=(unsigned char)getch();
	    if ((MainNewChar & 0xff) == 24)  // CTRL-X   pressed
		{
        	    repeat = 0; // END mark
		}
	 }
  }

#ifdef USE_OUTPUT_FILE
 fprintf(fi, "\nEnd time: %d\n", Get1msTimeMS());
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

 printf ("\nApplication complete.\n");

}

/********************************************************************
  Declaration: This would be a thread for serial port receiving info.
  Call:
  Input:
  Returns:
  23.10.2006 Initial codin - YS.
*********************************************************************/
void thReadSerialPort(void *dummy )
{
  int PortNumber = 1;
	printf ("ComSerialPort thread started.\n");

	InitSerialPorts(3);

	while ( repeat  )
    {
        EnterCriticalSection(&critsect);
        //**********************************
		NbrOfReadBytes = ReadRxData(PortNumber, ReceiveBuffer);
		//printf ("NbrOfReadBytes: %d\n", NbrOfReadBytes);
		//**********************************
        LeaveCriticalSection(&critsect);
    }

	RemoveSerialPortFromPoll();
	printf ("ComSerialPort thread stop.\n");
	_endthread();
}


/* CheckKey - Thread to wait for a keystroke, then clear repeat flag. */
void TheIncrement(void *dummy )
{
  printf ("TheIncrement thread started.\n");
	while ( repeat  )
    {
      i++;
		  //for ( i = 0; i < 5; i++ ) a[ i ] = num;
      //num++;
    }
	printf ("TheIncrement thread stop.\n");

}

/* CheckKey - Thread to wait for a keystroke, then clear repeat flag. */
void CheckKey( void *dummy )
{
    printf ("CheckKey thread started.\n");
	_getch();
    repeat = 0;    /* _endthread implied */
	printf ("CheckKey thread stop.\n");
}

/* Bounce - Thread to create and and control a colored letter that moves
 * around on the screen.
 *
 * Params: ch - the letter to be moved
 */
void Bounce( void *ch )
{
    /* Generate letter and color attribute from thread argument. */
    char    blankcell = 0x20;
    char    blockcell = (char) ch;
    BOOL    first = TRUE;
    COORD   oldcoord, newcoord;
    DWORD   result;


    /* Seed random number generator and get initial location. */
    srand( _threadid );
    newcoord.X = GetRandom( 0, csbi.dwSize.X - 1 );
    newcoord.Y = GetRandom( 0, csbi.dwSize.Y - 1 );
    while( repeat )
    {
        /* Pause between loops. */
        Sleep( 10L );

        /* Blank out our old position on the screen, and draw new letter. */
        if( first )
            first = FALSE;
        else
        {
            WriteConsoleOutputCharacter( hStdOut, &blankcell, 1, oldcoord, &result );
            WriteConsoleOutputCharacter( hStdOut, &blockcell, 1, newcoord, &result );
        }

        /* Increment the coordinate for next placement of the block. */
        oldcoord.X = newcoord.X;
        oldcoord.Y = newcoord.Y;
        newcoord.X += GetRandom( -1, 1 );
        newcoord.Y += GetRandom( -1, 1 );

        /* Correct placement (and beep) if about to go off the screen. */
        if( newcoord.X < 0 )
            newcoord.X = 1;
        else if( newcoord.X == csbi.dwSize.X )
            newcoord.X = csbi.dwSize.X - 2;
        else if( newcoord.Y < 0 )
            newcoord.Y = 1;
        else if( newcoord.Y == csbi.dwSize.Y )
            newcoord.Y = csbi.dwSize.Y - 2;

        /* If not at a screen border, continue, otherwise beep. */
        else
            continue;
        //Beep( ((char) ch - 'A') * 100, 175 );
    }
    /* _endthread given to terminate */
	printf ("Bounce: endthread\n");
    _endthread();
}
