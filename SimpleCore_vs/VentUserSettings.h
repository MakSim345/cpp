#if !defined( VENTUSERSETTINGS_H )
#define VENTUSERSETTINGS_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VCBTESTINTERFACEDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VCBTESTINTERFACEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include "VCB_Enums.h"
#ifdef VCBTESTINTERFACEDLL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

extern "C"
{
    DLL_EXPORT typedef struct
    {
      VENTILATION_MODE VentilationMode;
      //## end VentUserSettings::VentilationMode%3E416C070049.attr

      //## Attribute: bySetBreathRate%3E416C350163
      //## begin VentUserSettings::bySetBreathRate%3E416C350163.attr preserve=no  public: unsigned char {UA} 
      unsigned char bySetBreathRate;
      //## end VentUserSettings::bySetBreathRate%3E416C350163.attr

      //## Attribute: nSetPeep%3E416C4A000B
      //## begin VentUserSettings::nSetPeep%3E416C4A000B.attr preserve=no  public: short {UA} 
      short nSetPeep;
      //## end VentUserSettings::nSetPeep%3E416C4A000B.attr

      //## Attribute: dwSetTidalVolume%3E416C5D0049
      //	Set Tidal Volume in microliters.
      //## begin VentUserSettings::dwSetTidalVolume%3E416C5D0049.attr preserve=no  public: unsigned long {UA} 
      unsigned long dwSetTidalVolume;
      //## end VentUserSettings::dwSetTidalVolume%3E416C5D0049.attr

      //## Attribute: nSetPinspired%3E416C6E0347
      //	represents Pinsp, which is pressure above PEEP
      //## begin VentUserSettings::nSetPinspired%3E416C6E0347.attr preserve=no  public: short {UA} 
      short nSetPinspired;
      //## end VentUserSettings::nSetPinspired%3E416C6E0347.attr

      //## Attribute: nSetPhigh%499C3F5702CE
      //	represents Phigh, which is the high pressure level
      //## begin VentUserSettings::nSetPhigh%499C3F5702CE.attr preserve=no  public: short {UA} 
      short nSetPhigh;
      //## end VentUserSettings::nSetPhigh%499C3F5702CE.attr

      //## Attribute: nSetPmax%3E416C7D024D
      //## begin VentUserSettings::nSetPmax%3E416C7D024D.attr preserve=no  public: short {UA} 
      short nSetPmax;
      //## end VentUserSettings::nSetPmax%3E416C7D024D.attr

      //## Attribute: dwApneaDelayTime%3E416C8A02F9
      //## begin VentUserSettings::dwApneaDelayTime%3E416C8A02F9.attr preserve=no  public: unsigned long {UA} 
      unsigned long dwApneaDelayTime;
      //## end VentUserSettings::dwApneaDelayTime%3E416C8A02F9.attr

      //## Attribute: nAltitude%3E416C9E03A5
      //## begin VentUserSettings::nAltitude%3E416C9E03A5.attr preserve=no  public: short {UA} 
      short nAltitude;
      //## end VentUserSettings::nAltitude%3E416C9E03A5.attr

      //## Attribute: bySettingType%3EEF71A2029B
      //## begin VentUserSettings::bySettingType%3EEF71A2029B.attr preserve=no  public: unsigned char {UA} 
      unsigned char bySettingType;
      //## end VentUserSettings::bySettingType%3EEF71A2029B.attr

      //## Attribute: nSetPLimit%3EEF71B4021E
      //## begin VentUserSettings::nSetPLimit%3EEF71B4021E.attr preserve=no  public: short {UA} 
      short nSetPLimit;
      //## end VentUserSettings::nSetPLimit%3EEF71B4021E.attr

      //## Attribute: byLeakLimit%4676C1CC0293
      //## begin VentUserSettings::byLeakLimit%4676C1CC0293.attr preserve=no  public: unsigned char {UA} 
      unsigned char byLeakLimit;
      //## end VentUserSettings::byLeakLimit%4676C1CC0293.attr

      //## Attribute: byLeakCompensation%4228C2CB0340
      //## begin VentUserSettings::byLeakCompensation%4228C2CB0340.attr preserve=no  public: unsigned char {UA} 
      unsigned char byLeakCompensation;
      //## end VentUserSettings::byLeakCompensation%4228C2CB0340.attr

      //## Attribute: byVolumeCalcCondition%4228C4F4007D
      //## begin VentUserSettings::byVolumeCalcCondition%4228C4F4007D.attr preserve=no  public: unsigned char {UA} 
      unsigned char byVolumeCalcCondition;
      //## end VentUserSettings::byVolumeCalcCondition%4228C4F4007D.attr

      //## Attribute: bNfsState%43EB71E10301
      //	indicates whether NFS was turned off by the user
      //	(true=on, false=off)
      //## begin VentUserSettings::bNfsState%43EB71E10301.attr preserve=no  public: bool {UA} 
      bool bNfsState;
      //## end VentUserSettings::bNfsState%43EB71E10301.attr

      //## Attribute: nSetTlow%43F5E4D401B0
      //	Tlow set by the user
      //## begin VentUserSettings::nSetTlow%43F5E4D401B0.attr preserve=no  public: short {UA} 
      short nSetTlow;
      //## end VentUserSettings::nSetTlow%43F5E4D401B0.attr

      //## Attribute: nSetTinsp%4676C2B00225
      //	User Setting Tinsp
      //## begin VentUserSettings::nSetTinsp%4676C2B00225.attr preserve=no  public: short {UA} 
      short nSetTinsp;
      //## end VentUserSettings::nSetTinsp%4676C2B00225.attr

      //## Attribute: bTriggerCompensation%43F5E4ED03C4
      //	true if trigger compensation was enabled by the user
      //## begin VentUserSettings::bTriggerCompensation%43F5E4ED03C4.attr preserve=no  public: bool {UA} 
      bool bTriggerCompensation;
      //## end VentUserSettings::bTriggerCompensation%43F5E4ED03C4.attr

      //## Attribute: dwSetBreathTime%4676C1440029
      //	User set calculated breath time.
      //## begin VentUserSettings::dwSetBreathTime%4676C1440029.attr preserve=no  public: unsigned long {UA} 
      unsigned long dwSetBreathTime;
      //## end VentUserSettings::dwSetBreathTime%4676C1440029.attr

      //## Attribute: bBackupSetting%49DB6CFB0074
      //	indicates whether to backup the current mode in failed
      //	state
      //## begin VentUserSettings::bBackupSetting%49DB6CFB0074.attr preserve=no  public: bool {UA} 
      bool bBackupSetting;
      //## end VentUserSettings::bBackupSetting%49DB6CFB0074.attr

      //## Attribute: bManualVent%4C2B885A01A8
      //	Used to turn manual vent mode on/off
      //## begin VentUserSettings::bManualVent%4C2B885A01A8.attr preserve=no  public: bool {UA} false
      bool bManualVentModeOn;
      //## end VentUserSettings::bManualVent%4C2B885A01A8.attr

    }VentUserSettings;

}

#endif
