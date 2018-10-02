//============================================================
//
// Description:
//============================================================
#include "worker.h"



worker::worker()
{

}

void worker::setMValue(int i)
{
    m_nValue = i;
}

int worker::getMValue(void)
{
    return m_nValue;
}

int worker::GetRNDValue(int minVal, int nMaxVal)
{
    int nRetVal=0;
    static int nFirstTime = 1;

    int rnd_MAX = 65;

    if (1 == nFirstTime)
    {
        srand (time (NULL));
        nFirstTime = 0;
    }
    nRetVal = minVal + (rand() % nMaxVal);

    //cout << "Time: " << nRetVal;
    //cout << "Execution done";
    return nRetVal;
}

void worker::run()
{
    int m_width = 10;
    int m_height= 20;
    int n = 0;    
    do {
            
        int x = GetRNDValue(0, m_width);
        int y = GetRNDValue(0, m_height);
        
        int angle = GetRNDValue(0, 360);
        int red = GetRNDValue(0, 256);
        
        int green = GetRNDValue(0, 256);
        int blue = GetRNDValue(0, 256);
        int alpha = GetRNDValue(0, 256);
        
        cout << "Iteration number %d\n" << n ;
    } while ((!exiting) && (n > 0));
}

#ifdef YS_TEST_15_SEP_2011

#endif
