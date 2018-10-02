#pragma once

#include "gen.h"
//#include "utils.h"
#include "timectr.h"
//#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>



//#include <stdafx.h>

/********************************************************************

  Declaration: 
  Call: 
  Input:
  Returns:
  01.09.2006 Initial coding

*********************************************************************/
void PrintTimeN(int nCounter)
{

// printf ("PENTIUM time: %d, Counter %d\n", Get1msTime(), nCounter);
static int n_days   = 0;
static int n_hours   = 0;
static int n_minutes = 0;
static int n_seconds = 0;
static int n_millisc = 0;
static int n_milctr  = 0;
static int nBuff     = 0; 
static int nResult   = 0; 
static int nFirstTime= 1;
 
if (nFirstTime == 1)
{
 nFirstTime = 0;
 nBuff = nCounter; 
}

 nResult = nCounter - nBuff;
 nBuff = nCounter; 
 n_millisc = n_millisc + nResult;
 
 if (n_millisc >= 100)
 {  
  n_milctr++;
  n_millisc= 0;
  if (n_milctr >= 10)
  {   
   n_milctr = 0;
   n_seconds++;
   if (n_seconds >= 60)
   {
    n_seconds = 0;
    n_minutes++;
    if (n_minutes >= 60)
    {
     n_minutes = 0;
     n_hours++;
     if (n_hours >= 24)
     {      
      n_hours = 0;
      n_days++;
     }
    }     
   }
  }   
  // _dos (cls);
   // system("cls");
   //printf ("\n\n\n\n\n\n\n\t\t");
   printf ("TIME: %02d D %02d H %02d M %02d S %03d MS ", n_days, n_hours, n_minutes, n_seconds, n_milctr*100);  
 }
 
}

/********************************************************************

  Declaration: 
  Call: 
  Input:
  Returns:
  01.09.2006 Initial coding

*********************************************************************/
void PrintTimeMS(int nCounter)
{

// printf ("PENTIUM time: %d, Counter %d\n", Get1msTime(), nCounter);
static int n_days   = 0;
static int n_hours   = 0;
static int n_minutes = 0;
static int n_seconds = 0;
static int n_millisc = 0;
static int n_milctr  = 0;
static int nBuff     = 0; 
static int nResult   = 0; 
static int nFirstTime= 1;
 
if (nFirstTime == 1)
{
 nFirstTime = 0;
 nBuff = nCounter; 
}
    
 nResult = nCounter - nBuff;
 nBuff = nCounter; 
 n_millisc = n_millisc + nResult;
 
 if (n_millisc >= 100)
 {  
  n_milctr++;
  n_millisc= 0;
  if (n_milctr >= 10)
  {   
   n_milctr = 0;
   n_seconds++;
   if (n_seconds >= 60)
   {
    n_seconds = 0;
    n_minutes++;
    if (n_minutes >= 60)
    {
     n_minutes = 0;
     n_hours++;
     if (n_hours >= 24)
     {      
      n_hours = 0;
      n_days++;
     }
    }     
   }
  }   
  // _dos (cls);
   //system("cls");
   //printf ("\n\n\n\n\n\n\n\t\t");
   printf ("MSTM: %02d days %02d hrs %02d min %02d sec %03d ms ", n_days, n_hours, n_minutes, n_seconds, n_milctr*100);  
 }
 
}

// class CAuto
CAuto::CAuto()
 : m_Color(3)
{

 //m_Color = 3;
 m_HorsePwr = 200;

}

CAuto::~CAuto()
{
 return;
}

void CAuto::Start()
{
    CAuto::m_Speed = 100; 
}

int CAuto::GetAutoColor() const
{
 return m_Color;
}

int CAuto::GetAutoHorsePwr() const
{
 return  m_HorsePwr;
}
