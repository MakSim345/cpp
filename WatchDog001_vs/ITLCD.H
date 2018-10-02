#ifndef ItlcdH
#define ItlcdH

#define VC6

#include <windows.h>

#define C12_PROCENT_THROTTLE  0x12
#define C25_PROCENT_THROTTLE  0x14
#define C37_PROCENT_THROTTLE  0x16
#define C50_PROCENT_THROTTLE  0x18
#define C62_PROCENT_THROTTLE  0x1A
#define C75_PROCENT_THROTTLE  0x1C
#define C87_PROCENT_THROTTLE  0x1E
#define C100_PROCENT_THROTTLE 0x10
#define DISABLE_THROTTLE      0x00

#define BLK_ON                0x01
#define BLK_OFF               0x00

#define LCDVCC_ON             0x01
#define LCDVCC_OFF            0x00

#define LCDVCC3               0x00
#define LCDVCC5               0x01

#define LCDVCC3               0x00
#define LCDVCC5               0x01


#define TxDE_DISABLE          0x00
#define TxDE_DTR1             0x01
#define TxDE_nDTR1            0x02
#define TxDE_RTS1             0x03
#define TxDE_nRTS1            0x04
#define TxDE_ENABLE           0x05
#define TxDE_FPGA_LOCK_REG_BIT_1    0x06

#define CTSE_DISABLE          0x00
#define CTSE_DTR1             0x01
#define CTSE_nDTR1            0x02
#define CTSE_RTS1             0x03
#define CTSE_nRTS1            0x04
#define CTSE_ENABLE           0x05
#define CTSE_FPGA_LOCK_REG_BIT_0    0x06

#define ENABLE_RS422          0x01
#define ENABLE_RS485          0x02
#define ENABLE_RS232          0x03


#define ms 0x00
#define sec   0x01
#define min   0x02
#define hour  0x03


#define Sensor_Diode    0x01
#define Sensor_Resistor 0x02


#define Std_St_786  0x01  //786LCD/S,786LCD/3.5ST,786LCD/ST,786LCD/MG
#define Etx_786     0x02  //ETXplus-786LCD,ETX+-786LCD
#define GX1         0x04  //GX1LCD/S,GX1LCD/S PLUS,GX1LCD/3.5" PLUS,GX1LCD/3.5" STANDARD.
#define LB          0x08  //786LCD/5.25" PLUS
#define _886ATX     0x10  //886LCD/ATX,886LCD/ATX(GE),886LCD/ATXU,886LCD/ATX(GV)
#define _886_Flex   0x11  //886LCD-M/Flex,886LCD/mITX,886LCD-M/ATX
#define _889        0x12  //889LCD/ATX
#define _889U       0x13  //889LCD/ATXU
#define _786Mitx    0x14  //786LCD-M/Itx
#define _986Mitx    0x15  //986LCD-M/Itx
#define _965	    0x16  //KT965G product family


#define SUS_S3 0x00000001
#define SUS_S4 0x00000002


#define SUS_LIB_ERROR                  0x00000001
#define SUS_TIMER_ERROR                0x00000002
#define SUS_S4_ERROR                   0x00000004
#define SUS_S3_ERROR                   0x00000008
#define SUS_TYPE_UNKNOWN_ERROR         0x00000010
#define SUS_MIN_TIME_ERROR             0x00000020


#define Manual_Mode 0x00
#define Thermal_Cruise_Mode 0x01
#define Fan_Speed_Cruise_Mode 0x02


#pragma pack(push,1)




typedef struct
{
   DWORD dwAutoWakeup;
   DWORD dwSecToSleep;
   DWORD dwSuspendType;
   DWORD dwResult;
}Suspend;


typedef struct
{
	unsigned char Hour;
	unsigned char Minutes;
	unsigned long Reserved;
	
}RTCTime;

typedef struct
{
	unsigned char  Magicscan[4];
	unsigned char  Infosize;
	unsigned char  Boardinfo;
	unsigned short BIOSmjr;
	unsigned short BIOSmnr;
	unsigned char  PALid;
	unsigned char  Oui_sn_pn[8];
}IIH;


typedef struct
{
   UCHAR IdNum;
   CHAR AttributeName[40];
   UCHAR Value;
   UCHAR ThresHold;
   UCHAR Worst;
   UCHAR Flags;
   UCHAR RawData[6];

}_HDDDataBlock;


typedef struct
{
short int General_configuration;
short int Number_of_logical_cylinders;
short int Specific_configuration;
short int Number_of_logical_heads;
short int Retired1[2];
short int Number_of_logical_sectors_per_logical_track;
short int Reserved_for_assignment_by_the_CompactFlash_Association[2];
short int Retired2;
short int Serial_number[10]; //(20 ASCII characters)
short int Retired3[2];
short int Obsolete;
short int Firmware_revision[4];// (8 ASCII characters)
short int Model_number[20]; //(40 ASCII characters)
short int Reserved;
short int Rest[256];

} _IDentBlock;

typedef struct _HWMON
{

float VCORE;
   float VCOREb;
   float VCC2_5;
   float VCC3;
   float VCC5;
   float V12;
   float SB3;
   float V_12;
   float SB5;
   float VBATT;
   float CPUTemp;
   float FAN;
   float BoardTemp;
   float Reserved1;
   float Reserved2;
   float Reserved3;
   float Reserved4;
   float Reserved5;
   float Reserved6;

} HWMON;

#pragma pack(pop)

// Import from Itlcd.dll

#ifndef VC6

#define EXT extern "C" __stdcall
#define IMP __import

#else

#define EXT
#define IMP

#endif 



EXT DWORD IMP OpenItlcd(VOID);
EXT DWORD IMP CloseItlcd(VOID);

EXT DWORD IMP ReadMonitor(HWMON *Mon);
EXT DWORD IMP SetClrGPIO(BOOL SetClr,UCHAR GPIO);
EXT DWORD IMP ReadGPIO(UCHAR GPIO);
EXT DWORD IMP SetGPIODir(UCHAR GPIO);
EXT DWORD IMP SetFanSpeed(UCHAR Speed);
EXT DWORD IMP EnableWD(VOID);
EXT DWORD IMP DisableWD(VOID);
EXT DWORD IMP SetWDTimer(UCHAR Time);
EXT DWORD IMP SetWDTimerInterval(UCHAR VAL);
EXT DWORD IMP SetCPUThrottle(UCHAR DUTY);
EXT DWORD IMP SetBKLControl(DWORD Value);
EXT DWORD IMP SetLCDVCCControl(BOOL ON_OFF);
EXT DWORD IMP SetLCDVCC(BOOL VCC5_VCC3);
EXT DWORD IMP SetSerialInterface(UCHAR INTERFACE);
EXT DWORD IMP SetSerialInterfaceDataControl(UCHAR PIN);
EXT DWORD IMP SetSerialInterfaceControl(UCHAR PIN);
EXT DWORD IMP ReadBoardHeader(PVOID Buffer);
EXT DWORD IMP SelectFanTempTacChannel(UCHAR Channel);
EXT DWORD IMP SelectFanTempTacChannelType(UCHAR Type);
EXT DWORD IMP GetBoardType(void);
EXT DWORD IMP GetIntruderStatus(PULONG Status);
EXT DWORD IMP ClrIntruderStatus(void);
EXT DWORD IMP StartThermalCruise(void); 
EXT DWORD IMP GetIdentBlock(int DriveId,_IDentBlock *IDentBlock);
EXT DWORD IMP GetIDCount(UCHAR DriveNo);
EXT DWORD IMP GetHDDAttributes(int DriveNo,_HDDDataBlock *pHDDDataBlock,DWORD dwIDCount);
EXT DWORD IMP GetMac(UCHAR nMac,PVOID Buffer);
EXT DWORD IMP SetGamma(DWORD level);
EXT DWORD IMP SetRTCWake(PVOID Buffer); //Note: Not implemented
EXT DWORD IMP DoSuspend(Suspend *ptrSuspend);

EXT DWORD SetFanTarget(UCHAR ucStt);
EXT DWORD SetFanMode(UCHAR ucSfm);


EXT UCHAR SmBus_RecvByte(UCHAR ucDevAddr);
EXT UCHAR SmBus_ReadBlock(UCHAR ucDevAddr,UCHAR ucCommandCode,UCHAR ucByteCnt,UCHAR *ucpDataBuf);
EXT USHORT SmBus_ReadWord(UCHAR ucDevAddr,UCHAR ucCommandCode);
EXT UCHAR SmBus_ReadByte(UCHAR ucDevAddr,UCHAR ucCommandCode);
EXT void SmBus_SendByte(UCHAR ucDevAddr,UCHAR ucCommandCode);
EXT void SmBus_WriteBlock(UCHAR ucDevAddr,UCHAR ucCommandCode,UCHAR ucByteCnt,UCHAR *ucpDataBuf);
EXT void SmBus_WriteWord(UCHAR ucDevAddr,UCHAR ucCommandCode,USHORT usData);
EXT void SmBus_WriteByte(UCHAR ucDevAddr,UCHAR ucCommandCode,UCHAR usData);
EXT USHORT SmBus_PorcessCall(UCHAR ucDevAddr,UCHAR ucCommandCode,USHORT usData);
EXT void  GetRAIDStatusMessage(INT Nr,CHAR *Message);



//extern "C" __stdcall DWORD __import


#endif
