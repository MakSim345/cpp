#if defined TOPPICK

// Frame flags
#define SYNC_FLAG1  0xAA
#define SYNC_FLAG2  0x44
#define SYNC_FLAG3  0x12

#define BESTPOS_MSG  42
#define RANGE_MSG    43
#define RANGECMP_MSG 140
#define BESTXYZ_MSG  241
#define SATXYZ_MSG   270
#define SAV_RNG_MSG  1001
#define RTCM3_MSG    117
#define RTCM59_MSG   116

#define RNG_TMP_BUFF_SIZE 24
#define RNG_BUFF_SIZE 44
#define XYZ_TMP_BUFF_SIZE 68
#define SAV_RNG_TMP_BUFF_SIZE 16

#define MESSG_NUM 4

#define ADRR     0
#define LOCKTIME 1
#define SV_LAST  2 
#define SV_NOW   3

#define MAX_PRN 40
#define L1_WAVELEN (-0.1902936727984)

typedef struct
{
  unsigned char Flag1;
  unsigned char Flag2;
  unsigned char Flag3;
  // header only structure
  unsigned char HeaderLength;
  unsigned short MessageID;
  unsigned char MessageType;
  unsigned char PortAddress;
  unsigned short MessageLength;
  unsigned short Sequence;
  unsigned char IdleTime;
  unsigned char TimeStatus;
  unsigned short Week;
  unsigned long Milliseconds;
  unsigned long ReceiverStatus;
  unsigned short Reserved;
  unsigned short ReceiverSWVersion;
} HEADER;

typedef struct
{ 
  unsigned char Flag1;
  unsigned char Flag2;
  unsigned char Flag3;
  // header
  unsigned char HeaderLength;
  unsigned short MessageID;
  unsigned char MessageType;
  unsigned char PortAddress;
  unsigned short MessageLength;
  unsigned short Sequence;
  unsigned char IdleTime;
  unsigned char TimeStatus;
  unsigned short Week;
  unsigned long Milliseconds;
  unsigned long ReceiverStatus;
  unsigned short Reserved;
  unsigned short ReceiverSWVersion;
  // Data log
  unsigned long SolStatus;
  unsigned long PosType;
  double Lat;
  double Lon;
  double Hgt;
  float Undulation;
  unsigned long DatumID;
  float LatDev;
  float LonDev;
  float HgtDev;
  char StnID[4];
  float DiffAge;
  float SolAge;
  unsigned char Obs;
  unsigned char GPSL1;
  unsigned char L1;
  unsigned char L2;
  unsigned char Res1;
  unsigned char Res2;
  unsigned char Res3;
  unsigned char Res4;
  unsigned long CRC;
} BESTPOS;
//******************************BESTYXZ***************
typedef struct
{ 
  unsigned char Flag1;
  unsigned char Flag2;
  unsigned char Flag3;
  // header
  unsigned char HeaderLength;
  unsigned short MessageID;
  unsigned char MessageType;
  unsigned char PortAddress;
  unsigned short MessageLength;
  unsigned short Sequence;
  unsigned char IdleTime;
  unsigned char TimeStatus;
  unsigned short Week;
  unsigned long Milliseconds;
  unsigned long ReceiverStatus;
  unsigned short Reserved;
  unsigned short ReceiverSWVersion;
  // Data log
  unsigned long PSolStatus;
  unsigned long PosType;
  double X_Coord;
  double Y_Coord;
  double Z_Coord;
	float PX_StdDeviation;
	float PY_StdDeviation;
  float PZ_StdDeviation;
  unsigned long VSolStatus;
	unsigned long VelocityType;
  double X_VelocVector;
  double Y_VelocVector;
  double Z_VelocVector;
  float VX_StdDeviation;
	float VY_StdDeviation;
  float VZ_StdDeviation;    
	char StnID[4];
	float V_latency;
  float DiffAge;
  float SolAge;
  unsigned char Obs;
  unsigned char GPSL1;
  unsigned char L1;
  unsigned char L2;
  unsigned char Res1;
  unsigned char Res2;
  unsigned char Res3;
  unsigned char Res4;
  unsigned long CRC;
} BESTXYZ;
//**************************************RANGE_CMP***
typedef struct
{
	unsigned char Flag1;
  unsigned char Flag2;
  unsigned char Flag3;
  // header + obs RANGECMP structure
  unsigned char HeaderLength;
  unsigned short MessageID;
  unsigned char MessageType;
  unsigned char PortAddress;
  unsigned short MessageLength;
  unsigned short Sequence;
  unsigned char IdleTime;
  unsigned char TimeStatus;
  unsigned short Week;
  unsigned long Milliseconds;
  unsigned long ReceiverStatus;
  unsigned short Reserved;
  unsigned short ReceiverSWVersion;
	unsigned long obs; 
} RNG_HEADER;

typedef struct
{
   unsigned char ChnlTrackStatus[4]; //4
   unsigned int DopplerFreq; //4
	 char PseudoRNGu; //8	
	 unsigned int PseudoRNGl; //8	
	 unsigned int ADR; //8 
	 char SPSR; //4
	 char SADR; //4
	 unsigned char PRN; //2 
	 unsigned int LockTime; //4
	 char CNo; //4
	 BOOL DataValidate;	 
} RNG_RANGE;

typedef struct
{
  RNG_HEADER RNG_Header;
	unsigned char tmpRNG[24][24];
  RNG_RANGE RNG_Records[24]; 	
} RANGECMP;
//**************************************XYZ*********
typedef struct
{
  unsigned char Flag1;
  unsigned char Flag2;
  unsigned char Flag3;
	// header + obs RANGECMP structure
  unsigned char HeaderLength;
  unsigned short MessageID;
  unsigned char MessageType;
  unsigned char PortAddress;
  unsigned short MessageLength;
  unsigned short Sequence;
  unsigned char IdleTime;
  unsigned char TimeStatus;
  unsigned short Week;
  unsigned long Milliseconds;
  unsigned long ReceiverStatus;
  unsigned short Reserved;
  unsigned short ReceiverSWVersion;
	double ReservedXYZ;
	unsigned long sat; //numbers of satellites.
} XYZ_HEADER;

typedef struct
{   
  unsigned long PRN;
	double SatelX;
	double SatelY;
	double SatelZ;
	double CLK_Corr;
	double ION_Corr;
	double TROP_Corr;
	double Reserved1;
	double Reserved2;	
} XYZ_RANGE;

typedef struct
{
  XYZ_HEADER XYZ_Header;	
  XYZ_RANGE  XYZ_Records[12];	
	BOOL bValidSatArray[12];
	int nSat;
} SATXYZ;
//**************************************RANGE**

typedef struct
{
  unsigned char Flag1;
  unsigned char Flag2;
  unsigned char Flag3;
	// header + obs RANGECMP structure
  unsigned char HeaderLength;
  unsigned short MessageID;
  unsigned char MessageType;
  unsigned char PortAddress;
  unsigned short MessageLength;
  unsigned short Sequence;
  unsigned char IdleTime;
  unsigned char TimeStatus;
  unsigned short Week;
  unsigned long Milliseconds;
  unsigned long ReceiverStatus;
  unsigned short Reserved;
  unsigned short ReceiverSWVersion;	
	unsigned long obs; //numbers of satellites.
} RANGE_HEADER;

typedef struct
{   
  unsigned short PRN; //2
	unsigned short Reserved;
  double  PseudoRNG;
	float  SPSR;
	double ADR;
  float  SADR;
	float DopplerFreq;
	float CNo;
  float LockTime; //4
  unsigned char ChnlTrackStatus[4]; //4
} RANGE_RANGE;

typedef struct
{
  RANGE_HEADER Range_Header;
	BOOL bValidSatArray[24]; // 24's is because number of satellytes can be doubled! 
  RANGE_RANGE  Range_Records[24];
	int nObs;
} RANGE;
//**************************************SAV_RANGE_CMP***********

typedef struct
{
  unsigned char Flag1;
  unsigned char Flag2;
  unsigned char Flag3;
	// header + obs RANGE structure
  unsigned char HeaderLength;
  unsigned short MessageID;
  unsigned char MessageType;
  unsigned char PortAddress;
  unsigned short MessageLength;
  unsigned short Sequence;
  unsigned char IdleTime;
  unsigned char TimeStatus;
  unsigned short Week;
  unsigned long Milliseconds;
  unsigned long ReceiverStatus;
  unsigned short Reserved;
  unsigned short ReceiverSWVersion;	
	unsigned long obs; //numbers of satellites.
} SAV_RANGE_HEADER;

typedef struct
{   
  unsigned short PRN; //2	
  double ADR;
  float LockTime; //4  
} SAV_RANGE_RANGE;

typedef struct
{
  SAV_RANGE_HEADER Sav_Range_Header;	
	//int nObs;
  SAV_RANGE_RANGE  Sav_Range_Records[12];
	BOOL bValidSatArray[24];
	unsigned long CRC;
} SAV_RANGE_CMP;

//*******************************************************************
typedef struct
{
  unsigned short MsgID;
  unsigned long Milliseconds;
	BOOL bValidate;
} TimeStamp;
//********************************************************************
void  CalcPos (void);
float calcDD(int, int, float, float, float, float, float, float);
float calc_dis(int, int, float, float, float, float, float, float, float);
float update_pos(int, int, float, double, double, double, double, double, double, double, double, double);
int SatXYZAvail(int nCurPRN);
int BaseStationAvail(int nCurPRN);
void TopPickTimeStamp(unsigned short nMsgID, unsigned long Milliseconds);
//*********************************************************

#endif