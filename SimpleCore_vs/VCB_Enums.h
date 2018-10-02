//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%3CA1D94300BD.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CA1D94300BD.cm

//## begin module%3CA1D94300BD.cp preserve=no
//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	* CONFIDENTIAL & PROPRIETARY - PORTIONS OF THIS
//	* SOURCE CODE CONTAIN VALUABLE TRADE SECRET
//	* INFORMATION THAT IS THE PROPERTY
//	* OF DATEX-OHMEDA, INC.
//	*
//	* Archive Name:              $Archive: /prism/vcb/app/tip/Model/VCB_Hardware/VCB_Enums/VCB_Enums.h $
//	* Working File Name:         $Workfile: VCB_Enums.h $
//	*
//	* Version:                   $Revision: 2 $
//	*
//	* Last Modification Time:    $Modtime: 2/18/09 10:13a $
//	* Author:                    $Author: Dotzaunm $
//	*
//	*************************************************
//## end module%3CA1D94300BD.cp

//## Module: VCB_Enums%3CA1D94300BD; Package specification
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Source file: D:\Nate\PrismVentModule\VentControlBoard\Model\VCB_Hardware\VCB_Enums\VCB_Enums.h

#ifndef VCB_Enums_h
#define VCB_Enums_h 1

//## begin module%3CA1D94300BD.additionalIncludes preserve=no
//## end module%3CA1D94300BD.additionalIncludes

//## begin module%3CA1D94300BD.includes preserve=yes
//## end module%3CA1D94300BD.includes

//## begin module%3CA1D94300BD.declarations preserve=no
//## end module%3CA1D94300BD.declarations

//## begin module%3CA1D94300BD.additionalDeclarations preserve=yes
//## end module%3CA1D94300BD.additionalDeclarations


//## begin VCB_Enums%3CA0DD33034B.preface preserve=yes
//## end VCB_Enums%3CA0DD33034B.preface

//## Class: VCB_Enums%3CA0DD33034B
//	Interface to the vent control board enums.
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



class VCB_Enums 
{
  //## begin VCB_Enums%3CA0DD33034B.initialDeclarations preserve=yes
  //## end VCB_Enums%3CA0DD33034B.initialDeclarations

  public:
    // Additional Public Declarations
      //## begin VCB_Enums%3CA0DD33034B.public preserve=yes
      //## end VCB_Enums%3CA0DD33034B.public

  protected:
    // Additional Protected Declarations
      //## begin VCB_Enums%3CA0DD33034B.protected preserve=yes
      //## end VCB_Enums%3CA0DD33034B.protected

  private:
    // Additional Private Declarations
      //## begin VCB_Enums%3CA0DD33034B.private preserve=yes
      //## end VCB_Enums%3CA0DD33034B.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin VCB_Enums%3CA0DD33034B.implementation preserve=yes
      //## end VCB_Enums%3CA0DD33034B.implementation

};

//## begin VCB_Enums%3CA0DD33034B.postscript preserve=yes
//## end VCB_Enums%3CA0DD33034B.postscript

//## begin VCB_SERIAL_PORT_ID%3CA0DD8A0010.preface preserve=yes
//## end VCB_SERIAL_PORT_ID%3CA0DD8A0010.preface

//## Class: VCB_SERIAL_PORT_ID%3CA0DD8A0010
//	VCB specific mapings for the serial port ID's in the
//	DOSerialPortInterface OpenPort call.
//
//	1 = DEBUG_PORT1 = ColdFire port 1
//	2 = DEBUG_PORT2 = ColdFire port 2
//	3 = DISPLAY_COMPUTER_PORT
//	4 = EXPANSION_PORT_1
//	5 = EXPANSION_PORT_2 (routed through VMB)
//	6 =  AIR_SENSOR_PORT
//	7 = OXYGEN_SENSOR_PORT
//	8 = TOTAL_SENSOR_PORT
//	9 = VENT_MONITOR_BOARD_PORT
//	10 = VCB_TEST_PORT (used for MNT environment only)
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum
{
    DEBUG_PORT1 = 1, // ColdFire 1
    DEBUG_PORT2 = 2, // ColdFire 2
    DISPLAY_COMPUTER_PORT= 3,
    EXPANSION_PORT_1 = 4,
    EXPANSION_PORT_2 = 5, // expansion UART
    AIR_SENSOR_PORT = 6,
    OXYGEN_SENSOR_PORT = 7,
    TOTAL_SENSOR_PORT = 8,
    VENT_MONITOR_BOARD_PORT = 9,
    VCB_TEST_PORT = 10 // MNT only
} VCB_SERIAL_PORT_ID;

//## begin VCB_SERIAL_PORT_ID%3CA0DD8A0010.postscript preserve=yes
//## end VCB_SERIAL_PORT_ID%3CA0DD8A0010.postscript

//## begin SYSTEM_STATE%3D80FE690168.preface preserve=yes
//## end SYSTEM_STATE%3D80FE690168.preface

//## Class: SYSTEM_STATE%3D80FE690168
//	System States shared with the Display Computer.
//
//	    SYSTEM_STATE_OFF,
//	    SYSTEM_STATE_STANDBY,
//	    SYSTEM_STATE_POWERUP_SELFTEST,
//	    SYSTEM_STATE_CHECKOUT,
//	    SYSTEM_STATE_THERAPY,
//	    SYSTEM_STATE_MONITORING,
//	    SYSTEM_STATE_SERVICE,
//	    SYSTEM_STATE_SUPER_USER,
//	    SYSTEM_STATE_SOFTWARE_UPDATE,
//	    SYSTEM_STATE_FAILED,
//	    SYSTEM_STATE_FAILED_WITH_VENT,
//	    SYSTEM_STATE_MAX
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum
{
    SYSTEM_STATE_OFF,
    SYSTEM_STATE_STANDBY,
    SYSTEM_STATE_POWERUP_SELFTEST,
    SYSTEM_STATE_CHECKOUT,
    SYSTEM_STATE_THERAPY,
    SYSTEM_STATE_MONITORING,
    SYSTEM_STATE_SERVICE,
    SYSTEM_STATE_SUPER_USER,
    SYSTEM_STATE_SOFTWARE_UPDATE,
    SYSTEM_STATE_FAILED,
    SYSTEM_STATE_FAILED_WITH_VENT,
    SYSTEM_STATE_MAX
} SYSTEM_STATE;

//## begin SYSTEM_STATE%3D80FE690168.postscript preserve=yes
//## end SYSTEM_STATE%3D80FE690168.postscript

//## begin SENSIRION_STATE%3DFF99BC00B9.preface preserve=yes
//## end SENSIRION_STATE%3DFF99BC00B9.preface

//## Class: SENSIRION_STATE%3DFF99BC00B9
//	Part of the UartInterrupt class.
//
//	State of Sensirion data information being passed in at a
//	200Hz rate
//	    SENSIRION_STATE_INIT = start of message
//	    SENSIRION_FIRST_FLOW_CHAR = first 7f char found
//	    SENSIRION_FLOW_MSG_HEADER = second 7f char found
//	    SENSIRION_FLOW_DATA = first data point found, this
//	cannot be a 7f
//	    SENSIRION_ACTIVATE_FLOW = second data point found,
//	activate hisr
//
//	    SENSIRION_T = start of temperature message
//	    SENSIRION_E
//	    SENSIRION_M
//	    SENSIRION_P
//	    SENSIRION_FIRST_TEMP_CHAR = first 7f of temp msg
//	    SENSIRION_TEMP_MSG_HEADER = second 7f of temp msg
//	    SENSIRION_TEMP_DATA = first data point found, this
//	cannot be a 7f
//	    SENSIRION_ACTIVATE_TEMP = second data point found,
//	activate hisr
//
//	    SENSIRION_O
//	    SENSIRION_K
//
//	    SENSIRION_CR = start of EOL pair \r\n
//	    SENSIRION_EOL
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum
{
    SENSIRION_STATE_INIT,
    SENSIRION_FIRST_FLOW_CHAR,
    SENSIRION_FLOW_MSG_HEADER,
    SENSIRION_FLOW_DATA,
    SENSIRION_ACTIVATE_FLOW,
    SENSIRION_T,
    SENSIRION_E,
    SENSIRION_M,
    SENSIRION_P,
    SENSIRION_FIRST_TEMP_CHAR,
    SENSIRION_TEMP_MSG_HEADER,
    SENSIRION_TEMP_DATA,
    SENSIRION_ACTIVATE_TEMP,
    SENSIRION_O,
    SENSIRION_OK,
    SENSIRION_CR,
    SENSIRION_EOL
} SENSIRION_STATE;

//## begin SENSIRION_STATE%3DFF99BC00B9.postscript preserve=yes
//## end SENSIRION_STATE%3DFF99BC00B9.postscript

//## begin VENTILATION_MODE%3E4189E001C0.preface preserve=yes
//## end VENTILATION_MODE%3E4189E001C0.preface

//## Class: VENTILATION_MODE%3E4189E001C0
//	Enum defining the current ventilation mode.
//	VENTILATION_MODE_PT_VCV,
//	VENTILATION_MODE_PT_PCV,
//	VENTILATION_MODE_VG_PCV,
//	VENTILATION_MODE_VC_SIMV,
//	VENTILATION_MODE_PC_SIMV,
//	VENTILATION_MODE_BIPAP,
//	VENTILATION_MODE_BIPAP_PHIGH,
//	VENTILATION_MODE_BILEVEL_TINSP,
//	VENTILATION_MODE_BILEVEL_TINSP_PHIGH,
//	VENTILATION_MODE_BILEVEL_IE,
//	VENTILATION_MODE_BILEVEL_IE_PHIGH,
//	VENTILATION_MODE_CPAP_PSV,
//	VENTILATION_MODE_CPAP_PSV_RATE,
//	VENTILATION_MODE_PCVG_SIMV,
//	VENTILATION_MODE_VG_BILEVEL,
//	VENTILATION_MODE_NIV,
//	VENTILATION_MODE_NCPAP,
//	VENTILATION_MODE_PSVG
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum {
VENTILATION_MODE_PT_VCV,
VENTILATION_MODE_PT_PCV,
VENTILATION_MODE_VG_PCV,
VENTILATION_MODE_VC_SIMV,
VENTILATION_MODE_PC_SIMV,
VENTILATION_MODE_BIPAP,
VENTILATION_MODE_BIPAP_PHIGH,
VENTILATION_MODE_BILEVEL_TINSP,
VENTILATION_MODE_BILEVEL_TINSP_PHIGH,
VENTILATION_MODE_BILEVEL_IE,
VENTILATION_MODE_BILEVEL_IE_PHIGH,
VENTILATION_MODE_CPAP_PSV, //also AMV for now
VENTILATION_MODE_CPAP_PSV_RATE,
VENTILATION_MODE_PCVG_SIMV,
VENTILATION_MODE_VG_BILEVEL,
VENTILATION_MODE_NIV,
VENTILATION_MODE_NCPAP,
VENTILATION_MODE_PSVG
} VENTILATION_MODE;

//## begin VENTILATION_MODE%3E4189E001C0.postscript preserve=yes
//## end VENTILATION_MODE%3E4189E001C0.postscript

//## begin VCB_ERROR_CODE%3E494D0502E0.preface preserve=yes
//## end VCB_ERROR_CODE%3E494D0502E0.preface

//## Class: VCB_ERROR_CODE%3E494D0502E0
//	codes sent to the DU to be added to the Error Log.  some
//	of the values at the end of the list are for internal
//	use and should not be sent to the DU.  they are
//	identified below.  any code that is not recognized by
//	the DU will be logged as an unknown error.
//
//	Note:  Once these error codes are published, the error
//	codes should not change.  If an error code is no longer
//	needed, it should remain in this list to preserve the
//	integrity of the list.  If an error code becomes
//	obsolete, it should still remain in the list so the
//	latest list can be used for previous versions of
//	software.
//
//	VCB error codes:
//
//	UNUSED_ERROR_CODE = 0,
//	- Zero is not used so there is no confusion about the
//	absence of an error code.
//
//	VCB_4P906V_REF_ERROR_CODE = 1,
//	VCB_16V_SUPPLY_ERROR_CODE = 2,
//	VCB_12P5V_SUPPLY_ERROR_CODE = 3,
//	VCB_5V_ANALOG_SUPPLY_ERROR_CODE = 4,
//	VCB_6V_ANALOG_SUPPLY_ERROR_CODE = 5,
//	VCB_N6V_ANALOG_SUPPLY_ERROR_CODE = 6,
//	VCB_5P5V_ANALOG_SUPPLY_ERROR_CODE = 7,
//	NEBULIZER_SUPPLY_VOLTAGE_ERROR_CODE = 8,
//	AIR_O2_INSP_FLOW_SENSOR_SUPPLY_VOLTAGE_ERROR_CODE = 9,
//	TOTAL_FLOW_SENSOR_SUPPLY_VOLTAGE_ERROR_CODE = 10,
//	MONITOR_MODULE_POWER_FAIL_ERROR_CODE = 11,
//	PSM_POWER_FAIL_ERROR_CODE = 12,
//	EXPANSION_POWER_FAIL_ERROR_CODE = 13,
//	DU_ERR_LOG_EXP_FLOW_NORM_DISABLED = 14,
//	DU_ERR_LOG_EXC_BUS_ERROR = 15
//	DU_ERR_LOG_EXC_ADDRESS_ERROR = 16
//	DU_ERR_LOG_EXC_ILLEGAL_INSTRUCTION = 17
//	DU_ERR_LOG_EXC_DIVIDE_BY_ZERO = 18
//	DU_ERR_LOG_EXC_CHK_CHK2 = 19
//	DU_ERR_LOG_EXC_TRAPV = 20
//	DU_ERR_LOG_EXC_PRIVILEGE_VIOLATION = 21
//	DU_ERR_LOG_EXC_TRACE = 22
//	DU_ERR_LOG_EXC_EMUL_A = 23
//	DU_ERR_LOG_EXC_EMUL_B = 24
//	DU_ERR_LOG_EXC_HDW_BREAKPOINT = 25
//	DU_ERR_LOG_EXC_COPROCESSOR_VIOLATION = 26
//	DU_ERR_LOG_EXC_FORMAT_ERROR = 27
//	DU_ERR_LOG_EXC_UNINIT_INTERRUPT = 28
//	DU_ERR_LOG_EXC_SPURIOUS = 29
//	DU_ERR_LOG_EXC_UNKNOWN = 30
//	DU_ERR_LOG_UNEXPECTED_RESET_DETECTED = 31
//	DU_ERR_LOG_WATCHDOG_RESET_DETECTED = 32
//	DU_ERR_LOG_NVM_RESET_DETECTED = 33
//	DU_ERR_LOG_FAILED_WITH_VENT = 34
//
//	the following codes apply only to the VCB error log...
//
//	INCOMPATIBLE_IRIS_LINK = 0x100,
//	VCB_POST_FAILURE = 0x101,
//	NVM_CRC_FAILURE = 0x102,
//	EXC_STACK = 0x103,
//	EXC_FORMAT_STATUS = 0x104,
//	EXC_PROGRAM_COUNTER = 0x105
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum
{
    // DU error log codes
    UNUSED_ERROR_CODE = 0,
    VCB_4P906V_REF_ERROR_CODE = 1,
    VCB_16V_SUPPLY_ERROR_CODE = 2,
    VCB_12P5V_SUPPLY_ERROR_CODE = 3,
    VCB_5V_ANALOG_SUPPLY_ERROR_CODE = 4,
    VCB_6V_ANALOG_SUPPLY_ERROR_CODE = 5,
    VCB_N6V_ANALOG_SUPPLY_ERROR_CODE = 6,
    VCB_5P5V_ANALOG_SUPPLY_ERROR_CODE = 7,
    NEBULIZER_SUPPLY_VOLTAGE_ERROR_CODE = 8,
    AIR_O2_INSP_FLOW_SENSOR_SUPPLY_VOLTAGE_ERROR_CODE = 9,
    TOTAL_FLOW_SENSOR_SUPPLY_VOLTAGE_ERROR_CODE = 10,
    MONITOR_MODULE_POWER_FAIL_ERROR_CODE = 11,
    PSM_POWER_FAIL_ERROR_CODE = 12,
    EXPANSION_POWER_FAIL_ERROR_CODE = 13,
    DU_ERR_LOG_EXP_FLOW_NORM_DISABLED = 14,
    DU_ERR_LOG_EXC_BUS_ERROR = 15,
    DU_ERR_LOG_EXC_ADDRESS_ERROR = 16,
    DU_ERR_LOG_EXC_ILLEGAL_INSTRUCTION = 17,
    DU_ERR_LOG_EXC_DIVIDE_BY_ZERO = 18,
    DU_ERR_LOG_EXC_CHK_CHK2 = 19,
    DU_ERR_LOG_EXC_TRAPV = 20,
    DU_ERR_LOG_EXC_PRIVILEGE_VIOLATION = 21,
    DU_ERR_LOG_EXC_TRACE = 22,
    DU_ERR_LOG_EXC_EMUL_A = 23,
    DU_ERR_LOG_EXC_EMUL_B = 24,
    DU_ERR_LOG_EXC_HDW_BREAKPOINT = 25,
    DU_ERR_LOG_EXC_COPROCESSOR_VIOLATION = 26,
    DU_ERR_LOG_EXC_FORMAT_ERROR = 27,
    DU_ERR_LOG_EXC_UNINIT_INTERRUPT = 28,
    DU_ERR_LOG_EXC_SPURIOUS = 29,
    DU_ERR_LOG_EXC_UNKNOWN = 30,
    DU_ERR_LOG_UNEXPECTED_RESET_DETECTED = 31,
    DU_ERR_LOG_WATCHDOG_RESET_DETECTED = 32,
    DU_ERR_LOG_NVM_RESET_DETECTED = 33,
    DU_ERR_LOG_FAILED_WITH_VENT = 34,

    // all codes below are for VCB error log only
    INCOMPATIBLE_IRIS_LINK = 0x100,
    VCB_POST_FAILURE = 0x101,
    NVM_CRC_FAILURE = 0x102,
    EXC_STACK = 0x103,
    EXC_FORMAT_STATUS = 0x104,
    EXC_PROGRAM_COUNTER = 0x105
} VCB_ERROR_CODE;

//## begin VCB_ERROR_CODE%3E494D0502E0.postscript preserve=yes
//## end VCB_ERROR_CODE%3E494D0502E0.postscript

//## begin ALARM_MEMBER%3E4955C30215.preface preserve=yes
//## end ALARM_MEMBER%3E4955C30215.preface

//## Class: ALARM_MEMBER%3E4955C30215
//	Number for which IRIS message to set the status bit to.
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum {
VCB_TECHNICAL_ALARM_STATUS1 = 1,
VCB_TECHNICAL_ALARM_STATUS2 = 2,
VCB_PARAMETER_ALARM_STATUS = 3
} ALARM_MEMBER;

//## begin ALARM_MEMBER%3E4955C30215.postscript preserve=yes
//## end ALARM_MEMBER%3E4955C30215.postscript

//## begin VCB_REBOOT_CODE%3EEF2BE20153.preface preserve=yes
//## end VCB_REBOOT_CODE%3EEF2BE20153.preface

//## Class: VCB_REBOOT_CODE%3EEF2BE20153
//	    UPGRADE_REQUESTED  // The application requested an
//	upgrade an is calling bootcode to perform it
//	    NORMAL_BOOT  // Reboots normally as in the case of a
//	reset
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum
{
    UPGRADE_REQUESTED,
    NORMAL_BOOT
} VCB_REBOOT_CODE;

//## begin VCB_REBOOT_CODE%3EEF2BE20153.postscript preserve=yes
//## end VCB_REBOOT_CODE%3EEF2BE20153.postscript

//## begin VMB_ERROR_CODE%3F9038490375.preface preserve=yes
//## end VMB_ERROR_CODE%3F9038490375.preface

//## Class: VMB_ERROR_CODE%3F9038490375
//	Note:  Once these error codes are published, the error
//	codes should not change.  If an error code is no longer
//	needed, it should remain in this list to preserve the
//	integrity of the list.  If an error code becomes
//	obsolete, it should still remain in the list so the
//	latest list can be used for previous versions of
//	software.
//
//	VMB error codes:
//
//	unused = 0,
//	- Zero is not used so there is no confusion about the
//	absence of an error code.
//
//	VMB_12P5V_SUPPLY_ERROR_CODE = 1
//	VMB_EXPIRATORY_FLOW_SENSOR_VOLTAGE_ERROR_CODE = 2
//	VMB_O2_CONCENTRATION_SENSOR_VOLTAGE_ERROR_CODE = 3
//	VMB_O2_PRESSURE_SENSOR_VOLTAGE_ERROR_CODE = 4
//	VMB_AIR_PRESSURE_SENSOR_VOLTAGE_ERROR_CODE = 5
//	VMB_5P5V_ANALOG_ERROR_CODE = 6
//	VMB_N5P5V_ANALOG_ERROR_CODE = 7
//	VMB_EXP_FLOW_NORMALIZATION_DISABLED = 8
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum {
    VMB_12P5V_SUPPLY_ERROR_CODE = 1,
    VMB_EXPIRATORY_FLOW_SENSOR_VOLTAGE_ERROR_CODE = 2,
    VMB_O2_CONCENTRATION_SENSOR_VOLTAGE_ERROR_CODE = 3,
    VMB_O2_PRESSURE_SENSOR_VOLTAGE_ERROR_CODE = 4,
    VMB_AIR_PRESSURE_SENSOR_VOLTAGE_ERROR_CODE = 5,
    VMB_5P5V_ANALOG_ERROR_CODE = 6,
    VMB_N5P5V_ANALOG_ERROR_CODE = 7,
    VMB_EXP_FLOW_NORMALIZATION_DISABLED = 8
} VMB_ERROR_CODE;

//## begin VMB_ERROR_CODE%3F9038490375.postscript preserve=yes
//## end VMB_ERROR_CODE%3F9038490375.postscript

//## begin VCB_PATIENT_TYPE%443D4C100018.preface preserve=yes
//## end VCB_PATIENT_TYPE%443D4C100018.preface

//## Class: VCB_PATIENT_TYPE%443D4C100018
//	PT_ADULT = 0
//	PT_PED = 1
//	PT_NEONATAL = 2
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum
{
    PT_ADULT,
    PT_PED,
    PT_NEONATAL,
    PT_MAX
} VCB_PATIENT_TYPE;

//## begin VCB_PATIENT_TYPE%443D4C100018.postscript preserve=yes
//## end VCB_PATIENT_TYPE%443D4C100018.postscript

//## begin SPIRO_INSP_TRIGGER_SOURCE%467BECD2028E.preface preserve=yes
//## end SPIRO_INSP_TRIGGER_SOURCE%467BECD2028E.preface

//## Class: SPIRO_INSP_TRIGGER_SOURCE%467BECD2028E
//	Spirometer source of inspiratory trigger:
//	INSP_TRIG_NONE = 0,
//	INSP_TRIG_FLOW = 1,
//	INSP_TRIG_AIRWAY_PRES = 2,
//	INSP_TRIG_NASAL_THRESHOLD = 3,
//	INSP_TRIG_TIMEOUT = 4
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum {
    INSP_TRIG_NONE,
    INSP_TRIG_FLOW,
    INSP_TRIG_AIRWAY_PRES,
    INSP_TRIG_NASAL_THRESHOLD,
    INSP_TRIG_TIMEOUT
} SPIRO_INSP_TRIGGER_SOURCE;

//## begin SPIRO_INSP_TRIGGER_SOURCE%467BECD2028E.postscript preserve=yes
//## end SPIRO_INSP_TRIGGER_SOURCE%467BECD2028E.postscript

//## begin SPIRO_EXP_TRIGGER_SOURCE%467BEE34028C.preface preserve=yes
//## end SPIRO_EXP_TRIGGER_SOURCE%467BEE34028C.preface

//## Class: SPIRO_EXP_TRIGGER_SOURCE%467BEE34028C
//	Spirometer source of expiratory trigger:
//	EXP_TRIG_NONE = 0,
//	EXP_TRIG_NON_LEAK_COMP_END_FLOW = 1,
//	EXP_TRIG_LEAK_COMP_END_FLOW = 2,
//	EXP_TRIG_AIRWAY_PRES = 3,
//	EXP_TRIG_NASAL_PERCENT_PEAK = 4,
//	EXP_TRIG_NASAL_THRESHOLD = 5,
//	EXP_TRIG_TIMEOUT = 6
//## Category: VCB_Hardware::VCB_Enums%3CA0DD1D02F9
//## Subsystem: VCB_Hardware::VCB_Enums%3CA1D92801E1
//## Persistence: Transient
//## Cardinality/Multiplicity: n



typedef enum {
    EXP_TRIG_NONE,
    EXP_TRIG_NON_LEAK_COMP_END_FLOW,
    EXP_TRIG_LEAK_COMP_END_FLOW,
    EXP_TRIG_AIRWAY_PRES,
    EXP_TRIG_NASAL_PERCENT_PEAK,
    EXP_TRIG_NASAL_THRESHOLD,
    EXP_TRIG_TIMEOUT
} SPIRO_EXP_TRIGGER_SOURCE;

//## begin SPIRO_EXP_TRIGGER_SOURCE%467BEE34028C.postscript preserve=yes
//## end SPIRO_EXP_TRIGGER_SOURCE%467BEE34028C.postscript

// Class VCB_Enums 

// Class VCB_Enums 

// Additional Declarations
  //## begin VCB_Enums%3CA0DD33034B.declarations preserve=yes
  //## end VCB_Enums%3CA0DD33034B.declarations

//## begin module%3CA1D94300BD.epilog preserve=yes
//## end module%3CA1D94300BD.epilog


#endif
