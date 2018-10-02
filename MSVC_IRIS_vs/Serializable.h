//	*************************************************
//	* Datex-Ohmeda Inc.
//	* Ohmeda Drive
//	* PO Box 7550
//	* Madison, WI 53707-7550
//	*
//	* Copyright 2000, Datex-Ohmeda, Inc.
//	*
//	* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/Serializable.h $
//	* Working File Name:         $Workfile: Serializable.h $
//	*
//	* Version:                   $Revision: 1.1 $
//	*
//	* Last Modification Time:    $Modtime: 7/11/03 1:40p $
//	* Author:                    $Author: 100027762 $
//	*
//	*************************************************

// Source file: \Common\IRIS\source\RoseSrc\Serializable.h

#ifndef Serializable_h
#define Serializable_h 1

#include "gen.h"
// IRIS_NodeInterface
#include "IRIS_NodeInterface.h"

//	This interface specifies the serialize and deserialize
//	functions.

class Serializable
{
  public:
    // Destructor (generated)
      virtual ~Serializable();


    // Other Operations (specified)
      virtual int deserialize (IRIS_UBYTE *dataPkt, IRIS_UINT32 length) = 0;

      virtual int serialize (IRIS_UBYTE *dataPkt) = 0;

  protected:

  private:

  private: // implementation

};

// Class Serializable 

inline Serializable::~Serializable()
{

}
// Class Serializable 

#endif
