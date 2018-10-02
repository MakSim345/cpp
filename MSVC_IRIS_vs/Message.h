//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	*
//	* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/Message.h $
//	* Working File Name:         $Workfile: Message.h $
//	*
//	* Version:                   $Revision: 1.1 $
//	*
//	* Last Modification Time:    $Modtime: 7/11/03 1:36p $
//	* Author:                    $Author: 100027762 $
//	*
//	*************************************************

#ifndef Message_h
#define Message_h 1

// Serializable
#include "Serializable.h"
// NetworkServices
#include "NetworkServices.h"
	// The following defines the number of bytes in an actual serialized 
	// message object that are added by the message class itself.
#define MESSAGE_CLASS_SERIALIZED_BYTE_COUNT 3
//	Generic base class for messages.  Contains functionality
//	common to all messages.  Allows handling of messages by
//	the Message type instead of the actual message type.
//	Messages are individually typed to allow accessing thier
//	members by name.
//
//	Messages that are described in the MDD are represented
//	by classes that are auto generated and sub class Message.

class Message : public Serializable  //## Inherits: <unnamed>%397CA1F601A9
{

  public:
    // Constructors (generated)
      Message();

    // Constructors (specified)      
      Message (IRIS_UINT32 id, IRIS_UINT32 ss);

    // Destructor (generated)
      virtual ~Message();


      virtual bool validate ();
      virtual IRIS_INT32 getSerializedSize ();
      virtual IRIS_INT32 getDeserializedSize ();
      bool addCRC (IRIS_UBYTE **pkt);
      void pktBuild (IRIS_UBYTE **pkt);
      virtual const char * toString ();
      //	ID
      IRIS_UBYTE ID;
  protected:

      void byteSwapCopy16 (void *src, void *dest);

      void byteSwapCopy32 (void *src, void *dest);
  
      // Data Members for Class Attributes
      //	Size of the serialized packet including ID and CRC, but
      //	not the end flag.
      //
      //	Setup by child class objects upon instanciation.
      IRIS_UINT32 serializedSize;

    // Data Members for Associations

      NetworkServices networkServices;
  private:

  private: //implementation
		friend class Iris;
};

// Class Message 

#endif
