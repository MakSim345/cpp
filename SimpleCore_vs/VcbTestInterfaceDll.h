// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VCBTESTINTERFACEDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VCBTESTINTERFACEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VCBTESTINTERFACEDLL_EXPORTS
#define VCBTESTINTERFACEDLL_API __declspec(dllexport)
#else
#define VCBTESTINTERFACEDLL_API __declspec(dllimport)
#endif

extern "C"
{
#include "VentilationParameters.h"
#include "VentUserSettings.h"
#include "VentilatorWaveforms.h"

	//Initiate a connection: Open port, test that communication works OK
	VCBTESTINTERFACEDLL_API bool startConnection( int port, int sampleTime );
	VCBTESTINTERFACEDLL_API void stopConnection();

	//Read debug strings sent from embedded SW, returns length of string or com. failure
	//caller must allocate memory and pass a pointer to the array and pass in the max length
	//returns boolean to determine if there are more debug messages
	VCBTESTINTERFACEDLL_API bool getLastDebugString( char * ptr, int maxLength );
	VCBTESTINTERFACEDLL_API bool isDebugMsgAvailable();

	VCBTESTINTERFACEDLL_API void setPeep( int peep );
    VCBTESTINTERFACEDLL_API void setBreathRate( int rr );
	VCBTESTINTERFACEDLL_API void setPmax( int pMax );
	VCBTESTINTERFACEDLL_API void setO2FreshGasFlow( unsigned short flow );
	VCBTESTINTERFACEDLL_API void setAirFreshGasFlow( unsigned short flow );
	VCBTESTINTERFACEDLL_API void setSqueezeSensitivity( unsigned short sensitivity );
	VCBTESTINTERFACEDLL_API void setInspFlow( int inspFlow );
	VCBTESTINTERFACEDLL_API void setExhVlv( int exhCmd );

	VCBTESTINTERFACEDLL_API void restorePeep( void );
	VCBTESTINTERFACEDLL_API void restorePmax( void );
	VCBTESTINTERFACEDLL_API void restoreInspFlow( void );
	VCBTESTINTERFACEDLL_API void restoreExhVlv( void );
    VCBTESTINTERFACEDLL_API void restoreSetBreathRate( void );

	VCBTESTINTERFACEDLL_API void startManualVent( void ); //start manual ventilation
	VCBTESTINTERFACEDLL_API void stopManualVent( void ); //stop manual ventilation
	VCBTESTINTERFACEDLL_API void startVent( void ); //starts the case
	VCBTESTINTERFACEDLL_API void stopVent( void ); //sets to standby mode

	VCBTESTINTERFACEDLL_API int getPeep( void );
    VCBTESTINTERFACEDLL_API int getSetBreathRate( void );
	VCBTESTINTERFACEDLL_API int getPmax( void );
	VCBTESTINTERFACEDLL_API int getInspFlow( void );
	VCBTESTINTERFACEDLL_API int getExpFlow( void );
	VCBTESTINTERFACEDLL_API int getSqueezeSensitivity( void );
	VCBTESTINTERFACEDLL_API int getExpPressure( void );
	VCBTESTINTERFACEDLL_API int getInspPressure( void );
	VCBTESTINTERFACEDLL_API int getAuxPressure( void );
	VCBTESTINTERFACEDLL_API int getInspFlowCmd( void );
	VCBTESTINTERFACEDLL_API int getExhCmd(void);

	//VCBTESTINTERFACEDLL_API int getVentilatorWaveforms(VentilatorWaveforms *waveforms);

	// Send ventilation mode settings
	//need to define struct definitions 
	//then send stucture as vent settings
	VCBTESTINTERFACEDLL_API void setVentParameters( VentilationParameters *params );
    VCBTESTINTERFACEDLL_API void setVentUserSettings( VentUserSettings *settings);
    VCBTESTINTERFACEDLL_API void restoreVentParameters();
    // Read alarm informations; id, priority, status, etc..
	//VCBTESTINTERFACEDLL_API void readAlarmInfo(struct *);
}
