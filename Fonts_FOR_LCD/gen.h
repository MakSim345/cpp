// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E1F22A53_DDD0_4EC3_BA00_07BD5F0D7EAB__INCLUDED_)
#define AFX_STDAFX_H__E1F22A53_DDD0_4EC3_BA00_07BD5F0D7EAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define TIME_TICK_INTERVAL 1000

// This didn't work:
// #define rdtsc __asm __emit 0fh __asm __emit 031h

#define PENTIUM
#define MHz 3000
#define WIN32_APP

#include <stdio.h>
#include "utils.h"
#include <conio.h>
#include "time.h"
#include <string.h>
#include <stdio.h>
#include "dos.h"

// this file included for "rdtsc"
//#include "intrin.h"

//#include <sys/stat.h>
#include "stdlib.h"
// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E1F22A53_DDD0_4EC3_BA00_07BD5F0D7EAB__INCLUDED_)
