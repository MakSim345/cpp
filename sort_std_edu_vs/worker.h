#ifndef _WORKER_H_
#define _WORKER_H_

//============================================================
//
//
//============================================================
//
// File:           Worker.h
//
//
//============================================================
// Description:
//==========================================================
#include "gen.h"

class worker 
{  
public:
    worker();
    int GetRNDValue(int minVal, int nMaxVal);

protected:
    void run();
    void setMValue(int i);
    int getMValue(void);

private:
	int m_nValue;
    int stars;
    bool exiting;
    int outerRadius;
    int innerRadius;
};

#endif 
