/*********************************************************************

  iris_if.cpp
  
**********************************************************************/


#include "gen.h"
#include "error.h"
#include "utils.h"
#include "commport.h"
#include "iris_if.h"
#include "comminc.h"
#include "NetworkServices.h"
#include "Message.h"
#include "GetRequestMessage.h"

#include  "VcbTestMessageHeaders.h"

extern int PortNumber;
extern CTRACE t;

IRIS_Node::IRIS_Node()
       :irisIsInitialized(0),
        unstuffedMsgBufSize(0),       
				unstuffedMsgBuf(0)

{
  //printf ("IRIS_Node - constructor income\n"); 
	IrisNodeInit();
	//printf ("IRIS_Node - constructor over\n"); 

}
/*
IRIS_Node::IRIS_Node(long compatCode, int maxMsg, unsigned char subsysId)
       :irisIsInitialized(0),
        unstuffedMsgBufSize(0),       
				unstuffedMsgBuf(0)
{

}
*/
/********************************************************************

  Declaration: Performs initialization (including opening the DOSerial
	             PortInterface) required to make the node ready to begin
							 communications.
							 
							 Actual instance of a class implementing DOSerialPort
							 Interface is passed to the init function to isolate IRIS
							 from any knowlege of the hardware or aplication.

  Call: 
  Input: char *, unsigned long
  Returns: 
	Initial coding: 13-OCT-2006, YS
  	  
*********************************************************************/
int IRIS_Node::IrisNodeInit ()
{
	int ndx;
	// int status = IRIS_NodeInterface::OK; // Init to 'OK'
	int status = 1; // Init to 'OK'

		// Do not proceed if IRIS is already initialized
	if(irisIsInitialized)
		return 1;// IRIS_NodeInterface::OK; 
	
	// Set the multithreading mode
	//multiThreaded = threadSafe;
	
		// If not thread safe, initialize the piggy back buffer
		/*
		** NOTE Piggy back buffer is automatically set up to be 
		** the maximum allowable IRIS message size.  There is no dynamic 
		** buffer size increase provision as there is with received messages.
		*/
	if(!multiThreaded)
	{
		printf ("IrisNodeInit:(multiThreaded == FALSE)\n"); 
		// Create the array
		piggyBackBuffer = new unsigned char[IRIS_MAX_MESSAGE_LENGTH];
			// Initialize the pointers
		piggyBackHead = piggyBackTail = piggyBackBuffer;
		piggyBackEnd = piggyBackBuffer + IRIS_MAX_MESSAGE_LENGTH - 1;
	}

		// Initialize the receive packet buffer
	if(unstuffedMsgBuf != 0)
		{
		 delete unstuffedMsgBuf;
		}

	unstuffedMsgBufSize = 300;
	unstuffedMsgBuf = new unsigned char [unstuffedMsgBufSize];

	
	// Create and initialize the message pool
	messagePool = (Message **)(new Message *[256]);
	
	if(messagePool != 0)
	{
		// Pre-fill the message pool with zeros to indicate empty slots
		for(ndx = 0 ; ndx < 256; ndx++)
			messagePool[ndx] = (Message *)0;
		
		// Create pool items for the special IRIS messages
		messagePool[GET_REQUEST_MSG_ID] = new GetRequestMessage();
		messagePool[LINK_TEST_MESSAGE] = new LinkTestMessage();
		messagePool[UPGRADE_COMMAND_MESSAGE] = new UpgradeCommandMessage();
		messagePool[UPGRADE_DATA_MESSAGE] = new UpgradeDataMessage();
		messagePool[STATUS_MESSAGE] = new StatusMessage();
		//messagePool[ROUTED_SUBSYSTEM_MESSAGE] = new SubsystemRoutedMessage();
    messagePool[32] = new VcbTest_SensorInfo();
			// Now fill in the pool by calling the node's createMessage function with successive ID's
			// until zero is returned
		// for(ndx = 32; ndx < 256; ndx++)
		for(ndx = 33; ndx < 256; ndx++)
		{
			messagePool[ndx] = CreateMessage(ndx);
			if(messagePool[ndx] == (Message *)0)
				break; // All done (create returned a zero
		}
 
	}
	else // Initialization fails on failure to allocate message pool
	{
		status = 0;//IRIS_NodeInterface::IRIS_INIT_FAILURE;
		// Do a cleanup
		//IrisNodeDestroy();

		return status;
	}
	

	//if(upgradePktForSend == 0)
	//	upgradePktForSend = new UpgradeDataMessage();

	// Save the serial port reference
  // comport = IRISserialPort;

   // Add this node to the subsystem manager	
   //IRIS_SubsystemServicesManager::AddBoundaryObject(this);

	// Indicate initialization is complete
   irisIsInitialized = true;

	return status;

}
/********************************************************************

  Declaration: Dispatches the received message.  Length is the number 
	             of characters from the start of buffer, up to and
							 including the end flag.
							 This function unstuffs, CRC checks, de-serializes, and
							 dispatches the incomming packet.
							 If the CRC check fails, the message is discarded.

  Call: 
  Input: char *, unsigned long
  Returns: 
  	  
*********************************************************************/ 
void IRIS_Node::receivePacket (char *buffer, unsigned long length)
{
	unsigned int unstuffNdx, stuffNdx;
	Message *incomming; // The received message
	int id;  // The received message ID
	int status;
	/*
	for (int Q = 0; Q<length; Q++)
	{
	 printf (" [0x%X]", (unsigned char)buffer[Q]);
	 //printf ("%c", (unsigned char)data[Q]);
	}
  printf ("\n");
	*/

	// Make sure the buffer is big enough
	if(length > (unsigned long)unstuffedMsgBufSize)
	{
		// Delete the old buffer if it exists
		if(unstuffedMsgBuf != 0)
			delete[] unstuffedMsgBuf;

	  // Now allocate the new buffer
		if(length > IRIS_MAX_MESSAGE_LENGTH) // Message length limited to IRIS_MAX_MESSAGE_LENGTH
		{
			unstuffedMsgBufSize = IRIS_MAX_MESSAGE_LENGTH;
			unstuffedMsgBuf = new unsigned char [unstuffedMsgBufSize];
		}
		
		else
		{
				// Allocate plenty of space to avoid thrashing the heap
			unstuffedMsgBufSize = length * 2;
			unstuffedMsgBuf = new unsigned char [unstuffedMsgBufSize];
		}
	}		

	// Unstuff the message
	// NOTE: stuffNdx is the length of the unstuffed packet
	for(stuffNdx = unstuffNdx = 0; stuffNdx < length - 1;) // Last character is the end flag (thus length - 1)
	{
			// Copy the character into the unstuffed message buffer
		unstuffedMsgBuf[unstuffNdx] = ((unsigned char *)buffer)[stuffNdx];
			// Detect the first character (IRIS_PACKET_CONTROL_CHAR) of a stuffed series
		if(unstuffedMsgBuf[unstuffNdx] == IRIS_PACKET_CONTROL_CHAR)
		{
			/*
			Stuff sequence detected, if its a IRIS_PACKET_END_FLAG replace it (overwriting the original control character).  
			Otherwise its a 0x7D and that character is already in the dest buffer from the if operation
			NOTE: any unstuffing errors are detected by the CRC check since the CRC calculation
			and check wrap the stuff/unstuff operations on the packet.
			*/
			if((((unsigned char *)buffer)[++stuffNdx]) == IRIS_PACKET_CONTROL_SEQUENCE_0x7E_REPLACEMENT)
				unstuffedMsgBuf[unstuffNdx]	= IRIS_PACKET_END_FLAG;
		}
		stuffNdx++;  // Not a stuffed character, on to the the next
		unstuffNdx++;
	 }

	// Get the message ID
	id = (int)unstuffedMsgBuf[0];
  t.TRACE ("Message id=%d", id);
  t.TRACE (" [0x%X]\n", id);
		// Now get a message object for this ID
	incomming = messagePool[id];
	
	// Report an error and abort if message ID is no good
	if(incomming == 0)
	{
		//commError(IRIS_NodeInterface::BAD_MESSAGE_ID);
		printf ("IRIS_NodeInterface::BAD_MESSAGE_ID - %d\n", id);
		return;
	}

	// Deserialize the packet into the message object
	status = incomming->deserialize(unstuffedMsgBuf, length);
	if (CRC_FAIL == status)
		{
		 t.TRACE ("IRIS_NodeInterface::CRC_FAIL - %d\n", status);
		}
	else
		{
		 t.TRACE ("IRIS_NodeInterface::CRC_OK - %d\n", status);
		}
	
 /*************TRACE******************
	unsigned short calcCRC;
  unsigned short recvCRC;

	calcCRC = NetworkServices::calcCRC(unstuffedMsgBuf, length-3);
	t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
 ************************************/	
  
	// If the de-serialization went ok, deliver the message
	
	if(status == IRIS_NodeInterface::OK)
		dispatch(incomming);  // After return, message has been delivered
	else
		{	
		 printf ("Something went bad\n");
		//commError((IRIS_NodeInterface::IRIS_STATUS_CODE)status);  // Something went bad, log an error
		}
  
}

/********************************************************************

  Declaration: Message delivery function called upon successful
	             deserialization of a received message.
							 
							 This function handles internal messaging or calls the
							 application receive functions if it is an application
							 message.
  Call: 
  Input: Message *msg
  Returns: 
	Initial coding: 18-OCT-2006, YS
  	  
*********************************************************************/
int IRIS_Node::dispatch (Message *msg)
{
	int status;
  t.TRACE("Call dispatcher for message %d\n", msg->ID); 
	switch(msg->ID)
	{
			// Pass off any upgrade messages to the handlers
		case ROUTED_SUBSYSTEM_MESSAGE:
			// Notify subsystem manager of originator in received message
			//IRIS_SubsystemServicesManager::ReceivedOriginator(((SubsystemRoutedMessage *)msg)->originator);
			//IRIS_SubsystemServicesManager::IncommingSubsystemMessage((SubsystemRoutedMessage *)msg);
			break;
		case IRIS_NodeInterface::UPGRADE_COMMAND_MESSAGE:
		{
			// Notify subsystem manager of originator in received message
			//IRIS_SubsystemServicesManager::ReceivedOriginator(((UpgradeCommandMessage *)msg)->originator);
			//IRIS_SubsystemClient *localSubsys = IRIS_SubsystemServicesManager::GetLocalSubsystem();
			//IRIS_SubsystemServer *subsysServer = IRIS_SubsystemServicesManager::GetServer(); 
			
			/*
			switch(((UpgradeCommandMessage *)msg)->command)
			{ 				
				// Client commands.  Call the local subsystem client
				case IRIS_Subsystem::START:
					if(localSubsys != 0)
						localSubsys->UpgradeStart();
					break;
				case IRIS_Subsystem::FINISHED:
					if(localSubsys != 0)
						localSubsys->UpgradeFinished();
					break;
				case IRIS_Subsystem::STATUS_REQUEST:
					if(localSubsys != 0)
						localSubsys->StatusRequest();
					break;
       */

				/*
				** Server commands.  These are passed to the server through the manager.
				** NOTE:
				** The messages are only received from single node (C) implementations.  Since these
				** nodes only understand point-to-point communications the clientId member of the 
				** message is established as the subsystem ID of the remote node.  This is done
				** on behalf of the single node subsystem by putting the ID in the server call.
				*/

				/*
		    case IRIS_Subsystem::ACCEPT_START:
					((UpgradeCommandMessage *)msg)->clientId = GetSubsystemId();
					if(subsysServer != 0)
						subsysServer->UpgradeAcceptStart(GetSubsystemId(), ((UpgradeCommandMessage *)msg)->data);
					break;
				case IRIS_Subsystem::ACK_PKT:
					((UpgradeCommandMessage *)msg)->clientId = GetSubsystemId();
					if(subsysServer != 0)
						subsysServer->UpgradePacketAcknowledge(GetSubsystemId(), (unsigned char)((UpgradeCommandMessage *)msg)->data);
					break;
        
				default:
					break;
			}
			*/
			break;
		}

		case IRIS_NodeInterface::STATUS_MESSAGE:
		{
			/*
			IRIS_SubsystemServer *subsysServer = IRIS_SubsystemServicesManager::GetServer(); 
			// Notify subsystem manager of originator in received message
			IRIS_SubsystemServicesManager::ReceivedOriginator(((StatusMessage *)msg)->originator);
			// Call the server, filling in the ID on behalf of the remote single node subsystem
			((StatusMessage *)msg)->clientId = GetSubsystemId();
			if(subsysServer != 0)
				subsysServer->StatusResponse(GetSubsystemId(), (StatusMessage *)msg);
			*/
			printf ("STATUS_MESSAGE\n");
			break;
		}
		
		case IRIS_NodeInterface::UPGRADE_DATA_MESSAGE:
		{
			/*
			IRIS_SubsystemClient *localSubsys = IRIS_SubsystemServicesManager::GetLocalSubsystem();
				// Notify subsystem manager of originator in received message
			IRIS_SubsystemServicesManager::ReceivedOriginator(((UpgradeDataMessage *)msg)->originator);
			if(localSubsys != 0)
				localSubsys->
				ReceiveUpgradePacket (	((UpgradeDataMessage *)msg)->deviceAddress, 
										((UpgradeDataMessage *)msg)->packetSize, 
										((UpgradeDataMessage *)msg)->GetBuffer(), 
										((UpgradeDataMessage *)msg)->sequenceNumber);
      */
			break;			
		}
		
		// If this is a get request, get an empty message and ask that it be filled in
		case IRIS_NodeInterface::GET_REQUEST_MSG_ID:

				// Handle link test request right here
      t.TRACE("msg->requestedMessageID = %d\n", ((GetRequestMessage *)msg)->requestedMessageID);

			if(((GetRequestMessage *)msg)->requestedMessageID == IRIS_NodeInterface::LINK_TEST_MESSAGE)
			{
				//linkTestRequestReceived();
				// Send_TEST_Message(0,PortNumber); // -YS
				return IRIS_NodeInterface::OK;
			}
				// Get a pointer to the actual Message
			msg = messagePool[((GetRequestMessage *)msg)->requestedMessageID];
				// Report an error and abort if message ID is no good
			if(msg == 0)
			{
				commError(IRIS_NodeInterface::BAD_MESSAGE_ID);
				return IRIS_NodeInterface::BAD_MESSAGE_ID;
			}
      /*
			status = ReceiveMessageRequest(msg);
				// If the get was handled by the receiver, send back the result
			switch(status)
			{
				case IRIS_NodeInterface::OK:
					SendMessageReceiveThread(msg);
					break;
				case IRIS_NodeInterface::APP_MSG_REQUEST_NO_RESPONSE:
					break; // No action taken, app will handle response
				default:
					commError(IRIS_NodeInterface::APP_MSG_NOT_SUPPORTED);
					break;
			}
			*/
			break; // Done with Get Request

		default:
			t.TRACE ("dispatcher: default for message %d\n", msg->ID);
			// Handle Link test messages here
			if(msg->ID == IRIS_NodeInterface::LINK_TEST_MESSAGE)
			{
				//linkTestMessageReceived((LinkTestMessage *)msg);
				return IRIS_NodeInterface::OK;
			}
			// Deliver the message
			// status = ReceiveMessage(msg); -- requires NodeAdapter!! 
			//if(status != IRIS_NodeInterface::OK)
			//	commError(IRIS_NodeInterface::APP_MSG_NOT_SUPPORTED);
			
			break;

	}

	return IRIS_NodeInterface::OK;		 
}

/********************************************************************

  Declaration: Sets the most recently received error to the given value.
  Call: 
  Input: IRIS_STATUS_CODE errCode
  Returns: 
	Initial coding: 18-OCT-2006, YS
  	  
*********************************************************************/

void IRIS_Node::commError (IRIS_STATUS_CODE errCode)
{
	// Notify any listeners
	//if(errorEventListener != 0)
	//	errorEventListener->Notify(errCode);
		// Update the counter 
	totalErrorCount++;
		// Set the error code
	lastErrorCode = errCode;
}

/***************************************************************
*
*  Function name: CreateMessage
*  Parameter(s):  int - Message ID
*  Return type:   Message * - Newley created message
*  Author(s):     J Klaus
*  Purpose:       Allocates a new message on the heap 
*                   whose type is determined by the 
*                   given ID
*
*  Notes (i.e., error codes, special resource needs, etc.):
*
****************************************************************/

Message *IRIS_Node::CreateMessage (int msgID)
{
  
	// Select the class
  switch(msgID)
  {
    case VCB_TEST_SENSOR_INFO_ID:
      return new VcbTest_SensorInfo();
      break;
    case VCB_TEST_SENSOR_DETAILS_ID:
      return 0; //new VcbTest_SensorDetails();
      break;
 
    default:
      return 0; // Message ID not supported!
  }
	
}
