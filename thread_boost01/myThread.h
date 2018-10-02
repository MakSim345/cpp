#include "stdafx.h"
#include "gen.h"
#include "vThread.h"

class MyThread : public vThread
{
public:
    MyThread(int);
    ~MyThread();
    void ChangeVariable(int &pVar);
    void CopyVariable(int &pVar);
    void ChangeFlag(int pVar);

    void getFlag(int *pVar);

protected:
    int number;
    int *pFlag;
    // int &mP;
    // overloaded thread init routine:
    void init(void *pParam);
    // overloaded thread main routine:
    DWORD run();    
};