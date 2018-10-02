//============================================================
//
// Description:
// Tracing and debugging macros
//
// Usage:
// DEB_TRACES definition activates traces
// ASSERT and VERIFY are both compiled to debug build
// VERIFY's test assignment is compiled also to release
//
//============================================================

#ifndef _TIME_H_
#define _TIME_H_

// #include "opsyslib.h"
#include <Windows.h>

// forward declarations
enum UNIT_CLOCK;        // these are forward declared to keep an include
enum MONTH;             // of ProductConfigBase.h out of opsyslib.h

/****************************************
** Author:  
** Purpose:   All data related to a specific time and date
** Comments:  
****************************************/
struct STime
{
	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned long hour;
	unsigned long minute;
	unsigned long second;
};

// Enum for -Unit Clock-
typedef enum UNIT_CLOCK
{
	UNIT_CLOCK_24_H,
	UNIT_CLOCK_12_H,
	UNIT_CLOCK_MAX
}UNIT_CLOCK;

/****************************************
** Author:  
** Purpose:   All time related functions
** Comments:  
****************************************/
class DOTime
{
public:

    // get local time
    static void GetLocalTime(STime &time);
    static unsigned long GetLocalTime();

    // set local time
    static bool SetLocalTime(const STime &time);

    // conversion methods
    static unsigned long ConvertTime(const STime &time);
    static void ConvertTime(unsigned long secSince1970, STime &time);

    // get number of msec since the os started
    static unsigned long GetTickCount();


    // Returns the difference between 2 tick count values, taking into account timer wrap-around.
    static unsigned long TickCountDiff( unsigned long earlierTime, unsigned long laterTime );

    // Returns the difference between the specified tick count and the current system tick count,
    //  taking into account timer wrap-around.
    static unsigned long TickCountDiff( unsigned long earlierTime );

    // format the time/date as a string
    static void GetTimeString(const STime &time, UNIT_CLOCK clockFormat, bool showSeconds,
                              LPTSTR timeString, unsigned long bufferSize);
    static void GetTimeString(unsigned long secSince1970, UNIT_CLOCK clockFormat,
                              bool showSeconds, LPTSTR timeString, unsigned long bufferSize);

    static void GetDateString(const STime &time, LPTSTR dateString, unsigned long bufferSize,
                              bool showYear = true, bool showDashes = true);
    static void GetDateString(unsigned long secSince1970, LPTSTR dateString,
                              unsigned long bufferSize, bool showYear = true, bool showDashes = true); 

	// Control access to RTC & CMOS memory
    static bool LockTimeAccess();
    static bool UnlockTimeAccess();

    // Method to convert between file time and unsigned long, its public because
    // other opsyslib classes need access to it
    static unsigned long FileTimeToUnsignedLong(const FILETIME &fileTime);

    // miscellaneous time related constants
    static const unsigned long MS_PER_TICK_COUNT;
    static const unsigned long MS_PER_SECOND;
    static const unsigned long SECONDS_PER_MINUTE;
    static const unsigned long MINUTES_PER_HOUR;
    static const unsigned long SECONDS_PER_HOUR;

private:

    // not implemented
    DOTime();
    virtual ~DOTime();
	DOTime( const DOTime&);
	DOTime& operator = (const DOTime&);

    // set time offset since the os started
	// This is intended to be used only for unit test purposes	
	static void SetTickCount(unsigned long tickCount);

    // helper methods used for conversion between structured
    // time and time as seconds since 1970

    static void UnsignedLongToFileTime(unsigned long t, LPFILETIME pft);
    static void SystemTimeToSTime(const SYSTEMTIME &sysTime, STime &time);
    static void STimeToSystemTime(const STime &time, SYSTEMTIME &sysTime);

    // mutex used to limit access to methods that access the RTC
    // under CE, the application used a software RTC that is not thread safe
    // static DOMutex m_timeAccessMutex; 
	friend void SWWatchDogUnitTestSetTickCount(unsigned long tickCount);

	// Number of set and get retries before SetLocalTime() fails
	static const long SET_LOCAL_TIME_RETRIES;

	// Maximum time set and get difference before SetLocalTime() fails
	static const long SET_TIME_DIFF_MAX;
};

#endif // _TIME_H_
