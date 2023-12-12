#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "gen.h"

class Semaphore
{
public:
    Semaphore(unsigned long initCountP)
    {
        m_counterSemaphores = initCountP;
    }
    // decrement the internal counter:
    void acquire()
    {
        std::unique_lock <std::mutex> theLock(m_Mutex);
        while (!m_counterSemaphores)
        {
            m_ConditionalVariable.wait(theLock);
        }
        m_counterSemaphores--;
    }

    // increment the internal counter:
    void release()
    {
        std::unique_lock <std::mutex> lck(m_Mutex);
        m_counterSemaphores++;
        lck.unlock();
        m_ConditionalVariable.notify_one();
    }
    // ~Semaphore();

private:
    unsigned long m_counterSemaphores;
    std::mutex m_Mutex;
    std::condition_variable m_ConditionalVariable;
};

class Semaphore2
{
public:
    Semaphore2(unsigned long initCountP)
    {
        semaphoreCounterM = initCountP;
    }
    // decrement the internal counter:
    void acquire()
    {
        std::unique_lock <std::mutex> lck(semaphoreMutexM);
        while (!semaphoreCounterM)
        {
            cv_.wait(lck);
        }
        semaphoreCounterM--;
    }

    // increment the internal counter:
    void release()
    {
        std::unique_lock <std::mutex> lck(semaphoreMutexM);
        semaphoreCounterM++;
        lck.unlock();
        cv_.notify_one();
    }

private:
    unsigned long semaphoreCounterM;
    std::mutex semaphoreMutexM;
    std::condition_variable cv_;
};


#endif
