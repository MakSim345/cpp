#ifndef GEN_H
#define GEN_H        
/*********************************************************************

  gen.h  
  01.10.2004 Initial coding YS          

**********************************************************************/
#ifndef TRUE
#define TRUE -1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#define IPAPckPlc 0x0A41
#define IPAHrtBt  0x0A31
#define IPAAckwg  0x0E29
#define TRACE printf
#define mkdir(path) mkdir(path,0700)
 
#define MAX_VAL 40

#define IPA_TOS_VER "SAV001"
#define IPA_HBEAT 100

#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))    

#define MEAN_ARR 136
    
#define TRACE printf
    
#endif GEN_H
