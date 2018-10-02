#ifndef COMMPORT_H
#define COMMPORT_H	

#include <Windows.h>

#define COMFILE_VERSION " RELEASE: REL_0_0_3 \n\r"
#define  TX0023     "\n\rLast Compilation: %s, %s"


class CommPort
{
public:
   enum Parity
	 { None = 0, Odd, Even, Mark, Space};

    enum DataBits
    { db4 = 4, db5, db6, db7, db8};

    enum StopBits
    { sb1 = 0, sb15, sb2};

    enum BitRate
    {
       br110 = 110,
       br300 = 300,
       br600 = 600,	
       br1200 = 1200,
       br2400 = 2400,
       br4800 = 4800,
       br9600 = 9600,
       br19200 = 19200,
       br38400 = 38400,
       br56000 = 56000,
       br57600 = 57600,
       br115200 = 115200,
       br256000 = 256000
    };
  

	 CommPort();
	 CommPort(const int);
	 CommPort(const int, BitRate);
	~CommPort();

	void OpenPort();
	void ClosePort(); 

	DWORD WriteToPort (const void *inBuffer, const unsigned long inBufSize);
	BOOL WriteToPort (const char inChar); // write one character.
	
 	int  ReadFromPort(char *inBuffer, const unsigned long inCharsReq);
  char ReadFromPort (void);
	
  void SetBaudRate(const BitRate nBaudRate);
	void SetByteSize(const DataBits nDataBits);
	void SetParity(const Parity nParity);
	void SetStopBits(const StopBits nStopBits);	
	void SetBufferSizeVar(const int i) {m_nBufferSize = i;}
	
	int  GetBufferSizeVar(void) {return m_nBufferSize;}

private:

	 char     *m_sComPort;
	 char     *MessageBuffer;
   BOOL     m_bPortReady;
   HANDLE   m_hCom;
   DCB      m_dcb;   
   BOOL     bWriteRC;
   BOOL     bReadRC;
   DWORD    iBytesWritten;
   DWORD    iBytesRead;
   char     sBuffer[128];
	 COMMTIMEOUTS m_CommTimeouts;
	 int      m_nBufferSize;
	 BitRate  m_BitRate;

	 BOOL setState (void);
	 BOOL getState (void);
	 BOOL setBufferComm (void);
};

void GetVersionString( char* sResString);

#endif // COMMPORT
