//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	*
//	* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/GetRequestMessage.h $
//	* Working File Name:         $Workfile: GetRequestMessage.h $
//	*
//	* Version:                   $Revision: 1.1 $
//	*
//	* Last Modification Time:    $Modtime: 3/24/03 11:54a $
//	* Author:                    $Author: 100027762 $
//	*
//	*************************************************

#ifndef GetRequestMessage_h
#define GetRequestMessage_h 1


// Message
#include "Message.h"
	// The number of bytes in the serialized message that are added by the 
	// this specialization of Message
#define GET_REQUEST_SERIALIZED_MSG_SIZE 1


//	Internal IRIS message used to send a request for a
//	message to the other side.

class GetRequestMessage : public Message  //## Inherits: <unnamed>%39C263F601E2
{

  public:
    // Constructors (generated)
      GetRequestMessage();

    // Destructor (generated)
      ~GetRequestMessage();

      int getID ();

      int deserialize (IRIS_UBYTE *bufPtr, IRIS_UINT32 length);

      int serialize (IRIS_UBYTE *bufPtr);

    // Data Members for Class Attributes

      //	This is the ID of the message being requested by the
      //	application
      int requestedMessageID;

	  // Additional Public Declarations

  protected:
    // Additional Protected Declarations
  
  private:
    // Additional Private Declarations
  
  private: // implementation

};


// Class GetRequestMessage 
#endif
