/*********************************************************************

  iris_if.h
	communication incapsulate
  13.10.2006 Initial coding

**********************************************************************/
#ifndef _IRIS_IF_H_
#define _IRIS_IF_H_

#include "IrisBasicTypes.h"
// Message
#include "Message.h"
// NetworkServices
#include "NetworkServices.h"

#include "IRIS_NodeInterface.h"

// LinkTestMessage
//#include "LinkTestMessage.h"

// UpgradeCommandMessage
//#include "UpgradeCommandMessage.h"

// UpgradeDataMessage
//#include "UpgradeDataMessage.h"

// StatusMessage
//#include "StatusMessage.h"

#define IRIS_MAX_MESSAGE_LENGTH 8192

#define IRIS_PACKET_END_FLAG 0x7E
	// This is the first (control) character in a replacement sequence
#define IRIS_PACKET_CONTROL_CHAR 0x7D
	// This is the second character in the sequence replacing 0x7D
#define IRIS_PACKET_CONTROL_SEQUENCE_0x7D_REPLACEMENT 0x5D
	// This is the second character in the sequence replacing 0x7E
#define IRIS_PACKET_CONTROL_SEQUENCE_0x7E_REPLACEMENT 0x5E

// void IRIS_Node_receivePacket (char *buffer, unsigned long length);
	/*
	Note:  Only class declerations occur in the header.  This prevents the entire include tree from
	being brought into the application when it includes IRIS_Node.h  This is done with the 
	pre-processor since Rose dosen't have a property to turn off generation of the includes.
	*/

//	This class implements most of the common (message
//	non-specific) IRIS messaging code.
//
//	Objects that communicate using IRIS inhierit
//	functionality from the IRIS_NodeInterface through IRIS_
//	Node and message content specific classes that are auto
//	generated.
/*
class IRIS_Node : public IRIS_NodeInterface, //## Inherits: <unnamed>%39C22B9D0096
                  	public IRIS_BoundaryObjectSubsystemProxy  //## Inherits: <unnamed>%3D2D8A460370
*/

class IRIS_Node : public IRIS_NodeInterface
{

  public:
		 IRIS_Node (); 
     // IRIS_Node (long compatCode, int maxMsg, unsigned char subsysId); 
		~IRIS_Node();    
     void receivePacket (char *buffer, unsigned long length);
     //void CheckLink ();
     //int GetLinkCheckResult ();
     //IRIS_Node * GetAsIrisNode ();
     //void SendSubsystemMsg (SubsystemRoutedMessage *msg);
     //void ReceiveSubsystemMsg (SubsystemRoutedMessage *msg);
     //void UpgradeStart ();
     //void ReceiveUpgradePacket (unsigned long address, unsigned short packetSize, unsigned char *packet, unsigned char sequenceNumber);
     //void StatusRequest ();
     //void UpgradeFinished ();
     //virtual unsigned char GetRoute ();
		
	protected:
      //int SendMessageProtected (Message *msg, unsigned char *stuffedMsgBuf, unsigned char *serializedMsgBuf);
      //int SendMessageProtectedReceiveThread (Message *msg, unsigned char *stuffedMsgBuf, unsigned char *serializedMsgBuf);
      //virtual int SendMessageReceiveThread (Message *msg) = 0;
      //int SendMessageRequest (int msgID);
     
		  //int IrisNodeInit (DOSerialPortInterface *IRISserialPort, bool threadSafe);
      
		   int IrisNodeInit (); // safe variant, for testing - YS, 13-OCT-2006

      //void IrisNodeDestroy ();
       void commError (IRIS_STATUS_CODE errCode);
      //IRIS_NodeInterface::IRIS_STATUS_CODE getLastError ();
      //void registerForErrors (IRIS_ErrorNotification *listener);
      Message **messagePool;
  
	private:
		  Message *CreateMessage(int);
      //int StuffMessageInternal (Message *msg, unsigned char *stuffedMsgBuf, unsigned long *length, unsigned char *serializedMsgBuf);
      //int receiveThreadWritePort (char *buffer, unsigned long length);
      //int sendThreadWritePort (char *buffer, unsigned long length);
      //int SendMessageRequestInternal (int msgID);
      int dispatch (Message *msg);
      //void linkTestRequestReceived ();
      //void linkTestMessageReceived (LinkTestMessage *msg);
    // Data Members for Class Attributes
      int maxMessageSize;
      //	This holds the most recently generated error code as set
      //	by commError.
      IRIS_NodeInterface::IRIS_STATUS_CODE lastErrorCode;
      //	Generated from the 32 bit CRC of each message name  and
      //	member type and name, in the order they appear in the
      //	mdd file.  This causes the compatability code to be
      //	differient only when one of these critical items has
      //	changed.  Note that message ordering IS significant.
      IRIS_UINT32 compatabilityCode;
      //	Holds the most recently determined link check result.
      int linkTestResult;
      //	Set to 1 (true) when IRIS_NodeInit has completed
      //	successfully.
      int irisIsInitialized;
      //	Buffer to store messages sent by the send thread on
      //	behalf of the receive thread.
      unsigned char *piggyBackBuffer;
      //	Head pointer for the piggy back buffer.  This is written
      //	by the receive thread.
      //
      //	Points to the next available position in which to add a
      //	character to the queue.
      unsigned char *piggyBackHead;
      //	Tailpointer for the piggy back buffer.  This is written
      //	by the send thread.
      //
      //	Points to the next character to be removed from the
      //	queue.  When head == tail the queue is empty.
      unsigned char *piggyBackTail;
      //	Address of the last character position in the piggy back
      //	queue.
      unsigned char *piggyBackEnd;
      //	Indicates that the send thread is in the process of
      //	making the write port call.
      bool txThreadInUse;
      //	Count of all the calls to commError.
      unsigned long totalErrorCount;
      //	Set to true on initialization if threadSafe argument to
      //	IrisNodeInit is true;
      bool multiThreaded;
      //	Used in receive packet to store unstuffed messgae
      //	packets.  The buffer is initially 300 bytes and is
      //	dynamically expanded as needed.  The maximum size of
      //	this buffer is 8192 bytes (value arbitrarly selected).
      unsigned char *unstuffedMsgBuf;
      //	Size of the currently allocated unstuffedMsgBuf.
      int unstuffedMsgBufSize;
      //	This message is maintained on the node for upgrade
      //	packets being sent to the other side of the link.  This
      //	is kept around to prevent the internal buffer from being
      //	reallocated for each packet sent.
      
			//UpgradeDataMessage *upgradePktForSend;
      // Data Members for Associations
      //DOSerialPortInterface *comport;
      //IRIS_ErrorNotification *errorEventListener;

};

#endif // IRIS_IF	
	