// #include "stdafx.h"
#include "VcbTestMessageHeaders.h"
// #include "IRIS_GUI_01.h" 

extern CTRACE t;
extern uVcbSensorInfo VcbSensorInfoStruct;
extern uVcbOtherVcbData VcbOtherVcbDataStruct;

#ifdef NTEL_PLATFORM_CONVERT
#define BYTE_SWAP_COPY_16(A,B) byteSwapCopy16(A,B);
#define BYTE_SWAP_COPY_32(A,B) byteSwapCopy32(A,B);
#else
#define BYTE_SWAP_COPY_16(A,B) *((IRIS_UINT16 *)B) = *((IRIS_UINT16 *)A);
#define BYTE_SWAP_COPY_32(A,B) *((IRIS_UINT32 *)B) = *((IRIS_UINT32 *)A);
#endif

// #if 0

/***************** START MESSAGE ******************/
// VCB_TEST_SENSOR_INFO_ID 32
const int VcbTest_SensorInfo::msgID = VCB_TEST_SENSOR_INFO_ID;

const char VcbTest_SensorInfo::nameStr[] = "VcbTest_SensorInfo";

/*
Provides type of Sensor, Software, Hardware, Version, Units, Factor, 
Overflow, Sensitivity, Reference Temperature, Factor temperature, 
Sensor Serial Number, Current Temperature value, and Sensor Flow value. 
*/

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SensorInfo::VcbTest_SensorInfo() :
    Message(VCB_TEST_SENSOR_INFO_ID , 24)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SensorInfo::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;

  // Fill in the Message class info
  Message::pktBuild(&pktPtr);

  // Copy individual members into the serial buffer

  // IRIS_INT32 
  //BYTE_SWAP_COPY_32(pktPtr, &TotalFlow);
	BYTE_SWAP_COPY_32(&TotalFlow, pktPtr);
  pktPtr += 4;	
  
  // IRIS_INT32
  BYTE_SWAP_COPY_32(&OxygenFlow, pktPtr);
  pktPtr += 4;
	
  // IRIS_INT32 AirFlow
  BYTE_SWAP_COPY_32(&AirFlow, pktPtr);
  pktPtr += 4;
	
 // IRIS_INT32 TotalCurrentTemp
  BYTE_SWAP_COPY_32(&TotalCurrentTemp, pktPtr);
  pktPtr += 4;
	
  // IRIS_INT32 OxygenCurrentTemp
  BYTE_SWAP_COPY_32(	&OxygenCurrentTemp, pktPtr);
  pktPtr += 4;
	
  // IRIS_INT32 AirCurrentTemp  
  BYTE_SWAP_COPY_32(&AirCurrentTemp, pktPtr);
  pktPtr += 4;
	
  // Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SensorInfo::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  // IRIS_INT32 
  BYTE_SWAP_COPY_32(pktPtr, &TotalFlow);
  pktPtr += 4;	
  //t.TRACEY ("TotalFlow: %d\n", TotalFlow);
	VcbSensorInfoStruct.nTotalFlow = TotalFlow;
	
  // IRIS_INT32
  BYTE_SWAP_COPY_32(pktPtr, &OxygenFlow);
  pktPtr += 4;
	//t.TRACEY ("OxygenFlow: %d\n", OxygenFlow);
	VcbSensorInfoStruct.nOxygenFlow = OxygenFlow;

  // IRIS_INT32 AirFlow
  BYTE_SWAP_COPY_32(pktPtr, &AirFlow);
  pktPtr += 4;
	//t.TRACEY ("AirFlow: %d\n", AirFlow);
	VcbSensorInfoStruct.nAirFlow  = AirFlow;
	
 // IRIS_INT32 TotalCurrentTemp
  BYTE_SWAP_COPY_32(pktPtr, &TotalCurrentTemp);
  pktPtr += 4;
	//t.TRACEY ("TotalCurrentTemp: %.2f\n", (float)TotalCurrentTemp/100);
	VcbSensorInfoStruct.nTotalCurrentTemp = TotalCurrentTemp;

  // IRIS_INT32 OxygenCurrentTemp
  BYTE_SWAP_COPY_32(pktPtr, &OxygenCurrentTemp);
  pktPtr += 4;
	//t.TRACEY ("OxygenCurrentTemp: %.2f\n", (float)OxygenCurrentTemp/100);
	VcbSensorInfoStruct.nOxygenCurrentTemp = OxygenCurrentTemp;

  // IRIS_INT32 AirCurrentTemp  
  BYTE_SWAP_COPY_32(pktPtr, &AirCurrentTemp);
  pktPtr += 4;
	//t.TRACEY ("AirCurrentTemp: %.2f\n", (float)AirCurrentTemp/100);
	VcbSensorInfoStruct.nAirCurrentTemp = AirCurrentTemp;
  
  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SensorInfo::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SENSOR_DETAILS_ID 33
const int VcbTest_SensorDetails::msgID = VCB_TEST_SENSOR_DETAILS_ID;

const char VcbTest_SensorDetails::nameStr[] = "VcbTest_SensorDetails";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SensorDetails::VcbTest_SensorDetails() :
    Message(VCB_TEST_SENSOR_DETAILS_ID , 11)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SensorDetails::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	//BYTE_SWAP_COPY_16(&VmExhalOpen, pktPtr);
	//pktPtr[nArrPointer] = VmExhalOpen;	
  pktPtr += 1;
	//t.TRACEY (": %d\n", );
	  
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SensorDetails::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  //byteSwapCopy8(pktPtr, &ModPwrFail);
  //pktPtr += 1;	
  //t.TRACEY ("ModPwrFail: %d\n", ModPwrFail);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SensorDetails::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_CHANNEL_CONFIGURATIONS_ID 34	
const int VcbTest_ChannelConfigurations::msgID = VCB_TEST_CHANNEL_CONFIGURATIONS_ID;

const char VcbTest_ChannelConfigurations::nameStr[] = "VcbTest_ChannelConfigurations";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_ChannelConfigurations::VcbTest_ChannelConfigurations() :
    Message(VCB_TEST_CHANNEL_CONFIGURATIONS_ID , 116) // 152?
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_ChannelConfigurations::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
		
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	//Expiratory Pressure IRIS_UINT16 InspPressureCounts;
	BYTE_SWAP_COPY_16(&InspPressureCounts, pktPtr);
	pktPtr += 2;
	
  //Expiratory Pressure IRIS_INT16 InspPressureValue;
	BYTE_SWAP_COPY_16(&InspPressureValue, pktPtr);
	pktPtr += 2;

  //Aux Pressure IRIS_UINT16 AuxPressureCounts;
	BYTE_SWAP_COPY_16(&AuxPressureCounts, pktPtr);
	pktPtr += 2;

  //Aux Pressure IRIS_INT16 AuxPressureValue;
	BYTE_SWAP_COPY_16(&AuxPressureValue, pktPtr);
	pktPtr += 2;

  //Exhalation Valve Drive Voltage IRIS_UINT16 ExhValveVoltageCounts;
	BYTE_SWAP_COPY_16(&ExhValveVoltageCounts, pktPtr);
	pktPtr += 2;

  //Exhalation Valve Drive Voltage IRIS_INT32 ExhValveVoltageValue;
	BYTE_SWAP_COPY_32(&ExhValveVoltageValue, pktPtr);
	pktPtr += 4;

  //Exhalation Valve Drive Current IRIS_UINT16 ExhValveCurrentCounts;
	BYTE_SWAP_COPY_16(&ExhValveCurrentCounts, pktPtr);
	pktPtr += 2;

  //Exhalation Valve Drive Current IRIS_INT32 ExhValveCurrentValue;
	BYTE_SWAP_COPY_32(&ExhValveCurrentValue, pktPtr);
	pktPtr += 4;

  //Secondary Voltage Reference IRIS_UINT16 V4096refCounts;
	BYTE_SWAP_COPY_16(&V4096refCounts, pktPtr);
	pktPtr += 2;

  //Secondary Voltage Reference IRIS_INT32 V4096refValue;
	BYTE_SWAP_COPY_32(&V4096refValue, pktPtr);
	pktPtr += 4;

  //Analog Ground IRIS_UINT16 MUXA_AGND_Counts;
	BYTE_SWAP_COPY_16(&MUXA_AGND_Counts, pktPtr);
	pktPtr += 2;

  //Analog Ground IRIS_INT32 MUXA_AGND_Value;
	BYTE_SWAP_COPY_32(&MUXA_AGND_Value, pktPtr);
	pktPtr += 4;

  //Analog Ground IRIS_UINT16 MUXB_AGND_Counts;
	BYTE_SWAP_COPY_16(&MUXB_AGND_Counts, pktPtr);
	pktPtr += 2;

  //Analog Ground IRIS_INT32 MUXB_AGND_Value;
	BYTE_SWAP_COPY_32(&MUXB_AGND_Value, pktPtr);
	pktPtr += 4;

  //Analog Ground IRIS_UINT16 ADC_AGND_Counts;
	BYTE_SWAP_COPY_16(&ADC_AGND_Counts, pktPtr);
	pktPtr += 2;

  //Analog Ground IRIS_INT32 ADC_AGND_Value;
	BYTE_SWAP_COPY_32(&ADC_AGND_Value, pktPtr);
	pktPtr += 4;

  //Oxygen Valve Drive Current IRIS_UINT16 O2ValveCurrentCounts;
	BYTE_SWAP_COPY_16(&O2ValveCurrentCounts, pktPtr);
	pktPtr += 2;

  //Oxygen Valve Drive Current IRIS_INT32 O2ValveCurrentValue;
	BYTE_SWAP_COPY_32(&O2ValveCurrentValue, pktPtr);
	pktPtr += 4;

  //Air Valve Current Counts IRIS_UINT16 AirValveCurrentCounts;
	BYTE_SWAP_COPY_16(&AirValveCurrentCounts, pktPtr);
	pktPtr += 2;

  //Air Valve Current Counts IRIS_INT32 AirValveCurrentValue;
	BYTE_SWAP_COPY_32(&AirValveCurrentValue, pktPtr);
	pktPtr += 4;

  //Nebulizer Supply Voltage IRIS_UINT16 V9Test_C_Counts;
	BYTE_SWAP_COPY_16(&V9Test_C_Counts, pktPtr);
	pktPtr += 2;

  //Nebulizer Supply Voltage IRIS_INT32 V9Test_C_Value;
	BYTE_SWAP_COPY_32(&V9Test_C_Value, pktPtr);
	pktPtr += 4;

  //Ambient Temperature Near Valves IRIS_UINT16 AmbientTempCounts;
	BYTE_SWAP_COPY_16(&AmbientTempCounts, pktPtr);
	pktPtr += 2;

  //Ambient Temperature Near Valves IRIS_INT32 AmbientTempValue;
	BYTE_SWAP_COPY_32(&AmbientTempValue, pktPtr);
	pktPtr += 4;

  //Mod Power Fail IRIS_UINT16 ModPwrFailCounts;
	BYTE_SWAP_COPY_16(&ModPwrFailCounts, pktPtr);
	pktPtr += 2;

  //Mod Power Fail IRIS_INT32 ModPwrFailValue;
	BYTE_SWAP_COPY_32(&ModPwrFailValue, pktPtr);
	pktPtr += 4;

  //12P5 IRIS_UINT16 V12P5_Test_Counts;
	BYTE_SWAP_COPY_16(&V12P5_Test_Counts, pktPtr);
	pktPtr += 2;

  //12P5 IRIS_INT32 V12P5_Test_Value;
	BYTE_SWAP_COPY_32(&V12P5_Test_Value, pktPtr);
	pktPtr += 4;

  //5VA IRIS_UINT16 V5VA_Test_Counts;
	BYTE_SWAP_COPY_16(&V5VA_Test_Counts, pktPtr);
	pktPtr += 2;

  //5VA IRIS_INT32 V5VA_Test_Value;
	BYTE_SWAP_COPY_32(&V5VA_Test_Value, pktPtr);
	pktPtr += 4;

  //6VA IRIS_UINT16 V6VA_Test_Counts;
	BYTE_SWAP_COPY_16(&V6VA_Test_Counts, pktPtr);
	pktPtr += 2;

  //6VA IRIS_INT32 V6VA_Test_Value;
	BYTE_SWAP_COPY_32(&V6VA_Test_Value, pktPtr);
	pktPtr += 4;

  //N6VA IRIS_UINT16 N6VA_Test_Counts;
	BYTE_SWAP_COPY_16(&N6VA_Test_Counts, pktPtr);
	pktPtr += 2;

  //N6VA IRIS_INT32 N6VA_Test_Value;
	BYTE_SWAP_COPY_32(&N6VA_Test_Value, pktPtr);
	pktPtr += 4;

  //5P5VA IRIS_UINT16 V5P5VA_Test_Counts;
	BYTE_SWAP_COPY_16(&V5P5VA_Test_Counts, pktPtr);
	pktPtr += 2;

  //5P5VA IRIS_INT32 V5P5VA_Test_Value;
	BYTE_SWAP_COPY_32(&V5P5VA_Test_Value, pktPtr);
	pktPtr += 4;

  //9VA IRIS_UINT16 V9_TestA_Counts;
	BYTE_SWAP_COPY_16(&V9_TestA_Counts, pktPtr);
	pktPtr += 2;

  //9VA IRIS_INT32 V9_TestA_Value;
	BYTE_SWAP_COPY_32(&V9_TestA_Value, pktPtr);
	pktPtr += 4;

  //9VB IRIS_UINT16 V9_TestB_Counts;
	BYTE_SWAP_COPY_16(&V9_TestB_Counts, pktPtr);
	pktPtr += 2;

  //9VB IRIS_INT32 V9_TestB_Value; 
	BYTE_SWAP_COPY_32(&V9_TestB_Value, pktPtr);
	pktPtr += 4;
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_ChannelConfigurations::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  	//Expiratory Pressure IRIS_UINT16 InspPressureCounts;
	BYTE_SWAP_COPY_16(pktPtr, &InspPressureCounts);
	pktPtr += 2;
	t.TRACEY ("InspPressureCounts: %d\n", InspPressureCounts);
	
  //Expiratory Pressure IRIS_INT16 InspPressureValue;
	BYTE_SWAP_COPY_16(pktPtr, &InspPressureValue,);
	pktPtr += 2;
	t.TRACEY ("InspPressureValue: %d\n", InspPressureValue);

  //Aux Pressure IRIS_UINT16 AuxPressureCounts;
	BYTE_SWAP_COPY_16(pktPtr, &AuxPressureCounts);
	pktPtr += 2;
	t.TRACEY ("AuxPressureCounts: %d\n", AuxPressureCounts);

  //Aux Pressure IRIS_INT16 AuxPressureValue;
	BYTE_SWAP_COPY_16(pktPtr, &AuxPressureValue);
	pktPtr += 2;
	t.TRACEY ("AuxPressureValue: %d\n", AuxPressureValue);

  //Exhalation Valve Drive Voltage IRIS_UINT16 ExhValveVoltageCounts;
	BYTE_SWAP_COPY_16(pktPtr, &ExhValveVoltageCounts);
	pktPtr += 2;
	t.TRACEY ("ExhValveVoltageCounts: %d\n", ExhValveVoltageCounts);

  //Exhalation Valve Drive Voltage IRIS_INT32 ExhValveVoltageValue;
	BYTE_SWAP_COPY_32(pktPtr, &ExhValveVoltageValue);
	pktPtr += 4;
	t.TRACEY ("ExhValveVoltageValue: %d\n", ExhValveVoltageValue);

  //Exhalation Valve Drive Current IRIS_UINT16 ExhValveCurrentCounts;
	BYTE_SWAP_COPY_16(pktPtr, &ExhValveCurrentCounts);
	pktPtr += 2;
	t.TRACEY ("ExhValveCurrentCounts: %d\n", ExhValveCurrentCounts);

  //Exhalation Valve Drive Current IRIS_INT32 ExhValveCurrentValue;
	BYTE_SWAP_COPY_32(pktPtr, &ExhValveCurrentValue);
	pktPtr += 4;
	t.TRACEY ("ExhValveCurrentValue: %d\n", ExhValveCurrentValue);

  //Secondary Voltage Reference IRIS_UINT16 V4096refCounts;
	BYTE_SWAP_COPY_16(pktPtr, &V4096refCounts);
	pktPtr += 2;
	t.TRACEY ("V4096refCounts: %d\n", V4096refCounts);

  //Secondary Voltage Reference IRIS_INT32 V4096refValue;
	BYTE_SWAP_COPY_32(pktPtr, &V4096refValue);
	pktPtr += 4;
	t.TRACEY ("V4096refValue: %d\n", V4096refValue);

  //Analog Ground IRIS_UINT16 MUXA_AGND_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &MUXA_AGND_Counts);
	pktPtr += 2;
	t.TRACEY ("MUXA_AGND_Counts: %d\n", MUXA_AGND_Counts);

  //Analog Ground IRIS_INT32 MUXA_AGND_Value;
	BYTE_SWAP_COPY_32(pktPtr, &MUXA_AGND_Value);
	pktPtr += 4;
	t.TRACEY ("MUXA_AGND_Value: %d\n", MUXA_AGND_Value);

  //Analog Ground IRIS_UINT16 MUXB_AGND_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &MUXB_AGND_Counts);
	pktPtr += 2;
	t.TRACEY ("MUXB_AGND_Counts: %d\n", MUXB_AGND_Counts);

  //Analog Ground IRIS_INT32 MUXB_AGND_Value;
	BYTE_SWAP_COPY_32(pktPtr, &MUXB_AGND_Value);
	pktPtr += 4;
	t.TRACEY ("MUXB_AGND_Value: %d\n", MUXB_AGND_Value);

  //Analog Ground IRIS_UINT16 ADC_AGND_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &ADC_AGND_Counts);
	pktPtr += 2;
	t.TRACEY ("ADC_AGND_Counts: %d\n", ADC_AGND_Counts);

  //Analog Ground IRIS_INT32 ADC_AGND_Value;
	BYTE_SWAP_COPY_32(pktPtr, &ADC_AGND_Value);
	pktPtr += 4;
	t.TRACEY ("ADC_AGND_Value: %d\n", ADC_AGND_Value);

  //Oxygen Valve Drive Current IRIS_UINT16 O2ValveCurrentCounts;
	BYTE_SWAP_COPY_16(pktPtr, &O2ValveCurrentCounts);
	pktPtr += 2;
	t.TRACEY ("O2ValveCurrentCounts: %d\n", O2ValveCurrentCounts);

  //Oxygen Valve Drive Current IRIS_INT32 O2ValveCurrentValue;
	BYTE_SWAP_COPY_32(pktPtr, &O2ValveCurrentValue);
	pktPtr += 4;
	t.TRACEY ("O2ValveCurrentValue: %d\n", O2ValveCurrentValue);

  //Air Valve Current Counts IRIS_UINT16 AirValveCurrentCounts;
	BYTE_SWAP_COPY_16(pktPtr, &AirValveCurrentCounts);
	pktPtr += 2;
	t.TRACEY ("AirValveCurrentCounts: %d\n", AirValveCurrentCounts);

  //Air Valve Current Counts IRIS_INT32 AirValveCurrentValue;
	BYTE_SWAP_COPY_32(pktPtr, &AirValveCurrentValue);
	pktPtr += 4;
  t.TRACEY ("AirValveCurrentValue: %d\n", AirValveCurrentValue);

  //Nebulizer Supply Voltage IRIS_UINT16 V9Test_C_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &V9Test_C_Counts);
	pktPtr += 2;
  t.TRACEY ("V9Test_C_Counts: %d\n", V9Test_C_Counts);

  //Nebulizer Supply Voltage IRIS_INT32 V9Test_C_Value;
	BYTE_SWAP_COPY_32(pktPtr, &V9Test_C_Value);
	pktPtr += 4;
	t.TRACEY ("V9Test_C_Value: %d\n", V9Test_C_Value);

  //Ambient Temperature Near Valves IRIS_UINT16 AmbientTempCounts;
	BYTE_SWAP_COPY_16(pktPtr, &AmbientTempCounts);
	pktPtr += 2;
	t.TRACEY ("AmbientTempCounts: %d\n", AmbientTempCounts);

  //Ambient Temperature Near Valves IRIS_INT32 AmbientTempValue;
	BYTE_SWAP_COPY_32(pktPtr, &AmbientTempValue);
	pktPtr += 4;
	t.TRACEY ("AmbientTempValue: %d\n", AmbientTempValue);

  //Mod Power Fail IRIS_UINT16 ModPwrFailCounts;
	BYTE_SWAP_COPY_16(pktPtr, &ModPwrFailCounts);
	pktPtr += 2;
	t.TRACEY ("ModPwrFailCounts: %d\n", ModPwrFailCounts);

  //Mod Power Fail IRIS_INT32 ModPwrFailValue;
	BYTE_SWAP_COPY_32(pktPtr, &ModPwrFailValue);
	pktPtr += 4;
	t.TRACEY ("ModPwrFailValue: %d\n", ModPwrFailValue);

  //12P5 IRIS_UINT16 V12P5_Test_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &V12P5_Test_Counts);
	pktPtr += 2;
	t.TRACEY ("V12P5_Test_Counts: %d\n", V12P5_Test_Counts);

  //12P5 IRIS_INT32 V12P5_Test_Value;
	BYTE_SWAP_COPY_32(pktPtr, &V12P5_Test_Value);
	pktPtr += 4;
	t.TRACEY ("V12P5_Test_Value: %d\n", V12P5_Test_Value);

  //5VA IRIS_UINT16 V5VA_Test_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &V5VA_Test_Counts);
	pktPtr += 2;
	t.TRACEY ("V5VA_Test_Counts: %d\n", V5VA_Test_Counts);

  //5VA IRIS_INT32 V5VA_Test_Value;
	BYTE_SWAP_COPY_32(pktPtr, &V5VA_Test_Value);
	pktPtr += 4;
	t.TRACEY ("V5VA_Test_Value: %d\n", V5VA_Test_Value);

  //6VA IRIS_UINT16 V6VA_Test_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &V6VA_Test_Counts);
	pktPtr += 2;
	t.TRACEY ("V6VA_Test_Counts: %d\n", V6VA_Test_Counts);

  //6VA IRIS_INT32 V6VA_Test_Value;
	BYTE_SWAP_COPY_32(pktPtr, &V6VA_Test_Value);
	pktPtr += 4;
	t.TRACEY ("V6VA_Test_Value: %d\n", V6VA_Test_Value);

  //N6VA IRIS_UINT16 N6VA_Test_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &N6VA_Test_Counts);
	pktPtr += 2;
	t.TRACEY ("N6VA_Test_Counts: %d\n", N6VA_Test_Counts);

  //N6VA IRIS_INT32 N6VA_Test_Value;
	BYTE_SWAP_COPY_32(pktPtr, &N6VA_Test_Value);
	pktPtr += 4;
	t.TRACEY ("N6VA_Test_Value: %d\n", N6VA_Test_Value);

  //5P5VA IRIS_UINT16 V5P5VA_Test_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &V5P5VA_Test_Counts);
	pktPtr += 2;
	t.TRACEY ("V5P5VA_Test_Counts: %d\n", V5P5VA_Test_Counts);

  //5P5VA IRIS_INT32 V5P5VA_Test_Value;
	BYTE_SWAP_COPY_32(pktPtr, &V5P5VA_Test_Value);
	pktPtr += 4;
	t.TRACEY ("V5P5VA_Test_Value: %d\n", V5P5VA_Test_Value);

  //9VA IRIS_UINT16 V9_TestA_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &V9_TestA_Counts);
	pktPtr += 2;
	t.TRACEY ("V9_TestA_Counts: %d\n", V9_TestA_Counts);

  //9VA IRIS_INT32 V9_TestA_Value;
	BYTE_SWAP_COPY_32(pktPtr, &V9_TestA_Value);
	pktPtr += 4;
	t.TRACEY ("V9_TestA_Value: %d\n", V9_TestA_Value);

  //9VB IRIS_UINT16 V9_TestB_Counts;
	BYTE_SWAP_COPY_16(pktPtr, &V9_TestB_Counts);
	pktPtr += 2;
	t.TRACEY ("V9_TestB_Counts: %d\n", V9_TestB_Counts);

  //9VB IRIS_INT32 V9_TestB_Value; 
	BYTE_SWAP_COPY_32(pktPtr, &V9_TestB_Value);
	pktPtr += 4;
	t.TRACEY ("V9_TestB_Value: %d\n", V9_TestB_Value);
	
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_ChannelConfigurations::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_INPUT_SIGNAL_LATCH_ID 35
const int VcbTest_InputSignalLatch::msgID = VCB_TEST_INPUT_SIGNAL_LATCH_ID;

const char VcbTest_InputSignalLatch::nameStr[] = "VcbTest_InputSignalLatch";

/*
Provides type of Sensor, Software, Hardware, Version, Units, Factor, 
Overflow, Sensitivity, Reference Temperature, Factor temperature, 
Sensor Serial Number, Current Temperature value, and Sensor Flow value. 
*/

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_InputSignalLatch::VcbTest_InputSignalLatch() :
    Message(VCB_TEST_INPUT_SIGNAL_LATCH_ID , 11)
// ID and Serialized Size (auto generated literals)
{}

void byteSwapCopy8 (void *src, void *dest)
{
  *((IRIS_UBYTE *)dest) = *((IRIS_UBYTE *)src);  
}

/*************************************************
*************************************************/
int VcbTest_InputSignalLatch::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
  // BYTE_SWAP_COPY_16(&ModPwrFail, pktPtr);
	byteSwapCopy8 (&ModPwrFail, pktPtr);
	//pktPtr[nArrPointer] = ModPwrFail;	
	pktPtr += 1;	
  //t.TRACEY ("ModPwrFail: %d\n", ModPwrFail);

  // BYTE_SWAP_COPY_16(&PsmPwrFail, pktPtr);
	byteSwapCopy8(&PsmPwrFail, pktPtr);
  //pktPtr[nArrPointer] = PsmPwrFail;	
	pktPtr += 1;
	//t.TRACEY ("PsmPwrFail: %d\n", PsmPwrFail);

  // BYTE_SWAP_COPY_16(&OverPress, pktPtr);
	byteSwapCopy8(&OverPress, pktPtr);
	//pktPtr[nArrPointer] = OverPress;	
	pktPtr += 1;
	//t.TRACEY ("OverPress: %d\n", OverPress);
	
  // BYTE_SWAP_COPY_16(&ZeroExppOn, pktPtr);
	byteSwapCopy8(&ZeroExppOn, pktPtr);
  //pktPtr[nArrPointer] = ZeroExppOn;	
	pktPtr += 1;
	//t.TRACEY ("ZeroExppOn: %d\n", ZeroExppOn);

  // BYTE_SWAP_COPY_16(&VmBuzzerOn, pktPtr);
	byteSwapCopy8(&VmBuzzerOn, pktPtr);
	//pktPtr[nArrPointer] = VmBuzzerOn;	
  pktPtr += 1;
	//t.TRACEY ("VmBuzzerOn: %d\n", VmBuzzerOn);

  // BYTE_SWAP_COPY_16(&NebSnse1, pktPtr);
	byteSwapCopy8(&NebSnse1, pktPtr);
	//pktPtr[nArrPointer] = NebSnse1;	
  pktPtr += 1;
	//t.TRACEY ("NebSnse1: %d\n", NebSnse1);

	// BYTE_SWAP_COPY_16(&NebSnse2, pktPtr);
	byteSwapCopy8(&NebSnse2, pktPtr);
	//pktPtr[nArrPointer] = NebSnse2;	
  pktPtr += 1;
	//t.TRACEY ("NebSnse2: %d\n", NebSnse2);

	//BYTE_SWAP_COPY_16(&ExpPwrFail, pktPtr);
	byteSwapCopy8(&ExpPwrFail, pktPtr);
	//pktPtr[nArrPointer] = ExpPwrFail;	
  pktPtr += 1;
	//t.TRACEY ("ExpPwrFail: %d\n", ExpPwrFail);

	//BYTE_SWAP_COPY_16(&BuzzerSnse, pktPtr);
	byteSwapCopy8(&BuzzerSnse, pktPtr);
	//pktPtr[nArrPointer] = BuzzerSnse;	
  pktPtr += 1;
	//t.TRACEY ("BuzzerSnse: %d\n", BuzzerSnse);

	//BYTE_SWAP_COPY_16(&ZeroAuxPOn, pktPtr);
	byteSwapCopy8(&ZeroAuxPOn, pktPtr);
	//pktPtr[nArrPointer] = ZeroAuxPOn;	
  pktPtr += 1;
	//t.TRACEY ("ZeroAuxPOn: %d\n", ZeroAuxPOn);
  
	//BYTE_SWAP_COPY_16(&VmExhalOpen, pktPtr);
	byteSwapCopy8(&VmExhalOpen, pktPtr);
	//pktPtr[nArrPointer] = VmExhalOpen;	
  pktPtr += 1;
	//t.TRACEY ("VmExhalOpen: %d\n", VmExhalOpen);
	
  
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_InputSignalLatch::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  byteSwapCopy8(pktPtr, &ModPwrFail);
  pktPtr += 1;	
  t.TRACEY ("ModPwrFail: %d\n", ModPwrFail);
	
  byteSwapCopy8(pktPtr, &PsmPwrFail);
  pktPtr += 1;
	t.TRACEY ("PsmPwrFail: %d\n", PsmPwrFail);

  byteSwapCopy8(pktPtr, &OverPress);
  pktPtr += 1;
	t.TRACEY ("OverPress: %d\n", OverPress);
	
  byteSwapCopy8(pktPtr, &ZeroExppOn);
  pktPtr += 1;
	t.TRACEY ("ZeroExppOn: %d\n", ZeroExppOn);

  byteSwapCopy8(pktPtr, &VmBuzzerOn);
  pktPtr += 1;
	t.TRACEY ("VmBuzzerOn: %d\n", VmBuzzerOn);

  byteSwapCopy8(pktPtr, &NebSnse1);
  pktPtr += 1	;
	t.TRACEY ("NebSnse1: %d\n", NebSnse1);

	byteSwapCopy8(pktPtr, &NebSnse2);
  pktPtr += 1	;
	t.TRACEY ("NebSnse2: %d\n", NebSnse2);

	byteSwapCopy8(pktPtr, &ExpPwrFail);
  pktPtr += 1	;
	t.TRACEY ("ExpPwrFail: %d\n", ExpPwrFail);

	byteSwapCopy8(pktPtr, &BuzzerSnse);
  pktPtr += 1	;
	t.TRACEY ("BuzzerSnse: %d\n", BuzzerSnse);

	byteSwapCopy8(pktPtr, &ZeroAuxPOn);
  pktPtr += 1	;
	t.TRACEY ("ZeroAuxPOn: %d\n", ZeroAuxPOn);

	byteSwapCopy8(pktPtr, &VmExhalOpen);
  pktPtr += 1	;
	t.TRACEY ("VmExhalOpen: %d\n", VmExhalOpen);

  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_InputSignalLatch::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_PING_CALIBRATION_STATUS_ID 36
const int VcbTest_PingCalibrationStatus::msgID = VCB_TEST_PING_CALIBRATION_STATUS_ID;

const char VcbTest_PingCalibrationStatus::nameStr[] = "VcbTest_PingCalibrationStatus";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_PingCalibrationStatus::VcbTest_PingCalibrationStatus() :
    Message(VCB_TEST_PING_CALIBRATION_STATUS_ID , 43)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_PingCalibrationStatus::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	// Current running calibration 
  //IRIS_BYTE CalStatus[40];
  for (int i=0; i<40; i++)
	{		
		// BYTE_SWAP_COPY_16(&CalStatus[i], pktPtr);
		byteSwapCopy8(&CalStatus[i], pktPtr);
    pktPtr++;    
	}
		
	//Pass Fail running calibration   
	*pktPtr = PassFailStatus;//IRIS_UBYTE 
  pktPtr++;
  
	//Percentage complete of current running calibration 
  //IRIS_UINT16 CalPercent;
	BYTE_SWAP_COPY_16(&CalPercent, pktPtr);
	pktPtr += 2;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated
}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_PingCalibrationStatus::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  //byteSwapCopy8(pktPtr, &ModPwrFail);
  //pktPtr += 1;	
  //t.TRACEY ("ModPwrFail: %d\n", ModPwrFail);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_PingCalibrationStatus::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_OTHER_VCB_DATA_ID 37
const int VcbTest_OtherVcbData::msgID = VCB_TEST_OTHER_VCB_DATA_ID;

const char VcbTest_OtherVcbData::nameStr[] = "VcbTest_OtherVcbData";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_OtherVcbData::VcbTest_OtherVcbData() :
    Message(VCB_TEST_OTHER_VCB_DATA_ID , 30)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_OtherVcbData::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  /* Vcb Vmb Crc errors */
  //IRIS_UINT32 VmbVcbCommErrors;
	BYTE_SWAP_COPY_32(&VmbVcbCommErrors, pktPtr);	
  pktPtr += 4;

  /* Cpu Loading Average  */
  //IRIS_UINT16 CpuLoadAvg;
  BYTE_SWAP_COPY_16(&CpuLoadAvg, pktPtr);	
  pktPtr += 2;

  /* Compensated O2 Value  */
  //IRIS_INT16 O2Comp;
  BYTE_SWAP_COPY_16(&O2Comp, pktPtr);	
  pktPtr += 2;

  //IRIS_UINT32 VCBTechnicalAlarmStatus1;
	BYTE_SWAP_COPY_32(&VCBTechnicalAlarmStatus1, pktPtr);	
  pktPtr += 4;

  /*Bit 8: Exp Flow Sensor Zeroing Error */
  //IRIS_UINT32 VCBTechnicalAlarmStatus2;
	BYTE_SWAP_COPY_32(&VCBTechnicalAlarmStatus2, pktPtr);	
  pktPtr += 4;

  /* Parameter alarm status bits reported by the VCB. */
  //IRIS_UINT32 VCBParameterAlarmStatus;
	BYTE_SWAP_COPY_32(&VCBParameterAlarmStatus, pktPtr);	
  pktPtr += 4;

  /*
  Monitors our waveform submission to see if we are sending data, 
  at the desired 5Hz rate. It is measured as millisecond deviation, 
  from the expected 200ms per transmission. 
  */
  //IRIS_UINT16 WaveformJitter;
	BYTE_SWAP_COPY_16(&WaveformJitter, pktPtr);	
  pktPtr += 2;

  /*
  Maximum deviation from expected 500ms timeframe for vent parameters 
  message. 
  */
  // IRIS_UINT16 MaxVentParamJitter;
	BYTE_SWAP_COPY_16(&MaxVentParamJitter, pktPtr);	
  pktPtr += 2;

  /* Average jitter over 1 minute. */
  //IRIS_UINT16 AvgVentParamJitter;
	BYTE_SWAP_COPY_16(&AvgVentParamJitter, pktPtr);	
  pktPtr += 2;

  /* Maximum deviation from expected 1s timeframe for system state message. */
  //IRIS_UINT16 MaxSysStateJitter;
	BYTE_SWAP_COPY_16(&MaxSysStateJitter, pktPtr);	
  pktPtr += 2;

  /* Average jitter over 1 minute. */
  //IRIS_UINT16 AvgSysStateJitter;
	BYTE_SWAP_COPY_16(&AvgSysStateJitter, pktPtr);	
  pktPtr += 2;
  
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_OtherVcbData::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

    /* Vcb Vmb Crc errors */
  //IRIS_UINT32 VmbVcbCommErrors;
	BYTE_SWAP_COPY_32(pktPtr, &VmbVcbCommErrors);
  pktPtr += 4;
	//t.TRACEY ("VmbVcbCommErrors: %d\n", (int)VmbVcbCommErrors);

  /* Cpu Loading Average  */
  //IRIS_UINT16 CpuLoadAvg;
  BYTE_SWAP_COPY_16(pktPtr, &CpuLoadAvg);	
  pktPtr += 2;
	VcbOtherVcbDataStruct.CpuLoadAvg = CpuLoadAvg;
	t.TRACEY ("CpuLoadAvg: %d\n", CpuLoadAvg);

  /* Compensated O2 Value  */
  //IRIS_INT16 O2Comp;
  BYTE_SWAP_COPY_16(pktPtr, &O2Comp);	
  pktPtr += 2;
	VcbOtherVcbDataStruct.O2Comp = O2Comp;
	//t.TRACEY ("O2Comp: %d\n", O2Comp);

  //IRIS_UINT32 VCBTechnicalAlarmStatus1;
	BYTE_SWAP_COPY_32(pktPtr, &VCBTechnicalAlarmStatus1);	
  pktPtr += 4;
  //t.TRACEY ("VCBTechnicalAlarmStatus1: %d\n", (int)VCBTechnicalAlarmStatus1);

  /*Bit 8: Exp Flow Sensor Zeroing Error */
  //IRIS_UINT32 VCBTechnicalAlarmStatus2;
	BYTE_SWAP_COPY_32(pktPtr, &VCBTechnicalAlarmStatus2);	
  pktPtr += 4;
	//t.TRACEY ("VCBTechnicalAlarmStatus2: %d\n", (int)VCBTechnicalAlarmStatus2);

  /* Parameter alarm status bits reported by the VCB. */
  //IRIS_UINT32 VCBParameterAlarmStatus;
	BYTE_SWAP_COPY_32(pktPtr, &VCBParameterAlarmStatus);	
  pktPtr += 4;
	//t.TRACEY ("VCBParameterAlarmStatus: %d\n", (int)VCBParameterAlarmStatus);

  /*
  Monitors our waveform submission to see if we are sending data, 
  at the desired 5Hz rate. It is measured as millisecond deviation, 
  from the expected 200ms per transmission. 
  */
  //IRIS_UINT16 WaveformJitter;
	BYTE_SWAP_COPY_16(pktPtr, &WaveformJitter);	
  pktPtr += 2;
	//t.TRACEY ("WaveformJitter: %d\n", WaveformJitter);

  /*
  Maximum deviation from expected 500ms timeframe for vent parameters 
  message. 
  */
  // IRIS_UINT16 MaxVentParamJitter;
	BYTE_SWAP_COPY_16(pktPtr, &MaxVentParamJitter);	
  pktPtr += 2;
	//t.TRACEY ("MaxVentParamJitter: %d\n", MaxVentParamJitter);

  /* Average jitter over 1 minute. */
  //IRIS_UINT16 AvgVentParamJitter;
	BYTE_SWAP_COPY_16(pktPtr, &AvgVentParamJitter);	
  pktPtr += 2;
	//t.TRACEY ("AvgVentParamJitter: %d\n", AvgVentParamJitter);

  /* Maximum deviation from expected 1s timeframe for system state message. */
  //IRIS_UINT16 MaxSysStateJitter;
	BYTE_SWAP_COPY_16(pktPtr, &MaxSysStateJitter);	
  pktPtr += 2;
	//t.TRACEY ("MaxSysStateJitter: %d\n", MaxSysStateJitter);

  /* Average jitter over 1 minute. */
  //IRIS_UINT16 AvgSysStateJitter;
	BYTE_SWAP_COPY_16(pktPtr, &AvgSysStateJitter);	
  pktPtr += 2;
	//t.TRACEY ("AvgSysStateJitter: %d\n", AvgSysStateJitter);

  //byteSwapCopy8(pktPtr, &ModPwrFail);
  //pktPtr += 1;	
  
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_OtherVcbData::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SYSTEM_STATE_ID 38
const int VcbTest_SystemState::msgID = VCB_TEST_SYSTEM_STATE_ID;

const char VcbTest_SystemState::nameStr[] = "VcbTest_SystemState";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SystemState::VcbTest_SystemState() :
    Message(VCB_TEST_SYSTEM_STATE_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SystemState::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
  
	*((IRIS_UBYTE *)pktPtr) = SystemState;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SystemState::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  SystemState = *pktPtr;

  switch(SystemState)
  {
    case 1:
			t.TRACEY ("SystemState: %d. Power Selftest\n", SystemState);  
      break;
    case 2:
			t.TRACEY ("SystemState: %d. Standby\n", SystemState);  
      break;
		case 3:
			t.TRACEY ("SystemState: %d. Checkout\n", SystemState);  
      break;
		case 4:
			t.TRACEY ("SystemState: %d. Therapy\n", SystemState);  
      break;
		case 5:
			t.TRACEY ("SystemState: %d. Monitoring\n", SystemState);  
      break;
    case 6:
			t.TRACEY ("SystemState: %d. Service\n", SystemState);  
      break;
    case 7:
			t.TRACEY ("SystemState: %d. Super User\n", SystemState);  
      break;
    case 8:
			t.TRACEY ("SystemState: %d. Software Update\n", SystemState);  
      break;
    case 9:
			t.TRACEY ("SystemState: %d. Failed\n", SystemState);  
      break;
		case 10:
			t.TRACEY ("SystemState: %d. Failed With Vent\n", SystemState);  
      break;
	
		default:
      t.TRACEY ("SystemState: %d. State UNKNOWN!\n", SystemState);  
  }

	
	
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SystemState::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_INTERRUPT_NUMBER_ID 39
const int VcbTest_InterruptNumber::msgID = VCB_TEST_INTERRUPT_NUMBER_ID;

const char VcbTest_InterruptNumber::nameStr[] = "VcbTest_InterruptNumber";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_InterruptNumber::VcbTest_InterruptNumber() :
    Message(VCB_TEST_INTERRUPT_NUMBER_ID , 4)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_InterruptNumber::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
   /*
  Number of Interrupts 
	IRIS_UINT32 Interrupt;
  */  
	BYTE_SWAP_COPY_32(&Interrupt, pktPtr);	
  pktPtr += 4;
	//t.TRACEY (": %d\n", );
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_InterruptNumber::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  BYTE_SWAP_COPY_32(pktPtr, &Interrupt);
  pktPtr += 4;	
  t.TRACEY ("VcbTest_InterruptNumber::Interrupt=%d\n", (int)Interrupt);
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_InterruptNumber::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_VCB_VMB_COMMON_ALARMS_ID 41
const int VcbTest_VcbVmbCommonAlarms::msgID = VCB_TEST_VCB_VMB_COMMON_ALARMS_ID;

const char VcbTest_VcbVmbCommonAlarms::nameStr[] = "VcbTest_VcbVmbCommonAlarms";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_VcbVmbCommonAlarms::VcbTest_VcbVmbCommonAlarms() :
    Message(VCB_TEST_VCB_VMB_COMMON_ALARMS_ID , 4)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_VcbVmbCommonAlarms::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer  
  /*
	 IRIS_UINT16 VcbCommonAlarms;
	 IRIS_UINT16 VmbCommonAlarms;
  */
	BYTE_SWAP_COPY_16(&VcbCommonAlarms, pktPtr);	
  pktPtr += 2;
	
	BYTE_SWAP_COPY_16(&VmbCommonAlarms, pktPtr);	
  pktPtr += 2;	
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_VcbVmbCommonAlarms::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  BYTE_SWAP_COPY_16(pktPtr, &VcbCommonAlarms);
  pktPtr += 2;
	
	BYTE_SWAP_COPY_16(pktPtr, &VmbCommonAlarms);
  pktPtr += 2;

  // t.TRACEY ("VcbTest_VcbVmbCommonAlarms::VcbCommonAlarms=%d\n", (int)VcbCommonAlarms);
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_VcbVmbCommonAlarms::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_SEND_AIRVLV_DAC_ID 43
const int VcbTest_SendAirvlvDac::msgID = VCB_TEST_SEND_AIRVLV_DAC_ID;

const char VcbTest_SendAirvlvDac::nameStr[] = "VcbTest_SendAirvlvDac";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SendAirvlvDac::VcbTest_SendAirvlvDac() :
    Message(VCB_TEST_SEND_AIRVLV_DAC_ID , 2)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SendAirvlvDac::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	BYTE_SWAP_COPY_16(&DAC_Value, pktPtr);	
  pktPtr += 2;
	//t.TRACEY (": %d\n", );
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SendAirvlvDac::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  BYTE_SWAP_COPY_16(pktPtr, &DAC_Value);
  pktPtr += 1;	
  t.TRACEY ("SendAirvlvDac::DAC_Value=%d\n", DAC_Value);
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SendAirvlvDac::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SEND_O2VLV_DAC_ID 44
const int VcbTest_SendO2vlvDac::msgID = VCB_TEST_SEND_O2VLV_DAC_ID;

const char VcbTest_SendO2vlvDac::nameStr[] = "VcbTest_SendO2vlvDac";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SendO2vlvDac::VcbTest_SendO2vlvDac() :
    Message(VCB_TEST_SEND_O2VLV_DAC_ID , 2)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SendO2vlvDac::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	BYTE_SWAP_COPY_16(&DAC_Value, pktPtr);	
  pktPtr += 2;
	//t.TRACEY (": %d\n", );
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SendO2vlvDac::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  BYTE_SWAP_COPY_16(pktPtr, &DAC_Value);
  pktPtr += 1;	
  t.TRACEY ("VcbTest_SendO2vlvDac::DAC_Value=%d\n", DAC_Value);
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SendO2vlvDac::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SEND_EXHVLV_DAC_ID 45
const int VcbTest_SendExhvlvDac::msgID = VCB_TEST_SEND_EXHVLV_DAC_ID;

const char VcbTest_SendExhvlvDac::nameStr[] = "VcbTest_SendExhvlvDac";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SendExhvlvDac::VcbTest_SendExhvlvDac() :
    Message(VCB_TEST_SEND_EXHVLV_DAC_ID , 2)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SendExhvlvDac::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	BYTE_SWAP_COPY_16(&DAC_Value, pktPtr);	
  pktPtr += 2;
	//t.TRACEY (": %d\n", );
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SendExhvlvDac::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  BYTE_SWAP_COPY_16(pktPtr, &DAC_Value);
  pktPtr += 1;	
  t.TRACEY ("VcbTest_SendExhvlvDac::DAC_Value=%d\n", DAC_Value);
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SendExhvlvDac::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_SEND_EXHVLV_DITHER_DAC_ID 46
const int VcbTest_SendExhvlvDitherDac::msgID = VCB_TEST_SEND_EXHVLV_DITHER_DAC_ID;

const char VcbTest_SendExhvlvDitherDac::nameStr[] = "VcbTest_SendExhvlvDitherDac";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SendExhvlvDitherDac::VcbTest_SendExhvlvDitherDac() :
    Message(VCB_TEST_SEND_EXHVLV_DITHER_DAC_ID , 2)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SendExhvlvDitherDac::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	BYTE_SWAP_COPY_16(&DAC_Value, pktPtr);	
  pktPtr += 2;
	//t.TRACEY (": %d\n", );
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SendExhvlvDitherDac::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  BYTE_SWAP_COPY_16(pktPtr, &DAC_Value);
  pktPtr += 1;	
  t.TRACEY ("VcbTest_SendExhvlvDitherDac::DAC_Value=%d\n", DAC_Value);
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SendExhvlvDitherDac::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_PWR_VMB_INTERNAL_ID 47
const int VcbTest_PwrVmbInternal::msgID = VCB_TEST_PWR_VMB_INTERNAL_ID;

const char VcbTest_PwrVmbInternal::nameStr[] = "VcbTest_PwrVmbInternal";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_PwrVmbInternal::VcbTest_PwrVmbInternal() :
    Message(VCB_TEST_PWR_VMB_INTERNAL_ID , 22)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_PwrVmbInternal::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  // IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16(&ExpAirwayPress, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 P12p5vBits;
	BYTE_SWAP_COPY_16(&P12p5vBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 P12p5vMv;
	BYTE_SWAP_COPY_16(&P12p5vMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 N5p5vBits;
	BYTE_SWAP_COPY_16(&N5p5vBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 N5p5vMv;
	BYTE_SWAP_COPY_16(&N5p5vMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 P5p5vBits;
	BYTE_SWAP_COPY_16(&P5p5vBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 P5p5vMv;
	BYTE_SWAP_COPY_16(&P5p5vMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 Vref122Bits;
	BYTE_SWAP_COPY_16(&Vref122Bits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 Vref122Mv;
	BYTE_SWAP_COPY_16(&Vref122Mv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 AgndBits;
	BYTE_SWAP_COPY_16(&AgndBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 AgndMv;
	BYTE_SWAP_COPY_16(&AgndMv, pktPtr);	
  pktPtr += 2;
	  
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_PwrVmbInternal::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  BYTE_SWAP_COPY_16(pktPtr, &ExpAirwayPress);	
  pktPtr += 2;
  //IRIS_UINT16 P12p5vBits;
	BYTE_SWAP_COPY_16(pktPtr, &P12p5vBits);	
  pktPtr += 2;
  //IRIS_UINT16 P12p5vMv;
	BYTE_SWAP_COPY_16(pktPtr, &P12p5vMv);	
  pktPtr += 2;
  //IRIS_UINT16 N5p5vBits;
	BYTE_SWAP_COPY_16(pktPtr, &N5p5vBits);	
  pktPtr += 2;
  //IRIS_UINT16 N5p5vMv;
	BYTE_SWAP_COPY_16(pktPtr, &N5p5vMv);	
  pktPtr += 2;
  //IRIS_UINT16 P5p5vBits;
	BYTE_SWAP_COPY_16(pktPtr, &P5p5vBits);	
  pktPtr += 2;
  //IRIS_UINT16 P5p5vMv;
	BYTE_SWAP_COPY_16(pktPtr, &P5p5vMv);	
  pktPtr += 2;
  //IRIS_UINT16 Vref122Bits;
	BYTE_SWAP_COPY_16(pktPtr, &Vref122Bits);	
  pktPtr += 2;
  //IRIS_UINT16 Vref122Mv;
	BYTE_SWAP_COPY_16(pktPtr, &Vref122Mv);	
  pktPtr += 2;
  //IRIS_UINT16 AgndBits;
	BYTE_SWAP_COPY_16(pktPtr, &AgndBits);	
  pktPtr += 2;
  //IRIS_UINT16 AgndMv;
	BYTE_SWAP_COPY_16(pktPtr, &AgndMv);	
  pktPtr += 2;
  
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_PwrVmbInternal::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_PWR_EXT_SENSOR_ID 48
const int VcbTest_PwrExtSensor::msgID = VCB_TEST_PWR_EXT_SENSOR_ID;

const char VcbTest_PwrExtSensor::nameStr[] = "VcbTest_PwrExtSensor";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_PwrExtSensor::VcbTest_PwrExtSensor() :
    Message(VCB_TEST_PWR_EXT_SENSOR_ID , 18)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_PwrExtSensor::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  // IRIS_INT16 ExpAirwayPress;

	//IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16(&ExpAirwayPress, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyBits;
	BYTE_SWAP_COPY_16(&AirSupplyBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyMv;
	BYTE_SWAP_COPY_16(&AirSupplyMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyBits;
	BYTE_SWAP_COPY_16(&O2SupplyBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyMv;
	BYTE_SWAP_COPY_16(&O2SupplyMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 O2ParaBits;
	BYTE_SWAP_COPY_16(&O2ParaBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 O2ParaMv;
	BYTE_SWAP_COPY_16(&O2ParaMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 ExFlowBits;
	BYTE_SWAP_COPY_16(&ExFlowBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 ExFlowMv;
	BYTE_SWAP_COPY_16(&ExFlowMv, pktPtr);	
  pktPtr += 2;
    
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_PwrExtSensor::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;
  
  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  // IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16(pktPtr, &ExpAirwayPress);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyBits;
	BYTE_SWAP_COPY_16(pktPtr, &AirSupplyBits);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyMv;
	BYTE_SWAP_COPY_16(pktPtr, &AirSupplyMv);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyBits;
	BYTE_SWAP_COPY_16(pktPtr, &O2SupplyBits);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyMv;
	BYTE_SWAP_COPY_16(pktPtr, &O2SupplyMv);	
  pktPtr += 2;
  //IRIS_UINT16 O2ParaBits;
	BYTE_SWAP_COPY_16(pktPtr, &O2ParaBits);	
  pktPtr += 2;
  //IRIS_UINT16 O2ParaMv;
	BYTE_SWAP_COPY_16(pktPtr, &O2ParaMv);	
  pktPtr += 2;
  //IRIS_UINT16 ExFlowBits;
	BYTE_SWAP_COPY_16(pktPtr, &ExFlowBits);	
  pktPtr += 2;
  //IRIS_UINT16 ExFlowMv;
	BYTE_SWAP_COPY_16(pktPtr, &ExFlowMv);	
  pktPtr += 2;
  
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_PwrExtSensor::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_PRESS_XDCR_OUT_ID 49
const int VcbTest_PressXdcrOut::msgID = VCB_TEST_PRESS_XDCR_OUT_ID;

const char VcbTest_PressXdcrOut::nameStr[] = "VcbTest_PressXdcrOut";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_PressXdcrOut::VcbTest_PressXdcrOut() :
    Message(VCB_TEST_PRESS_XDCR_OUT_ID , 16)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_PressXdcrOut::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer	
	//IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16(&ExpAirwayPress, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 ExpAirwayBitsMv;
	BYTE_SWAP_COPY_16(&ExpAirwayBitsMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 BaroBits;
	BYTE_SWAP_COPY_16(&BaroBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 BaroMv;
	BYTE_SWAP_COPY_16(&BaroMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyBits;
	BYTE_SWAP_COPY_16(&O2SupplyBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyMv;
	BYTE_SWAP_COPY_16(&O2SupplyMv, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyBits;
	BYTE_SWAP_COPY_16(&AirSupplyBits, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyMv;
	BYTE_SWAP_COPY_16(&AirSupplyMv, pktPtr);	
  pktPtr += 2;
    
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_PressXdcrOut::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;
  
  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  
	//IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16(pktPtr, &ExpAirwayPress);	
  pktPtr += 2;
  //IRIS_UINT16 ExpAirwayBitsMv;
	BYTE_SWAP_COPY_16(pktPtr, &ExpAirwayBitsMv);	
  pktPtr += 2;
  //IRIS_UINT16 BaroBits;
	BYTE_SWAP_COPY_16(pktPtr, &BaroBits);	
  pktPtr += 2;
  //IRIS_UINT16 BaroMv;
	BYTE_SWAP_COPY_16(pktPtr, &BaroMv);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyBits;
	BYTE_SWAP_COPY_16(pktPtr, &O2SupplyBits);	
  pktPtr += 2;
  //IRIS_UINT16 O2SupplyMv;
	BYTE_SWAP_COPY_16(pktPtr, &O2SupplyMv);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyBits;
	BYTE_SWAP_COPY_16(pktPtr, &AirSupplyBits);	
  pktPtr += 2;
  //IRIS_UINT16 AirSupplyMv;
	BYTE_SWAP_COPY_16(pktPtr, &AirSupplyMv);	
  pktPtr += 2;
  
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_PressXdcrOut::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_PORT_INPUT_ID 50
const int VcbTest_PortInput::msgID = VCB_TEST_PORT_INPUT_ID;

const char VcbTest_PortInput::nameStr[] = "VcbTest_PortInput";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_PortInput::VcbTest_PortInput() :
    Message(VCB_TEST_PORT_INPUT_ID , 6)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_PortInput::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
  
	// IRIS_INT16 ExpAirwayPress;	
	BYTE_SWAP_COPY_16(pktPtr, &ExpAirwayPress);	
  pktPtr += 2;
  //IRIS_UBYTE PortA;
	*((IRIS_UBYTE *)pktPtr) = PortA;
  pktPtr++;
  //IRIS_UBYTE PortB;
	*((IRIS_UBYTE *)pktPtr) = PortB;
  pktPtr++;
  //IRIS_UBYTE PortD;
	*((IRIS_UBYTE *)pktPtr) = PortD;
  pktPtr++;
  //IRIS_UBYTE PortE;
	*((IRIS_UBYTE *)pktPtr) = PortE;
  pktPtr++;
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_PortInput::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
		// IRIS_INT16 ExpAirwayPress;	
	BYTE_SWAP_COPY_16( &ExpAirwayPress, pktPtr);	
  pktPtr += 2;
  //IRIS_UBYTE PortA;
	PortA = *pktPtr;	
  pktPtr++;
  //IRIS_UBYTE PortB;
	PortB = *pktPtr;	
  pktPtr++;
  //IRIS_UBYTE PortD;
	PortD = *pktPtr;	
  pktPtr++;
  //IRIS_UBYTE PortE;
	PortE = *pktPtr;	
  pktPtr++;  
	
	//t.TRACEY ("VmbSystemState: %d\n", VmbSystemState);
	
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_PortInput::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_VMB_TASK_INFO_ID 52
const int VcbTest_VmbTaskInfo::msgID = VCB_TEST_VMB_TASK_INFO_ID;

const char VcbTest_VmbTaskInfo::nameStr[] = "VcbTest_VmbTaskInfo";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_VmbTaskInfo::VcbTest_VmbTaskInfo() :
    Message(VCB_TEST_VMB_TASK_INFO_ID , 4)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_VmbTaskInfo::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:  
	//IRIS_UINT16 TaskData1;
	BYTE_SWAP_COPY_16(pktPtr, &TaskData1);	
  pktPtr += 2;
  //IRIS_UBYTE TaskData2;
	*((IRIS_UBYTE *)pktPtr) = TaskData2;
  pktPtr++;
  //IRIS_UBYTE TaskData3;
	*((IRIS_UBYTE *)pktPtr) = TaskData3;
  pktPtr++;
	
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_VmbTaskInfo::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  //IRIS_UINT16 TaskData1;
	BYTE_SWAP_COPY_16( &TaskData1, pktPtr);	
  pktPtr += 2;
  //IRIS_UBYTE TaskData2;
	TaskData2 = *pktPtr;	
  pktPtr++;
  //IRIS_UBYTE TaskData3;
	TaskData3 = *pktPtr;	
  pktPtr++;
	
	//t.TRACEY ("VmbSystemState: %d\n", VmbSystemState);
	
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_VmbTaskInfo::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_PARACUBE_DATA_ID 53
const int VcbTest_ParacubeData::msgID = VCB_TEST_PARACUBE_DATA_ID;

const char VcbTest_ParacubeData::nameStr[] = "VcbTest_ParacubeData";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_ParacubeData::VcbTest_ParacubeData() :
    Message(VCB_TEST_PARACUBE_DATA_ID , 12)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_ParacubeData::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:  
	//IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16(pktPtr, &ExpAirwayPress);	
  pktPtr += 2;
  //IRIS_INT16 InspO2PctComp;
	BYTE_SWAP_COPY_16(pktPtr, &InspO2PctComp);	
  pktPtr += 2;
	//IRIS_UBYTE SerialNum[8];
	// *((IRIS_UBYTE *)pktPtr) = SerialNum; // ATTN! Has to be done!
  pktPtr++;
	
	t.TRACEY ("VcbTest_ParacubeData:: SerialNum = *pktPtr;	// ATTN! Has to be done!\n");

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_ParacubeData::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  //IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16( &ExpAirwayPress, pktPtr);	
  pktPtr += 2;
  //IRIS_INT16 InspO2PctComp;
	BYTE_SWAP_COPY_16( &InspO2PctComp, pktPtr);	
  pktPtr += 2;
	//IRIS_UBYTE SerialNum[8];
	// SerialNum = *pktPtr;	// ATTN! Has to be done!
  pktPtr++;
	
	t.TRACEY ("VcbTest_ParacubeData:: SerialNum = *pktPtr;	// ATTN! Has to be done!\n");
	
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_ParacubeData::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_ACUTRONICS_INFO_ID 54
const int VcbTest_AcutronicsInfo::msgID = VCB_TEST_ACUTRONICS_INFO_ID;

const char VcbTest_AcutronicsInfo::nameStr[] = "VcbTest_AcutronicsInfo";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_AcutronicsInfo::VcbTest_AcutronicsInfo() :
    Message(VCB_TEST_ACUTRONICS_INFO_ID , 4)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_AcutronicsInfo::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:  
	//IRIS_INT16 ExpAirwayPress;
	BYTE_SWAP_COPY_16(pktPtr, &ExpAirwayPress);	
  pktPtr += 2;
  //IRIS_UINT16 SoftwareVersion;
	BYTE_SWAP_COPY_16(pktPtr, &SoftwareVersion);	
  pktPtr += 2;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_AcutronicsInfo::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  //IRIS_INT16 ExpAirwayPress
	BYTE_SWAP_COPY_16( &ExpAirwayPress, pktPtr);	
  pktPtr += 2;
  //IRIS_UINT16 SoftwareVersion
	BYTE_SWAP_COPY_16( &SoftwareVersion, pktPtr);	
  pktPtr += 2;
	
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_AcutronicsInfo::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_VMB_SYSTEM_STATE_ID 55
const int VcbTest_VmbSystemState::msgID = VCB_TEST_SENSOR_DETAILS_ID;

const char VcbTest_VmbSystemState::nameStr[] = "VcbTest_VmbSystemState";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_VmbSystemState::VcbTest_VmbSystemState() :
    Message(VCB_TEST_SENSOR_DETAILS_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_VmbSystemState::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
  
	*((IRIS_UBYTE *)pktPtr) = VmbSystemState;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_VmbSystemState::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  VmbSystemState = *pktPtr;
  t.TRACEY ("VmbSystemState: %d\n", VmbSystemState);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_VmbSystemState::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}



/***************** START MESSAGE ******************/
//VCB_TEST_SYSTEM_CHECKS_DATA_ID 56
const int VcbTest_SystemChecksData::msgID = VCB_TEST_SYSTEM_CHECKS_DATA_ID;

const char VcbTest_SystemChecksData::nameStr[] = "VcbTest_SystemChecksData";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SystemChecksData::VcbTest_SystemChecksData() :
    Message(VCB_TEST_SYSTEM_CHECKS_DATA_ID , 14)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SystemChecksData::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  /*IRIS_UINT16 FlashPasses Number of VCB Flash passes*/
	BYTE_SWAP_COPY_16(&FlashPasses, pktPtr);	
  pktPtr += 2;  

  /*IRIS_UINT16 FlashFailures Number of VCB Flash failures*/  
  BYTE_SWAP_COPY_16(&FlashFailures, pktPtr);
	pktPtr += 2;

	/*IRIS_UINT16 SramPasses Number of SRAM passes*/  
  BYTE_SWAP_COPY_16(&SramPasses, pktPtr);
	pktPtr += 2;

	/*IRIS_UINT16 SramFailures Number of SRAM failures*/  
  BYTE_SWAP_COPY_16(&SramFailures, pktPtr);
  pktPtr += 2;

	/*IRIS_UINT16 EEPromPasses Number of EEProm passes*/
  BYTE_SWAP_COPY_16(&EEPromPasses, pktPtr);
  pktPtr += 2;

	/*IRIS_UINT16 EEPromFailures Number of EEProm failures*/  
	BYTE_SWAP_COPY_16(&EEPromFailures, pktPtr);
  pktPtr += 2;

  /*IRIS_INT16 TimerRatio Timer ratio*/
  BYTE_SWAP_COPY_16(&TimerRatio, pktPtr);	
  pktPtr += 2;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SystemChecksData::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  
  /*IRIS_UINT16 FlashPasses Number of VCB Flash passes*/
	BYTE_SWAP_COPY_16(pktPtr, &FlashPasses);
  pktPtr += 2;  
	t.TRACEY ("FlashPasses: %d\n", FlashPasses);

  /*IRIS_UINT16 FlashFailures Number of VCB Flash failures*/  
  BYTE_SWAP_COPY_16(pktPtr, &FlashFailures);
	pktPtr += 2;
	t.TRACEY ("FlashFailures: %d\n", FlashFailures);

	/*IRIS_UINT16 SramPasses Number of SRAM passes*/  
  BYTE_SWAP_COPY_16(pktPtr, &SramPasses);
	pktPtr += 2;
	t.TRACEY ("SramPasses: %d\n", SramPasses);

	/*IRIS_UINT16 SramFailures Number of SRAM failures*/  
  BYTE_SWAP_COPY_16(pktPtr, &SramFailures);
  pktPtr += 2;
	t.TRACEY ("SramFailures: %d\n", SramFailures);

	/*IRIS_UINT16 EEPromPasses Number of EEProm passes*/
  BYTE_SWAP_COPY_16(pktPtr, &EEPromPasses);
  pktPtr += 2;
	t.TRACEY ("EEPromPasses: %d\n", EEPromPasses);

	/*IRIS_UINT16 EEPromFailures Number of EEProm failures*/  
	BYTE_SWAP_COPY_16(pktPtr, &EEPromFailures);
  pktPtr += 2;
	t.TRACEY ("EEPromFailures: %d\n", EEPromFailures);

  /*IRIS_INT16 TimerRatio Timer ratio*/
  BYTE_SWAP_COPY_16(pktPtr, &TimerRatio);	
  pktPtr += 2;	
	t.TRACEY ("TimerRatio: %d\n", TimerRatio);
	
	return IRIS_NodeInterface::OK;
}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SystemChecksData::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_CHECKOUT_CIRCUIT_CHECK_ID 57
const int VcbTest_CheckoutCircuitCheck::msgID = VCB_TEST_CHECKOUT_CIRCUIT_CHECK_ID;

const char VcbTest_CheckoutCircuitCheck::nameStr[] = "VcbTest_CheckoutCircuitCheck";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_CheckoutCircuitCheck::VcbTest_CheckoutCircuitCheck() :
    Message(VCB_TEST_CHECKOUT_CIRCUIT_CHECK_ID , 12)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_CheckoutCircuitCheck::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  /*
  Leak   
  IRIS_UINT16 Leak;
  IRIS_UINT32 Resistance;
  IRIS_UINT32 Compliance;
  */  
	BYTE_SWAP_COPY_16(pktPtr, &Leak);
	pktPtr += 2;	

	BYTE_SWAP_COPY_32(pktPtr, &Resistance);
	pktPtr += 4;
	//t.TRACEY ("Resistance: %d\n", Resistance);
  
  BYTE_SWAP_COPY_32(pktPtr, &Compliance);
	pktPtr += 4;
	//t.TRACEY ("Compliance: %d\n", Compliance);
		
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_CheckoutCircuitCheck::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  
	BYTE_SWAP_COPY_16(&Leak, pktPtr);
	pktPtr += 2;	

	BYTE_SWAP_COPY_32(&Resistance, pktPtr);
	pktPtr += 4;	
  
  BYTE_SWAP_COPY_32(&Compliance, pktPtr);
	pktPtr += 4;
  
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_CheckoutCircuitCheck::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_REGULATOR_TEST_RESULTS_ID 60
const int VcbTest_RegulatorTestResults::msgID = VCB_TEST_REGULATOR_TEST_RESULTS_ID;

const char VcbTest_RegulatorTestResults::nameStr[] = "VcbTest_RegulatorTestResults";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_RegulatorTestResults::VcbTest_RegulatorTestResults() :
    Message(VCB_TEST_REGULATOR_TEST_RESULTS_ID , 24)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_RegulatorTestResults::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer 
  //IRIS_INT32 TotalFlowWithO2;
	BYTE_SWAP_COPY_32(pktPtr, &TotalFlowWithO2);
	pktPtr += 4;
  //IRIS_INT32 OxygenFlow;
	BYTE_SWAP_COPY_32(pktPtr, &OxygenFlow);
	pktPtr += 4;
	//IRIS_UINT16 OxygenPercError; 
	BYTE_SWAP_COPY_16(pktPtr, &OxygenPercError);
	pktPtr += 2;
	//IRIS_INT32 TotalFlowWithAir;
	BYTE_SWAP_COPY_32(pktPtr, &TotalFlowWithAir);
	pktPtr += 4;
	//IRIS_INT32 AirFlow;
	BYTE_SWAP_COPY_32(pktPtr, &AirFlow);
	pktPtr += 4;
	//IRIS_UINT16 AirPercError;
	BYTE_SWAP_COPY_16(pktPtr, &AirPercError);
	pktPtr += 2;
		
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_RegulatorTestResults::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;
	
  // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  //IRIS_INT32 TotalFlowWithO2;
	BYTE_SWAP_COPY_32(&TotalFlowWithO2, pktPtr);
	pktPtr += 4;
  //IRIS_INT32 OxygenFlow;
	BYTE_SWAP_COPY_32(&OxygenFlow, pktPtr);
	pktPtr += 4;
	//IRIS_UINT16 OxygenPercError; 
	BYTE_SWAP_COPY_16(&OxygenPercError, pktPtr);
	pktPtr += 2;
	//IRIS_INT32 TotalFlowWithAir;
	BYTE_SWAP_COPY_32(&TotalFlowWithAir, pktPtr);
	pktPtr += 4;
	//IRIS_INT32 AirFlow;
	BYTE_SWAP_COPY_32(&AirFlow, pktPtr);
	pktPtr += 4;
	//IRIS_UINT16 AirPercError;
	BYTE_SWAP_COPY_16(&AirPercError, pktPtr);
	pktPtr += 2;
  
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_RegulatorTestResults::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_SAFE_CLOSE_ID 67
const int VcbTest_SetSafeClose::msgID = VCB_TEST_SET_SAFE_CLOSE_ID;

const char VcbTest_SetSafeClose::nameStr[] = "VcbTest_SetSafeClose";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetSafeClose::VcbTest_SetSafeClose() :
    Message(VCB_TEST_SET_SAFE_CLOSE_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetSafeClose::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetSafeClose::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetSafeClose: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetSafeClose::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_MNVR_OPEN_ID 68
const int VcbTest_SetMnvrOpen::msgID = VCB_TEST_SET_MNVR_OPEN_ID;

const char VcbTest_SetMnvrOpen::nameStr[] = "VcbTest_SetMnvrOpen";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetMnvrOpen::VcbTest_SetMnvrOpen() :
    Message(VCB_TEST_SET_MNVR_OPEN_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetMnvrOpen::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetMnvrOpen::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetMnvrOpen: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetMnvrOpen::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_OK_TO_ZERO_ID 69
const int VcbTest_SetOkToZero::msgID = VCB_TEST_SET_OK_TO_ZERO_ID;

const char VcbTest_SetOkToZero::nameStr[] = "VcbTest_SetOkToZero";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetOkToZero::VcbTest_SetOkToZero() :
    Message(VCB_TEST_SET_OK_TO_ZERO_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetOkToZero::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetOkToZero::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetOkToZero: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetOkToZero::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_SW_LED_ID 70
const int VcbTest_SetSwLed::msgID = VCB_TEST_SET_SW_LED_ID;

const char VcbTest_SetSwLed::nameStr[] = "VcbTest_SetSwLed";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetSwLed::VcbTest_SetSwLed() :
    Message(VCB_TEST_SET_SW_LED_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetSwLed::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetSwLed::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetSwLed: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetSwLed::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_FS_PWR_EN_ID 71
const int VcbTest_SetFsPwrEn::msgID = VCB_TEST_SET_FS_PWR_EN_ID;

const char VcbTest_SetFsPwrEn::nameStr[] = "VcbTest_SetFsPwrEn";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetFsPwrEn::VcbTest_SetFsPwrEn() :
    Message(VCB_TEST_SET_FS_PWR_EN_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetFsPwrEn::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetFsPwrEn::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetFsPwrEn: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetFsPwrEn::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_NEB_ON_ID 72
const int VcbTest_SetNebOn::msgID = VCB_TEST_SET_NEB_ON_ID;

const char VcbTest_SetNebOn::nameStr[] = "VcbTest_SetNebOn";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetNebOn::VcbTest_SetNebOn() :
    Message(VCB_TEST_SET_NEB_ON_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetNebOn::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetNebOn::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetNebOn: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetNebOn::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_MBUS_RESET_ID 73
const int VcbTest_SetMbusReset::msgID = VCB_TEST_SET_MBUS_RESET_ID;

const char VcbTest_SetMbusReset::nameStr[] = "VcbTest_SetMbusReset";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetMbusReset::VcbTest_SetMbusReset() :
    Message(VCB_TEST_SET_MBUS_RESET_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetMbusReset::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetMbusReset::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetMbusReset: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetMbusReset::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}


/***************** START MESSAGE ******************/
// VCB_TEST_SET_ILIM_MOD_EN_ID 74
const int VcbTest_SetIlimModEn::msgID = VCB_TEST_SET_ILIM_MOD_EN_ID;

const char VcbTest_SetIlimModEn::nameStr[] = "VcbTest_SetIlimModEn";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetIlimModEn::VcbTest_SetIlimModEn() :
    Message(VCB_TEST_SET_ILIM_MOD_EN_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetIlimModEn::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetIlimModEn::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetIlimModEn: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetIlimModEn::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_ILIM_PSM_EN_ID 75
const int VcbTest_SetIlimPsmEn::msgID = VCB_TEST_SET_ILIM_PSM_EN_ID;

const char VcbTest_SetIlimPsmEn::nameStr[] = "VcbTest_SetIlimPsmEn";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetIlimPsmEn::VcbTest_SetIlimPsmEn() :
    Message(VCB_TEST_SET_ILIM_PSM_EN_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetIlimPsmEn::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetIlimPsmEn::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetIlimPsmEn: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetIlimPsmEn::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_WD_STRB_ID 76
const int VcbTest_SetWdStrb::msgID = VCB_TEST_SET_WD_STRB_ID;

const char VcbTest_SetWdStrb::nameStr[] = "VcbTest_SetWdStrb";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetWdStrb::VcbTest_SetWdStrb() :
    Message(VCB_TEST_SET_WD_STRB_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetWdStrb::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetWdStrb::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetWdStrb: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetWdStrb::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_EXP_ZERO_ID 77
const int VcbTest_SetExpZero::msgID = VCB_TEST_SET_EXP_ZERO_ID;

const char VcbTest_SetExpZero::nameStr[] = "VcbTest_SetExpZero";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetExpZero::VcbTest_SetExpZero() :
    Message(VCB_TEST_SET_EXP_ZERO_ID , 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetExpZero::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetExpZero::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetExpZero: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetExpZero::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_AUX_ZERO_ID 78
const int VcbTest_SetAuxZero::msgID = VCB_TEST_SET_AUX_ZERO_ID;

const char VcbTest_SetAuxZero::nameStr[] = "VcbTest_SetAuxZero";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetAuxZero::VcbTest_SetAuxZero() :
    Message(VCB_TEST_SET_AUX_ZERO_ID, 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetAuxZero::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetAuxZero::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetAuxZero: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetAuxZero::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_BUZZER_ID 79
const int VcbTest_SetBuzzer::msgID = VCB_TEST_SET_BUZZER_ID;

const char VcbTest_SetBuzzer::nameStr[] = "VcbTest_SetBuzzer";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetBuzzer::VcbTest_SetBuzzer() :
    Message(VCB_TEST_SET_BUZZER_ID, 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetBuzzer::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetBuzzer::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetBuzzer: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetBuzzer::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_AIR_VALVE_EN_ID 80
const int VcbTest_SetAirValveEn::msgID = VCB_TEST_SET_AIR_VALVE_EN_ID;

const char VcbTest_SetAirValveEn::nameStr[] = "VcbTest_SetAirValveEn";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetAirValveEn::VcbTest_SetAirValveEn() :
    Message(VCB_TEST_SET_AIR_VALVE_EN_ID, 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetAirValveEn::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetAirValveEn::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetAirValveEn: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetAirValveEn::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_O2_VALVE_EN_ID 81
const int VcbTest_SetO2ValveEn::msgID = VCB_TEST_SET_O2_VALVE_EN_ID;

const char VcbTest_SetO2ValveEn::nameStr[] = "VcbTest_SetO2ValveEn";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetO2ValveEn::VcbTest_SetO2ValveEn() :
    Message(VCB_TEST_SET_O2_VALVE_EN_ID, 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetO2ValveEn::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetO2ValveEn::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetO2ValveEn: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetO2ValveEn::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

/***************** START MESSAGE ******************/
// VCB_TEST_SET_EXH_VALVE_EN_ID 82
const int VcbTest_SetExhValveEn::msgID = VCB_TEST_SET_EXH_VALVE_EN_ID;

const char VcbTest_SetExhValveEn::nameStr[] = "VcbTest_SetExhValveEn";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SetExhValveEn::VcbTest_SetExhValveEn() :
    Message(VCB_TEST_SET_EXH_VALVE_EN_ID, 1)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SetExhValveEn::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer:
   /*
  Set to on off 
	IRIS_UBYTE Setting;
  */  
	*((IRIS_UBYTE *)pktPtr) = Setting;
  pktPtr++;

	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SetExhValveEn::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data
  Setting = *pktPtr;
  t.TRACEY ("VcbTest_SetExhValveEn: %d\n", Setting);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SetExhValveEn::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}
	
/***************** START MESSAGE ******************/
// VCB_TEST_E_E_PROM_TEST_PROGRESS_ID 84
const int VcbTest_EEPromTestProgress::msgID = VCB_TEST_E_E_PROM_TEST_PROGRESS_ID;

const char VcbTest_EEPromTestProgress::nameStr[] = "VcbTest_EEPromTestProgress";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_EEPromTestProgress::VcbTest_EEPromTestProgress() :
    Message(VCB_TEST_E_E_PROM_TEST_PROGRESS_ID , 2)	
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_EEPromTestProgress::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	/*IRIS_UINT16 Progress: Progress of the EEProm test */
  
	BYTE_SWAP_COPY_16(&Progress, pktPtr);
	pktPtr += 2;
		  
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_EEPromTestProgress::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  BYTE_SWAP_COPY_16(pktPtr, &Progress);
  pktPtr += 1;	
  t.TRACEY ("EEPROM_Progress: %d\n", Progress);
	
	return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_EEPromTestProgress::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}

#if 0
// !!! ATTN! - This is only a template for message implementation.

/***************** START MESSAGE ******************/
// VCB_TEST_SENSOR_DETAILS_ID 33
const int VcbTest_SensorDetails::msgID = VCB_TEST_SENSOR_DETAILS_ID;

const char VcbTest_SensorDetails::nameStr[] = "VcbTest_SensorDetails";

// Initialize the ID and serialized and de-serialized sizes
/*************************************************/
VcbTest_SensorDetails::VcbTest_SensorDetails() :
    Message(VCB_TEST_SENSOR_DETAILS_ID , 11)
// ID and Serialized Size (auto generated literals)
{}

/*************************************************
*************************************************/
int VcbTest_SensorDetails::serialize(IRIS_UBYTE *bufPtr)
{
  IRIS_UINT16 crc;
  IRIS_UBYTE *pktPtr = bufPtr;
  
	// Fill in the Message class info
  Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer
  
	BYTE_SWAP_COPY_16(&VmExhalOpen, pktPtr);	
  pktPtr += 2;
	//t.TRACEY (": %d\n", );
	BYTE_SWAP_COPY_32(&V9_TestA_Value, pktPtr);
	pktPtr += 4;
	  
	// Now add the CRC
  crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
  BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated

}

/*************************************************
*
*  Function name: deserialize
*
*  Parameter(s):  IRIS_UBYTE - pointer to the message 
*                   buffer IRIS_UINT32 - length of the 
*                   given buffer
*
*  Return type:   int - returns IRIS_OK or IRIS_CRC_FAIL
*
*  Author(s):     J Klaus
*
*  Purpose:       Takes a byte stream with multi-byte 
*                   types arranged in network orderand 
*                   fills in this Message object with 
*                   the data.
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
int VcbTest_SensorDetails::deserialize(IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
  IRIS_UINT16 calcCrc, rcedCrc;
  IRIS_UBYTE *pktPtr = bufPtr;

	// printf ("VcbTest_InputSignalLatch::deserialize - start\n");
	// printf ("VcbTest_InputSignalLatch. serializedSize=%d\n",serializedSize);
	
    // Restore the Message ID and check the CRC
  calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
  BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);// set received crc to network order
  
	//*************TRACE***************	
	//t.TRACEY ("calculated CRC: 0x%X\n", calcCrc);
	//t.TRACEY ("received   CRC: 0x%X\n", rcedCrc);
	//*********************************

  if(calcCrc != rcedCrc)
    return IRIS_NodeInterface::CRC_FAIL;

  // Copy individual members into the serial buffer
  pktPtr += 1;  // Skip past the Message class data

  //byteSwapCopy8(pktPtr, &ModPwrFail);
  //pktPtr += 1;	
  //t.TRACEY ("ModPwrFail: %d\n", ModPwrFail);
	  return IRIS_NodeInterface::OK;

}

/*************************************************
*
*  Function name: validate
*
*  Parameter(s):  void
*
*  Return type:   bool - logical 'isValid'
*
*  Author(s):     J Klaus
*
*  Purpose:       Validates the entire message as 
*                   a series of individual member validations
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
*
*************************************************/
bool VcbTest_SensorDetails::validate()
{
  bool retval = true; // Default to 'valid'

    // Call the individual validators
  
  return retval;
}
#endif