#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define TIME_TICK_INTERVAL 1000
#define RND_MAX 65536

// This didn't work:
// #define rdtsc __asm __emit 0fh __asm __emit 031h

#define WIN32_APP

#include <stdio.h>
#include "utils.h"
#include <conio.h>
#include "time.h"
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sys/timeb.h>

#include "TCHAR.h"

using namespace std;

typedef signed char        IntS8;       /* signed 8 bits    */  
typedef unsigned char      IntU8;       /* unsigned 8 bits  */  

#if INT_MAX == 32767
typedef int                IntS16;      /* signed 16 bits    */ 
typedef unsigned int       IntU16;      /* unsigned 16 bits  */
typedef long               IntS32;      /* signed 32 bits    */ 
typedef unsigned long      IntU32;      /* unsigned 32 bits  */ 

#elif INT_MAX == 2147483647             
typedef short              IntS16;      /* signed 16 bits    */ 
typedef unsigned short     IntU16;      /* unsigned 16 bits  */
typedef int                IntS32;      /* signed 32 bits    */ 
typedef unsigned int       IntU32;      /* unsigned 32 bits  */
#endif

/*  64 bit integers done differently by MSVC++. */
#if defined(_MSC_VER)
typedef __int64            IntS64;      /*  signed 64 bits   */
typedef unsigned __int64   IntU64;      /*  unsigned 64 bits */
#elif defined(CADUL) || defined(__GNUC__) || defined(__ICCARM__)
typedef long long int      IntS64;      /*  signed 64 bits   */
typedef unsigned long long int IntU64;  /*  unsigned 64 bits */
#endif

enum
{
    MAX_ALARM_TEXT_LEN = 80,
    MAX_SHORT_ALARM_TEXT_LEN = 13,
    MAX_UTF8_ALARM_TEXT_LEN = 240
};

#define MAX_ALARM_MSG_TEXT_LEN 80

/* Data type declarations */
#define boolean				short		/* Logical boolean */
typedef unsigned char		byte;		/* Unsigned 8-bits */
typedef unsigned short		word;		/* Unsigned 16-bits */
typedef unsigned long		dword;		/* Unsigned 32-bits */

enum dri_alarm_color
{
    DRI_PR0,
    DRI_PR1,
    DRI_PR2,
    DRI_PR3,
    DRI_NR_OF_PRIORITIES
};
typedef short enum_dri_alarm_color;

enum dri_alarm_type
{
    DRI_AL_TYPE_UNKNOWN,
    DRI_AL_TYPE_LOW_LIMIT,
    DRI_AL_TYPE_HIGH_LIMIT,
    DRI_AL_TYPE_STATUS
};
typedef short enum_dri_alarm_type;


struct al_disp_al
{
    char                    text[MAX_ALARM_MSG_TEXT_LEN];
    boolean                 text_changed;
    enum_dri_alarm_color    color;
    boolean                 color_changed;
    char                    format_info;
    byte                    audio_mode;   /* : dri_al_audio_mode; DRI_LEVEL_04 ESP */
    byte                    is_asy;
    byte                    is_apnea;
    word                    alsrc_id;
    enum_dri_alarm_type     alarm_type;
    short                   dev_language; /* Implemented in DRI_LEVEL_00 */
    short                   reserved[1];
};

#define MSF_ASSERT(expr) printf ("%s\n", expr);
/*
(expr)\
{\
    std::cout xStrm;\
    xStrm << __FILE__ << ": "<< __LINE__ << " " << __FUNCTION__ << "(): " << expr;\
}
*/
