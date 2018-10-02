/************************************************************************

   Description:   Generally used things (variables, definitions, ...)
   File:          GLOBALS.H
   Language:      Borland C++ 3.0
   Original:      30.10.2001 JK: Initial coding

 *************************************************************************/
#ifndef _ERROR_H_
#define _ERROR_H_

#define MAX_NUMBER_OF_ERRORS 100

// error Types

//FATAL_ERROR   : system does not work at all. Unrecoverable.
//SEVERE_ERROR  : part of the system unrecoverable but partly OK
//NORMAL_ERROR  : user should be informed immediately, but system
//                still might work almost correctly.
//WARNING       : user should be informed, but not immediately.
//                System might work as it should.
//INFO          : only information for user


// Fatal error codes   (1-4999)

#define FATAL_ERROR001   1  // No serial ports found
#define FATAL_ERROR002   2  // No data from GPS 1  in 10 seconds
#define FATAL_ERROR003   3  // No data from S200 in 10 seconds
#define FATAL_ERROR004   4  // rtd.ini can not be opened
                            // second par defines ports in binary
#define FATAL_ERROR005   5  // No data from host in 10 seconds
#define FATAL_ERROR006   6  // No data from GPS 2 in 10 seconds
#define FATAL_ERROR007   7  // No data from BT in 10 seconds
#define FATAL_ERROR008   8  // No data from BaseStation in 10 seconds

// Severe error codes  (5000-9999)

#define SEVERE_ERROR001   5000  // can't read com setting for port(s)
#define SEVERE_ERROR002   5001  // No data from PLC in 10 s
#define SEVERE_ERROR003   5002  // Can't read yard.txt file
#define SEVERE_ERROR004   5003  // Can't open port (number of port,stage)
#define SEVERE_ERROR005   5004  // Can't load port settings (number of port,0)
#define SEVERE_ERROR006   5005  // Can't set lpt1 interrupt handler

// Normal error codes  (10000-14999)

#define NORMAL_ERROR001 10000  // Parity error (port,value)
#define NORMAL_ERROR002 10001  // Illegal nbr of data bits (port,value)
#define NORMAL_ERROR003 10002  // Illegal nbr of stop bits (port,value)
#define NORMAL_ERROR004 10003  // Illegal baud rate (port,value)
#define NORMAL_ERROR005 10004  // Gyro Initialization error (phase,code)
#define NORMAL_ERROR006 10005  // No data from GYRO in 10 s

// Warning codes  (15000-19999)

#define WARNING001      15000 // Too long or short  time slice
                               // Par1 (shortest), par2 (longest)
#define WARNING002      15001 // Can't read MaxDev from ini-file
#define WARNING003      15002 // Can't read DR data from ini-file
                              // par2=1 (low trav dist), par2=2 (high
                              // trav dist), par2=3 (pulses per meter)
                              // par2=4 (pulses slow)
#define WARNING004      15003 // Can't read gyro data from ini-file
#define WARNING005      15004 // Dreckoning reset (distance jump,par2)
#define WARNING006      15005 // Dreckoning reset (gyro jump,par2)
#define WARNING007      15006 // Can't read com port number data from
                              // ini-file
#define WARNING008      15007 // Error in received packet from
                              // OMRON (last,RecvPtr)
#define WARNING009      15008 // Can't read window data from ini-file
                              // (par2 : window number)
#define WARNING010      15009 // Can't read data Satel Data
                              // (par2 : window number)
#define WARNING011      15010 // Can't read data TIF Data
                              // (par2 : data  number)
#define WARNING012      15011 // Error in received COSMOS packet from
                              // HOST (last,last read CRC)
#define WARNING013      15013 // Can't read GPS_TIMEOUT from ini-file
                              //
#define WARNING014      15014 // Can't read ANALOG_FREQUENCY from ini-file                              
#define WARNING015      15015 // Can't read ANALOG_MESSAGE from ini-file
#define WARNING016      15016 // Can't read DISPLAY from ini-file
#define WARNING017      15017 // Can't read FAKE_ANALOG from ini-file
#define WARNING018      15018 // Can't read TEST from ini-file
#define WARNING019      15019 // Can't read PING_SAV from ini-file
#define WARNING020      15020 // Can't read AllTraceToFile from ini-file
#define WARNING021      15021 // Can't read AllTraceToComport from ini-file
#define WARNING022      15022 // Can't read TIME_STAMP_LOG from ini-file
#define WARNING023      15023 // Can't read TEST_RNG_MESSAGE from ini-file
#define WARNING024      15024 // Can't read RND_COM_PORT from ini-file
#define WARNING025      15025 // Can't read RND_MESSAGE_SIZE from ini-file
#define WARNING026      15026 // Can't read FREQUENCY from ini-file
#define WARNING027      15027 // Can't read GPS_COM3_TEST from ini-file
#define WARNING028      15028 // Can't read RelLog from ini-file

// Info codes    (20000-)

#define  INFO001   20000  // Number of COM ports found at bootup
#define  INFO002   20001  // COM1 address (0 if nonexistent)
#define  INFO003   20002  // COM2 address (0 if nonexistent)
#define  INFO004   20003  // COM3 address (0 if nonexistent)
#define  INFO005   20004  // COM4 address (0 if nonexistent)
#define  INFO006   20005  // COM5 address (0 if nonexistent)
#define  INFO007   20006  // COM6 address (0 if nonexistent)
#define  INFO008   20007  // COM1 active/deactive, type
#define  INFO009   20008  // COM2 active/deactive, type
#define  INFO010   20009  // COM3 active/deactive, type
#define  INFO011   20010  // COM4 active/deactive, type
#define  INFO012   20011  // COM5 active/deactive, type
#define  INFO013   20012  // COM6 active/deactive, type
#define  INFO014   20013  // Receive break from GPS 1 (last,current)
#define  INFO015   20014  // Receive break from S200(last,current)
#define  INFO016   20015  // Receive break from Gyro (last,current)
#define  INFO017   20016  // Receive break from PLC(last,current)
#define  INFO018   20017  // Receive break from HOST(last,current)
#define  INFO020   20019  // Receive break from GPS 2 (last,current)

#define  INFO021   20020  // Receive break from BaseStation(last,current)
#define  INFO022   20021  // Receive break from BT port (last,current)
#define  INFO023   20022  // Receive break from -
#define  INFO024   20023  // Receive break from -




typedef struct
 {
 unsigned int Code;
 unsigned char Priority;  //  0 is highest , 255 lowest
 long Par1;
 long Par2;
 unsigned int Counter;
 long Time ;  // in seconds after last bootup
 }error_type;

//////////////////////////////////
// Error window drawing; Here we define errors, which are shown to user.
typedef struct
{
  int Active;
} err_wnd_type;

#define GYRO_ERRORBOX_STR "Gyro"
#define GPS_ERRORBOX_STR "Gps"
#define LAN_ERRORBOX_STR "Lan"
#define BT_ERRORBOX_STR "BT"
#define INI_ERRORBOX_STR  "INI"
#define PULSEL_ERRORBOX_STR "PulseL"
#define PULSER_ERRORBOX_STR "PulseR"
#define PULSEQ_ERRORBOX_STR "PulseQ"
#define HOST_ERRORBOX_STR "Host"

#define GYRO_ERRORBOX_INDEX 0
#define GPS_ERRORBOX_INDEX 1
#define LAN_ERRORBOX_INDEX 2
#define BT_ERRORBOX_INDEX 3
#define INI_ERRORBOX_INDEX 4
#define PULSEL_ERRORBOX_INDEX 5
#define PULSER_ERRORBOX_INDEX 6
#define PULSEQ_ERRORBOX_INDEX 7
#define HOST_ERRORBOX_INDEX 8

extern const char ErrorText[][10];

////////////////////////////////

typedef struct
 {
 unsigned int Code;
 unsigned int Counter;
 long Time;  // time of last removal
 }rstack_type;


// prototypes

void AddError(unsigned int,unsigned char,long,long);
void RemoveError(unsigned int);
void InitErrorHandler();
int ActiveIniWarnings();





#endif// _ERROR_H_
