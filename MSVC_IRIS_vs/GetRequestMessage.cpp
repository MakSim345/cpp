//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	*
//	* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/GetRequestMessage.cpp $
//	* Working File Name:         $Workfile: GetRequestMessage.cpp $
//	*
//	* Version:                   $Revision: 1.2 $
//	*
//	* Last Modification Time:    $Modtime: 3/24/03 11:54a $
//	* Author:                    $Author: 100027762 $
//	*
//	*************************************************

// GetRequestMessage
#include "GetRequestMessage.h"
#ifdef NTEL_PLATFORM_CONVERT
#define BYTE_SWAP_COPY_16(A,B) byteSwapCopy16(A,B);
#define BYTE_SWAP_COPY_32(A,B) byteSwapCopy32(A,B);
#else
#define BYTE_SWAP_COPY_16(A,B) *((IRIS_UINT16 *)B) = *((IRIS_UINT16 *)A);
#define BYTE_SWAP_COPY_32(A,B) *((IRIS_UINT32 *)B) = *((IRIS_UINT32 *)A);
#endif

// Class GetRequestMessage 


GetRequestMessage::GetRequestMessage()
	: Message(IRIS_NodeInterface::GET_REQUEST_MSG_ID, GET_REQUEST_SERIALIZED_MSG_SIZE) // ID and size

{

}


GetRequestMessage::~GetRequestMessage()
{

}

//	See super class documentation.
int GetRequestMessage::getID ()
{
	return IRIS_NodeInterface::GET_REQUEST_MSG_ID;
}

//	See super class documentation.
int GetRequestMessage::deserialize (IRIS_UBYTE *bufPtr, IRIS_UINT32 length)
{
	IRIS_UBYTE *pktPtr = bufPtr;
	IRIS_UINT16 calcCrc, rcedCrc;

		// Restore the Message ID and check the CRC
	calcCrc = NetworkServices::calcCRC(bufPtr, serializedSize - 2);
	BYTE_SWAP_COPY_16(&bufPtr[serializedSize - 2], &rcedCrc);  // set received crc to network order

	if(calcCrc != rcedCrc)
	 {
	 	printf ("ERROR: calculated CRC: 0x%X, receiveded CRC: 0x%X\n", calcCrc,  rcedCrc);
		//return IRIS_NodeInterface::CRC_FAIL;
	 }
	
	// Copy individual members into the serial buffer

	pktPtr += 1;  // Skip past the Message class data

			// ID of the get message for this request
	requestedMessageID = *pktPtr;
	printf ("CRC -OK. calculated CRC: 0x%X, receiveded CRC: 0x%X\n", calcCrc,  rcedCrc);	
	return IRIS_NodeInterface::OK;
}

//	See super class documentation.
int GetRequestMessage::serialize (IRIS_UBYTE *bufPtr)
{
	IRIS_UBYTE *pktPtr = bufPtr;
	IRIS_UINT16 crc;

	// Fill in the Message members (ID, Dest, Orig)
	Message::pktBuild(&pktPtr);

	// Copy individual members into the serial buffer

			// ID of the get message for this request
	*((IRIS_UBYTE *)pktPtr) = requestedMessageID;
	pktPtr++;

	// Now add the CRC
	crc = NetworkServices::calcCRC(bufPtr, ((IRIS_UINT32)(serializedSize - 2)));
	BYTE_SWAP_COPY_16(&crc, pktPtr);  // set crc to network order and copy into the serialized packet

	return serializedSize;  // Length of packet is auto generated
}