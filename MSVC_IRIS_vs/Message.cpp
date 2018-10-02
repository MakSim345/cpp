//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	*
//	* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/Message.cpp $
//	* Working File Name:         $Workfile: Message.cpp $
//	*
//	* Version:                   $Revision: 1.1 $
//	*
//	* Last Modification Time:    $Modtime: 7/11/03 1:36p $
//	* Author:                    $Author: 100027762 $
//	*
//	*************************************************
// Message
#include "Message.h"
// Setup byte ordering (platform define is passed in by the compiler)
#ifdef IRIS_COLDFIRE_DIAB
#define SWAP_16_OFFSET 0
#define SWAP_16_INDEXER 1
#define SWAP_32_OFFSET 0
#define SWAP_32_INDEXER 1
#endif
#ifdef IRIS_WIN32_VCC 
#define SWAP_16_OFFSET 1
#define SWAP_16_INDEXER -1
#define SWAP_32_OFFSET 3
#define SWAP_32_INDEXER -1
#endif 
#ifdef IRIS_ATMEL_AT90S_IAR_SYSTEMS
#define SWAP_16_OFFSET 1
#define SWAP_16_INDEXER -1
#define SWAP_32_OFFSET 3
#define SWAP_32_INDEXER -1
#endif

// Class Message 

Message::Message()
{
}

Message::Message (IRIS_UINT32 id, IRIS_UINT32 ss)
    	: ID(id), serializedSize(ss + MESSAGE_CLASS_SERIALIZED_BYTE_COUNT) // Add three bytes for 16 bit CRC and ID

{
}


Message::~Message()
{

}

//	Provides local validation of message contents (IE set
//	parameters).

//	Returns true if all individual validatior functions of a
//	message return true.
bool Message::validate ()
{
  return true;  // messages without validation always return true
}


//	getSerializedSize
IRIS_INT32 Message::getSerializedSize ()
{
	return serializedSize;	
}


//	getDeserializedSize
//
//	DEPRECATED - TO BE REMOVED IN FUTURE VERSIONS
IRIS_INT32 Message::getDeserializedSize ()
{
	return 0;	
}


//	Adds the calculated CRC to the buffer and adjusts the
//	pointer.
bool Message::addCRC (IRIS_UBYTE **pkt)
{
	IRIS_UINT16 crc;
	
	// Get the CRC
	crc = NetworkServices::calcCRC(*pkt, serializedSize - 2);
	return 0;
}


//	Copies the Message class specific info (the ID) to the
//	serial buffer and adjusts the pointer.
void Message::pktBuild (IRIS_UBYTE **pkt)
{
   		// Copy the ID and increment the pointer by one
  	**pkt = ID;
	(*pkt)++; // Increnent the pointer
}


//	Returns a null terminated ASCII string corrosponding to
//	the MDD namespaced name of the message.
//
//	IE. MddFilename_MessageName
const char * Message::toString ()
{
	return 0;
}


//	Swaps the two bytes starting at src and copies them to
//	dest.
void Message::byteSwapCopy16 (void *src, void *dest)
{
  *((IRIS_UBYTE *)dest) = *((IRIS_UBYTE *)src + 1);
  *((IRIS_UBYTE *)dest + 1) = *((IRIS_UBYTE *)src);
}


//	Swaps the four bytes starting at src and copies them to
//	dest.
void Message::byteSwapCopy32 (void *src, void *dest)
{
  *((IRIS_UBYTE *)dest) = *((IRIS_UBYTE *)src + 3);
  *((IRIS_UBYTE *)dest + 1) = *((IRIS_UBYTE *)src + 2);
  *((IRIS_UBYTE *)dest + 2) = *((IRIS_UBYTE *)src + 1);
  *((IRIS_UBYTE *)dest + 3) = *((IRIS_UBYTE *)src);
}