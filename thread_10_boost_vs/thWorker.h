#ifndef TH_WORKER_H
#define TH_WORKER_H	
//============================================================
//

#include <iostream>
#include <boost/thread.hpp>

class thWorker
{
public:
    
    thWorker(unsigned N, float guess, unsigned iter);

    void operator()();

private:
    unsigned    m_Number;
    float       m_Guess;
    unsigned    m_Iterations;
};

#endif
