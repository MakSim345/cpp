/*
 * If you are using Visual Studio, Microsoft provides some useful functions for detecting and debugging memory leaks.

I would start with this set of articles: http://msdn.microsoft.com/en-us/library/x98tx3cf(VS.71).aspx

Here is the quick summary of those articles. First, include these headers:
*/

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
/*
Then you need to call this when your program exits:
*/

_CrtDumpMemoryLeaks();

/*
Alternatively, if your program does not exit in the same place every time, you can call this at the start of your program:

_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

Now when the program exits all the allocations that were not free'd will be printed in the Output Window along with the file they were allocated in and the allocation occurrence.

This strategy works for most programs. However, it becomes difficult or impossible in certain cases. Using third party libraries that do some initialization on startup may cause other objects to appear in the memory dump and can make tracking down your leaks difficult. Also, if any of your classes have members with the same name as any of the memory allocation routines( such as malloc ), the CRT debug macros will cause problems.

There are other techniques explained in the MSDN link referenced above that could be used as well.
*/
