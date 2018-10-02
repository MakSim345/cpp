#include "stdafx.h"
#include "Time.h"
#include <limits.h>

#ifdef YS_TEST_DEFINITON_12312399
//#include "DOLimits.h"
//#include "ProductConfigBase.h"
//#include "Localization.h"

// Miscellanous time related constants
const unsigned long DOTime::MS_PER_TICK_COUNT = 1;
const unsigned long DOTime::MS_PER_SECOND = 1000;
const unsigned long DOTime::SECONDS_PER_MINUTE = 60;
const unsigned long DOTime::MINUTES_PER_HOUR = 60;
const unsigned long DOTime::SECONDS_PER_HOUR = SECONDS_PER_MINUTE*MINUTES_PER_HOUR;


// This is the number of 100 nanosecond intervals between 1601 and 1970.
// It is used to convert between the FILETIME structure and an unsigned long value
const ULONGLONG TIME_DIFF = 116444736000000000;

// This is used to convert from 100 nanosecond intervals to seconds
const unsigned long TIME_DIVIDER = 10000000;

// name of mutex
//const TCHAR* SYSTEM_TIME_ACCESS_MUTEX = _T("SystemTimeAccessMutex");
//DOMutex DOTime::m_timeAccessMutex(false, SYSTEM_TIME_ACCESS_MUTEX);

// This is the tick count offset from OS GetTickCount() api 
// Used by DOTime::Set/GetTickCount() to facilitate roll-over testing
static unsigned long m_startingTickCount = 0;

// Number of set and get retries before SetLocalTime() fails
const long DOTime::SET_LOCAL_TIME_RETRIES = 5;

// Maximum time set and get difference before SetLocalTime() fails
const long DOTime::SET_TIME_DIFF_MAX = 10;

/****************************************
** Author:    
** Purpose:   Get the current local time in a structured format
** Comments:  
****************************************/
void DOTime::GetLocalTime(STime &time)
{
    SYSTEMTIME systemTime;
    //m_timeAccessMutex.Lock();
    __try
    {
        ::GetLocalTime(&systemTime);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // Not much can be done here, but the exception must
        // at least be caught so that it does not propogate.
        memset(&time, 0, sizeof(STime));
    }
    //m_timeAccessMutex.Unlock();
    SystemTimeToSTime(systemTime, time);
}


/************************************************
** Author:    
** Purpose:   This returns the same value that time() function would return.
              Unfortunately, that function is not supported in WinCE.
**            So for both WinCE and WinNT.  The system
**            time will be coverted to an unsigned long value
** Comments:  Returns seconds since Jan 1, 1970
*************************************************/
unsigned long DOTime::GetLocalTime()
{
    FILETIME fileTime;
    SYSTEMTIME systemTime;

    //m_timeAccessMutex.Lock();
    __try
    {
        ::GetLocalTime(&systemTime);
        //m_timeAccessMutex.Unlock();
        ::SystemTimeToFileTime(&systemTime, &fileTime);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        //m_timeAccessMutex.Unlock();
        return 0;
    }
    return FileTimeToUnsignedLong(fileTime);
}


/****************************************
** Author:    
** Purpose:   Set the current system time
** Comments:  Must confirm that date/time is actually  
**            set due to SC520 HW RTC problems 
****************************************/
bool DOTime::SetLocalTime(const STime &time)
{
    SYSTEMTIME systemTime;
    bool isSuccessful = false;
    STimeToSystemTime(time, systemTime);
    
    long retryCount = 0;
    unsigned long setTime = ConvertTime(time);

    //m_timeAccessMutex.Lock();
    __try
    {
        //  Retry if either SetLocalTime() fails or 
        //  the time that is read is out-of-range
        while( retryCount < SET_LOCAL_TIME_RETRIES )
        {
             //  Only check actual time if set time works 
            if( ::SetLocalTime(&systemTime) == TRUE )
            {
                //  Break out if set time is in range
                if( (GetLocalTime() - setTime) <= SET_TIME_DIFF_MAX )
                {
                    isSuccessful = true;
                    break;
                }
            }
            retryCount++;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // Not much can be done here, but the exception must
        // at least be caught so that it does not propogate.
        isSuccessful = false;
    }
    //m_timeAccessMutex.Unlock();
    return isSuccessful;
}


/****************************************
** Author:    
** Purpose:   Converts a time in a structure format to the number of 
**            seconds since 1970.
** Comments:  
****************************************/
unsigned long DOTime::ConvertTime(const STime &time)
{
    FILETIME fileTime;
    SYSTEMTIME systemTime;
    STimeToSystemTime(time, systemTime);
    __try
    {
        ::SystemTimeToFileTime(&systemTime, &fileTime);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // Not much can be done here, but the exception must
        // at least be caught so that it does not propogate.
        return 0;
    }
    return FileTimeToUnsignedLong(fileTime);
}


/****************************************
** Author:    
** Purpose:   Converts a time as the number of seconds since 1970
              to a structured format
** Comments:  
****************************************/
void DOTime::ConvertTime(unsigned long secSince1970, STime &time)
{
    FILETIME fileTime;
    SYSTEMTIME systemTime;
    UnsignedLongToFileTime(secSince1970, &fileTime);
    __try
    {
        ::FileTimeToSystemTime(&fileTime, &systemTime);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // Not much can be done here, but the exception must
        // at least be caught so that it does not propogate.
        memset(&time, 0, sizeof(STime));
    }
    SystemTimeToSTime(systemTime, time);
}


/************************************************
** Author:    
** Purpose:   Formats a string with the time
** Comments:  
*************************************************/
void DOTime::GetTimeString(const STime &time, UNIT_CLOCK clockFormat, bool showSeconds,
                           LPTSTR timeString, unsigned long bufferSize)
{
    if (timeString == NULL)
        return;

    __try
    {
        if (clockFormat == UNIT_CLOCK_12_H)
        {
            unsigned long hour = 0;
            if (time.hour == 0)
                hour = 12;
            else if (time.hour > 12)
                hour = time.hour - 12;
            else
                hour = time.hour;

            if (showSeconds)
                _sntprintf(timeString, bufferSize, _T("%.2d:%.2d:%.2d"), hour, time.minute, time.second);
            else
                _sntprintf(timeString, bufferSize, _T("%.2d:%.2d"), hour, time.minute);
        }
        else if (clockFormat == UNIT_CLOCK_24_H)
        {
            if (showSeconds)
                _sntprintf(timeString, bufferSize, _T("%.2d:%.2d:%.2d"), time.hour, time.minute, time.second);
            else
                _sntprintf(timeString, bufferSize, _T("%.2d:%.2d"), time.hour, time.minute);
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        timeString[0] = '\0';
    }

    timeString[bufferSize-1] = _T('\0');
}


/****************************************
** Author:    
** Purpose:   Save as above but for secsSince1970
** Comments:  
****************************************/
void DOTime::GetTimeString(unsigned long secSince1970, UNIT_CLOCK clockFormat,
                           bool showSeconds, LPTSTR timeString, unsigned long bufferSize)
{
    STime structTime;
    ConvertTime(secSince1970, structTime);
    GetTimeString(structTime, clockFormat, showSeconds, timeString, bufferSize);
}


/************************************************
** Author:    
** Purpose:   Formats a string with the date
** Comments:  
*************************************************/
void DOTime::GetDateString(const STime &time, LPTSTR dateString, unsigned long bufferSize,
                           bool showYear /*= true*/, bool showDashes /*= true*/)
{
    if (dateString == NULL)
        return;

	SYSTEMTIME systemTime;
    STimeToSystemTime(time, systemTime);

    __try
    {
        if (showYear == true)
        {
            if (showDashes == true)
                ::GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &systemTime, _T("dd'-'MMM'-'yyyy"),
                                dateString, static_cast<long>(bufferSize));
            else
                ::GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &systemTime, _T("ddMMMyyyy"),
                                dateString, static_cast<long>(bufferSize));
        }
        else
        {
            if (showDashes == true)
                ::GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &systemTime, _T("dd'-'MMM"),
                                dateString, static_cast<long>(bufferSize));
            else
                ::GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &systemTime, _T("ddMMM"),
                                dateString, static_cast<long>(bufferSize));
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        dateString[0] = '\0';
    }
    dateString[bufferSize-1] = _T('\0');
}


/****************************************
** Author:    
** Purpose:   Save as above but for secsSince1970
** Comments:  
****************************************/
void DOTime::GetDateString(unsigned long secSince1970, LPTSTR dateString,
                           unsigned long bufferSize, bool showYear /*= true*/, bool showDashes /*= true*/)
{
    STime structTime;
    ConvertTime(secSince1970, structTime);
    GetDateString(structTime, dateString, bufferSize, showYear, showDashes);
}


/****************************************
** Author:    
** Purpose:   Get the number of tick counts since last power-up
** Comments:  
****************************************/
unsigned long DOTime::GetTickCount()
{
    __try
    {
        return ::GetTickCount() + m_startingTickCount;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return 0;
    }
}

/****************************************
** Author:    
** Purpose:   Set the tick count offset so that roll-over can be tested	
** Comments:  Should only be used for test purposes 
****************************************/
void DOTime::SetTickCount(unsigned long tickCount)
{
    m_startingTickCount = tickCount - ::GetTickCount();
}


/****************************************
** Author:    
** Purpose:   Returns the difference between 2 tick count values, taking into account timer wrap-around.
** Comments:  The earlierTime parameter is assumed to be a tick count value from an earlier point in time
**            than the laterTime parameter value.  If earlierTime has a greater value, it is assumed that
**            the timer has wrapped around between earlierTime and laterTime.
****************************************/
unsigned long DOTime::TickCountDiff( unsigned long earlierTime, unsigned long laterTime )
{
    unsigned long timeDiff;
                
    if ( laterTime < earlierTime )
    {
        // Account for timer wrap.
        timeDiff = (UINT_MAX - earlierTime) + laterTime;
    }
    else
    {
        timeDiff = laterTime - earlierTime;
    }

    return timeDiff;
}

/****************************************
** Author:    
** Purpose:   Returns the difference between the specified tick count and the current system tick count,
**            taking into account timer wrap-around.
** Comments:  The earlierTime parameter is assumed to be a tick count value from an earlier point in time
**            than the current time.  If earlierTime has a greater value than the current tick count,
**            it is assumed that the timer has wrapped around between earlierTime and the current time.
****************************************/
unsigned long DOTime::TickCountDiff( unsigned long earlierTime )
{
    return TickCountDiff( earlierTime, DOTime::GetTickCount() );
}


/****************************************
** Author:    
** Purpose:   Utility function to convert a SYSTEMTIME struct to a STime struct
** Comments:  
****************************************/
void DOTime::SystemTimeToSTime(const SYSTEMTIME &sysTime, STime &time)
{
    time.year = sysTime.wYear;
	time.month = sysTime.wMonth;
	time.day = sysTime.wDay;
	time.hour = sysTime.wHour;
	time.minute = sysTime.wMinute;
	time.second = sysTime.wSecond;
}


/****************************************
** Author:    
** Purpose:   Utility function to convert a STime struct to a SYSTEMTIME struct
** Comments:  
****************************************/
void DOTime::STimeToSystemTime(const STime &time, SYSTEMTIME &sysTime)
{
	sysTime.wDay = static_cast<unsigned short>(time.day);
	sysTime.wHour = static_cast<unsigned short>(time.hour);
	sysTime.wMinute = static_cast<unsigned short>(time.minute);
	sysTime.wMonth = static_cast<unsigned short>(time.month);
	sysTime.wSecond = static_cast<unsigned short>(time.second);
	sysTime.wYear = static_cast<unsigned short>(time.year);
    sysTime.wDayOfWeek = 0;
	sysTime.wMilliseconds = 0;
}


/************************************************
** Author:    
** Purpose:   Utility function from MSDev help
** Comments:  Converts an unsigned long to a FILETIME
*************************************************/
void DOTime::UnsignedLongToFileTime(unsigned long t, LPFILETIME pft)
{
    if (pft != NULL)
    {
        __try
        {
            ULONGLONG ll = UInt32x32To64(t, TIME_DIVIDER) + TIME_DIFF;
            pft->dwLowDateTime = (DWORD) ll;
            pft->dwHighDateTime = static_cast<unsigned long>(ll >>32);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            pft->dwLowDateTime = 0;
            pft->dwHighDateTime = 0;
        }
    }
}


/************************************************
** Author:    
** Purpose:   Utiltity function to convert a file time
**            to an unsigned long value.  This is necessary
**            because WinCE does not support time_t
** Comments:  Derived by "reversing" the one above
*************************************************/
unsigned long DOTime::FileTimeToUnsignedLong(const FILETIME &fileTime)
{
    // Create a 64 bit data type from the file time structure
    ULONGLONG llLow = static_cast<ULONGLONG>( fileTime.dwLowDateTime );
    ULONGLONG llHigh = static_cast<ULONGLONG>(fileTime.dwHighDateTime) << 32;
    ULONGLONG ll = llLow | llHigh;

    // Subtract the time difference (100 ns intervals)
    // of the file time sturcture to the time_t value  
    ll -= TIME_DIFF;

    // Convert to seconds
    ll /= TIME_DIVIDER;

    return static_cast<unsigned long>(ll);
}


/************************************************************************
** Author:    
** Purpose:   Locks access to RTC & CMOS memory
** Comments:  
************************************************************************/
bool DOTime::LockTimeAccess()
{
	return 1;//( m_timeAccessMutex.Lock() );
}

/************************************************************************
** Author:    
** Purpose:   Locks access to RTC & CMOS memory
** Comments:  
************************************************************************/
bool DOTime::UnlockTimeAccess()
{
	return 0;//( m_timeAccessMutex.Unlock() );
}

#endif // #ifdef YS_TEST_DEFINITON_12312399
