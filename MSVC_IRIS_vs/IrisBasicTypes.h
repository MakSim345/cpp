/*************************************************
* Datex-Ohmeda Inc.
* Ohmeda Drive
* PO Box 7550
* Madison, WI 53707-7550
*
* Copyright 2000, Datex-Ohmeda, Inc.
*
* Archive Name:              $Archive: /DisplayComputer/Software/DCCommonSnapshot/Iris/Source/RoseSrc/IrisBasicTypes.h $
* Working File Name:         $Workfile: IrisBasicTypes.h $
*
* Version:                   $Revision: 1.1 $
*
* Last Modification Time:    $Modtime: 8/05/02 11:19a $
* Author:                    $Author: 100027762 $
*
*************************************************/
#ifndef IRIS_BASIC_TYPES_INCLUDED
#define IRIS_BASIC_TYPES_INCLUDED

//#define IRIS_WIN32_VCC

#ifdef IRIS_COLDFIRE_METROWERKS
typedef unsigned char	IRIS_BOOL;
typedef unsigned char 	IRIS_UBYTE;
typedef char 			IRIS_BYTE;
typedef unsigned short 	IRIS_UINT16;
typedef short 			IRIS_INT16;
typedef unsigned int 	IRIS_UINT32;
typedef int 			IRIS_INT32;
typedef float			IRIS_FLOAT32;
#endif

#ifdef IRIS_COLDFIRE_DIAB
typedef unsigned char	IRIS_BOOL;
typedef unsigned char 	IRIS_UBYTE;
typedef char 			IRIS_BYTE;
typedef unsigned short 	IRIS_UINT16;
typedef short 			IRIS_INT16;
typedef unsigned int 	IRIS_UINT32;
typedef int 			IRIS_INT32;
typedef float			IRIS_FLOAT32;
#endif

#ifdef IRIS_WIN32_VCC
typedef unsigned char	IRIS_BOOL;
typedef unsigned char 	IRIS_UBYTE;
typedef char 			IRIS_BYTE;
typedef unsigned short 	IRIS_UINT16;
typedef short 			IRIS_INT16;
typedef unsigned int 	IRIS_UINT32;
typedef int 			IRIS_INT32;
typedef float			IRIS_FLOAT32;
#endif

#ifdef IRIS_ATMEL_AT90S_IAR_SYSTEMS
typedef unsigned char	IRIS_BOOL;
typedef unsigned char 	IRIS_UBYTE;
typedef char 			IRIS_BYTE;
typedef unsigned int 	IRIS_UINT16;
typedef int 			IRIS_INT16;
typedef unsigned long 	IRIS_UINT32;
typedef long 			IRIS_INT32;
typedef float			IRIS_FLOAT32;
#endif

#endif
