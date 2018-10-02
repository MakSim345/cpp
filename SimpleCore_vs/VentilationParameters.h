#if !defined( VENTILATIONPARAMETERS_H )
#define VENTILATIONPARAMETERS_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VCBTESTINTERFACEDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VCBTESTINTERFACEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef VCBTESTINTERFACEDLL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

extern "C"
{
	DLL_EXPORT typedef struct
	{
		unsigned short wInspiratory;
		unsigned short wInspiratoryTrigger;
		unsigned short wInspiratoryPause;
		unsigned short wInspiratoryPauseTrigger;
		unsigned short wExpiratory;
		unsigned short wExpiratoryTrigger;
		unsigned short wExpiratoryPause;
		unsigned short wExpiratoryPauseTrigger;
		unsigned long dwMaxTidalVolume;
		unsigned long dwMinTidalVolume;
		unsigned short wMinMinuteVentilation;
		unsigned long dwMinFlow;
		unsigned long dwInitialFlow;
		unsigned long dwMaxFlow;
		unsigned long dwMaxExprFlow;
		unsigned short wPatientType;
		unsigned short wTriggerFlow;
		unsigned short wTriggerPressure;
		unsigned short wMinPressure;
		unsigned short wInitialPressure;
		unsigned short wMaxPressure;
		unsigned short wInspiratoryPressureSupport;
		unsigned short wExpiratoryPressureSupport;
		unsigned short wVentOptions;
		unsigned short wPressureSupportTimeout;
		unsigned short wSupportTermination;
		unsigned short wPeep;
		unsigned short wBaseFlow;
		unsigned short wInspiratoryPauseTriggerDelta;
		unsigned short wExpiratoryPauseTriggerDelta;
		unsigned short wFlowRiseTime;
		unsigned short wPressureRiseTime;
		unsigned short wPressureSupportRiseTime;
		unsigned short wPlimit;
		unsigned short wInspPressureRamp;
		unsigned short wFlowPattern;
		unsigned short wUnused1;
		unsigned short wUnused2; 
		unsigned short wUnused3;
	}VentilationParameters;

}

#endif
