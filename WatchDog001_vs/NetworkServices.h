//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	*
//	* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/NetworkServices.h $
//	* Working File Name:         $Workfile: NetworkServices.h $
//	*
//	* Version:                   $Revision: 1.1.1.1 $
//	*
//	* Last Modification Time:    $Modtime: 3/24/03 11:54a $
//	* Author:                    $Author: aa027762 $
//	*
//	*************************************************

// Source file: \Common\IRIS\source\RoseSrc\NetworkServices.h

#ifndef NetworkServices_h
#define NetworkServices_h 1

#include "gen.h"
// IRIS_NodeInterface
// #include "IRIS_NodeInterface.h"
#include "IrisBasicTypes.h"

//	Network Services.  Generic functionality needed by the
//	IRIS messaging code.

class NetworkServices 
{

  public:
    // Constructors (generated)
      NetworkServices();

    // Destructor (generated)
      ~NetworkServices();

      static IRIS_UINT16 calcCRC (IRIS_UBYTE *buffer, IRIS_INT32 length);

  protected:

  private:

  private: //## implementation
};
// Class NetworkServices 

#endif
