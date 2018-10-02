
/*********************************************************************

  gps.cpp
  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  31.10.2000 Initial coding
 **********************************************************************/

#include <stdio.h>
#include <dos.h>
#include <time.h>
#include <conio.h>
//#include <io.h>
//#include <allegro.h>

#include "gen.h"
//#include "globals.h"
#include "utils.h"
#include "error.h"

#define RSTACK_SIZE 30


error_type ErrStack[MAX_NUMBER_OF_ERRORS];
rstack_type RemovedErrorsStack[RSTACK_SIZE];
//err_wnd_type ErrWnd[10];

int EStackPtr=0;  // Error stack pointer
int RStackPtr=0;  // Removed Errors Stack Pointer

const char ErrorText[][10] = {GYRO_ERRORBOX_STR, GPS_ERRORBOX_STR, LAN_ERRORBOX_STR,
                              BT_ERRORBOX_STR,INI_ERRORBOX_STR,PULSEL_ERRORBOX_STR,
                              PULSER_ERRORBOX_STR,PULSEQ_ERRORBOX_STR,HOST_ERRORBOX_STR};


/********************************************************************

  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  Declaration: Add a new error (or increment old)to Error Stack
  Call: void AddError(Code,Priority, Par1, Par2)
  Input: unsigned int Code,unsigned char Priority,
         long Par1, long Par2
  Returns:
  04.12.2000 Initial coding

*********************************************************************/

  void  AddError(unsigned int Code,unsigned char Priority,
                 long Par1,long Par2)


   {
   //int i;
   int ErrFound=FALSE;
/*
   NO_INTERRUPTS (

   // Find if error already active

   for (i=0; i <= EStackPtr;i++)
     {
     if (ErrStack[i].Code == Code)
       {
       ErrStack[i].Counter++;  // Increment counter only
       ErrFound=TRUE;
       break;
       }
     }

   if (!ErrFound)
     {
     // add new error to stack
     ErrStack[EStackPtr].Code=Code;
     ErrStack[EStackPtr].Priority=Priority;
     ErrStack[EStackPtr].Par1=Par1;
     ErrStack[EStackPtr].Par2=Par2;
     ErrStack[EStackPtr].Counter=0;  // new error !
     ErrStack[EStackPtr].Time=Get1msTime();
     EStackPtr++;
     }

   )  // end of NO_INTERRUPT

	*/
}
/********************************************************************

  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  Declaration: Remove error from Error Stack
  Call: void RemoveError(ErrorCode)
  Input: unsigned int ErrorCode
  Returns:
  08.12.2000 Initial coding

*********************************************************************/

  void RemoveError(unsigned  int  ErrorCode)
   {
   int i,j;
   int RErrFound=FALSE;

   for (i=0; i <= EStackPtr; i++)
     {
     if (ErrStack[i].Code == ErrorCode)
       {
       for (j=i;j<=EStackPtr;j++)
         {
         ErrStack[j]=ErrStack[j+1];
         }
       ErrStack[j+1].Code=0;
       ErrStack[j+1].Priority=0;
       ErrStack[j+1].Par1=0;
       ErrStack[j+1].Par2=0;
       ErrStack[j+1].Counter=0;
       ErrStack[j+1].Time=0;
       EStackPtr--;
       break;
       }
     }

   // find if  error has been removed before

   for (i=0; i<=RStackPtr;i++)
     {
     if (RemovedErrorsStack[i].Code == ErrorCode)
       {
       RemovedErrorsStack[i].Counter++;
       RErrFound=TRUE;
       }
     }

   if (!RErrFound)
     {
     RemovedErrorsStack[RStackPtr].Code=ErrorCode;
     RemovedErrorsStack[RStackPtr].Time=Get1msTime();
     RStackPtr++;
     }


   }



/********************************************************************

  Savcor IT Oy/JLM
  Borland TURBO C++ 3.0
  Declaration: Error handler initialisation
  Call: InitErrorHandler()
  Input:
 Returns:
  04.12.2000 Initial coding

*********************************************************************/

void InitErrorHandler()
{
  int i;
  // reset error stack

  for (i=0;i<MAX_NUMBER_OF_ERRORS;i++)
    {
    ErrStack[i].Code=0;
    ErrStack[i].Priority=0;
    ErrStack[i].Par1=0;
    ErrStack[i].Par2=0;
    ErrStack[i].Counter=0;
    ErrStack[i].Time=0;		
    }

  for (i=0;i<RSTACK_SIZE;i++)
    {
    RemovedErrorsStack[i].Code=0;
    RemovedErrorsStack[i].Counter=0;
    RemovedErrorsStack[i].Time=0;		
    }

  }


// JLM 22.03.2002 in Poland

int ActiveIniWarnings()
{
  unsigned int e;
  for (int i=0; i<EStackPtr;i++)
  {
    e=ErrStack[i].Code;
    if ( 
         (e == WARNING002) || 
         (e == WARNING003) || 
         (e == WARNING004) || 
         (e == WARNING007) || 
         (e == WARNING009) ||
         (e == WARNING010) || 
         (e == WARNING011)
       )
    {
      return(TRUE);
    }
  }
  return(FALSE);
}