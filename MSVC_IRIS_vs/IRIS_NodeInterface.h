//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	*
//	* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/IRIS_NodeInterface.h $
//	* Working File Name:         $Workfile: IRIS_NodeInterface.h $
//	*
//	* Version:                   $Revision: 1.2 $
//	*
//	* Last Modification Time:    $Modtime: 7/11/03 1:30p $
//	* Author:                    $Author: 100027762 $
//	*
//	*************************************************

// Source file: \Common\IRIS\source\RoseSrc\IRIS_NodeInterface.h

#ifndef IRIS_NodeInterface_h
#define IRIS_NodeInterface_h 1
	// Note these typedefs must occur before any includes
#include "IrisBasicTypes.h"

#ifdef NOTHING
	/*
	Note:  Only class declerations occur in the header.  This prevents the entire include tree from
	being brought into the application when it includes IRIS_NodeInterface.h  This is done with the 
	pre-processor since Rose dosen't have a property to turn off generation of the includes.
	*/

// IRIS_ErrorNotification
#include "IRIS_ErrorNotification.h"
// DOSerialPortInterface
#include "DOSerialPortInterface.h"
// Message
#include "Message.h"

#else
class Message;
//class DOSerialPortInterface;
//class NodeMonitor;
//class IRIS_ErrorNotification;
//class UndefinedDataMessage;
#endif

	// This defines the upper limit for messages handled by IRIS.  

#define IRIS_MAX_MESSAGE_LENGTH 8192

//	This is the top level interface that defines the
//	application interface to common (not message coontent
//	specific) IRIS messaging functionality. That is, a suite
//	of services common to all IRIS nodes.
//
//	Methods are ultimatly inheirited by an application
//	object which is given controlled access to IRIS (methods
//	are protected).
//
//	See 'The IRIS Communications Protocol' for further
//	information.

class IRIS_NodeInterface 
{

  public:

      virtual void receivePacket (char *buffer, unsigned long length) = 0;

      //virtual void CheckLink () = 0;

      //virtual int GetLinkCheckResult () = 0;

		// Error codes used by IRIS as return status values
	enum IRIS_STATUS_CODE 	
	{	
		APP_MSG_REQUEST_NO_RESPONSE = 1, // Request accepted but no immediate response.  NO ERROR GENERTAED
		OK = 0,	 						// Normal result NO ERROR GENERATED
		CRC_FAIL = -1,					// Failed CRC check of an incomming message
		BAD_MESSAGE_ID = -2,			// Reference made to a non-existant message ID
		IRIS_PORT_OPEN_FAIL = -3,		// Failed to open the port for this node
		IRIS_INIT_FAILURE = -4,			// Failure in the node init function
		LINK_INCOMPATIBLE = -5,			// Compatability code returned from link test req was differient
		NO_LINK_DETECTED = -6,			// No compatability code recd since last check
		NULL_MESSAGE = -7,				// Message pointer was equal to zero
		APP_MSG_NOT_SUPPORTED = -8,		// Application did not handle received message
		APP_MSG_REQUEST_NOT_SUPPORTED = -9 // Application does not provide service for this message
	};

		// ID values for internal IRIS messages (not defined in an MDD)
	enum INTERNAL_IRIS_MESSAGES	{ 	GET_REQUEST_MSG_ID = 31,		// Don't transmit empty message on request of a get
									LINK_TEST_MESSAGE = 30,			// Used by link test functions
									UPGRADE_COMMAND_MESSAGE = 29,
									UPGRADE_DATA_MESSAGE = 28,
									STATUS_MESSAGE = 27,
									ROUTED_SUBSYSTEM_MESSAGE = 26
								};

  protected:

       //virtual Message * CreateMessage (int msgID) = 0;

      //virtual int ReceiveMessage (Message *msg) = 0;

      //virtual int ReceiveMessageRequest (Message *blankMessage) = 0;

      //virtual int SendMessage (Message *msg) = 0;	

      //virtual int SendMessageRequest (int msgID) = 0;

      // virtual int IrisNodeInit (unsigned int PortNumber, unsigned long BaudRate, DOSerialPortInterface *port, bool threadSafe = false) = 0;
			//virtual int IrisNodeInit ()=0;

      //virtual void commError (IRIS_STATUS_CODE errCode) = 0;

      //virtual IRIS_STATUS_CODE getLastError () = 0;

      // virtual void registerForErrors (IRIS_ErrorNotification *listener) = 0; // remove YS

      //virtual int msgID_IsValid (int msgID) = 0;

      //virtual void IrisNodeDestroy () = 0;

    // Additional Protected Declarations
	  //friend class DOSerialPortInterface;
  private:

  private: // implementation

};

// Class IRIS_NodeInterface 

#endif
