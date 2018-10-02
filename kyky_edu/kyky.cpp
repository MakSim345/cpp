/*****************************************************************
 *
 * KuKu Clock
 * 
 * Descr  :: Program goal is to scare the user as hard as 
 *           it is just possible. Each hour cd-rom opens for XX
 *           times and PC sais "KuKu!", where XX is the hour.
 *
 ****************************************************************/
#include "gen.h"
#include "kyky.h"

#include <windows.h>
#include <mmsystem.h>
//#include "resource.h"

// Function that sais "KuKu!" for XX times
void kuku( int kukus ) 
{
    // Using strings to send commands to out cd-rom
    LPCTSTR command_door_open    = "set cdaudio door open";
    LPCTSTR command_door_close    = "set cdaudio door closed";

    // Making the "KuKu!"
    for ( int i = 0; i < kukus; i++ ) 
    {
        mciSendString( command_door_open, 0, 0, 0 );            // open tray
        PlaySound( "KuKu", 0, SND_RESOURCE | SND_ASYNC );        // play sound
        mciSendString( command_door_close, 0, 0, 0 );            // close tray
    }
}

// Main Program Code
int __stdcall WinMain( HINSTANCE hModule, HINSTANCE, LPSTR , int ) 
{

    SYSTEMTIME the_now;                // getting current time here
    int    hours;                        // count of "hours" for the "now"
    int time_to_sleep;                // seconds to sleep until the next hour
    
    // Start Working
    // The Main Cycle of Time Counting
    while (1) 
    {        
        // What's the time?..
        GetSystemTime(&the_now);
        
        if (the_now.wMinute == 0) 
        {
            // The time is xx.00 =)
            hours = the_now.wHour;
            if (hours > 12) hours -= 12;
            // Let's say KuKu!)
            kuku(hours);
            // Sleep for approximately an hour
            Sleep(3580000);
        }
        else if (the_now.wMinute == 59) 
        {
            // On the last minute it's time to be worried
            // or to be really worried ...
            if (the_now.wSecond < 55) 
            {
                Sleep(5000);
            }
            else
            {
                Sleep(250);
            }
        } 
        else 
        {
            // When starting, fall asleep until the time comes
            time_to_sleep = (59 - the_now.wMinute) * 60;
            Sleep(time_to_sleep);    
        }
    }
    return 0;
}
// end :: main
//

// end. =)
// That's all, folks!)
