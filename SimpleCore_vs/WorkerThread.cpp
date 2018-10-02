#ifndef WORKER_THREAD_CPP
#define WORKER_THREAD_CPP

#include <iostream>
#include <boost/thread.hpp>

class Worker
{
public:
    
    Worker() 
    {
        // the thread is not-a-thread until we call start()
    }

    void start(long N)
    {
        m_Thread = boost::thread(&Worker::processQueue, this, N);
    }

    void join()
    {
        m_Thread.join();
    }
    
    void processQueue(long N)
    {
        long ms = N * 1000;
        boost::posix_time::milliseconds workTime(ms);

        std::cout << "Worker: started, will work for "
                  << ms << "ms\n";
                  

        // We're busy, honest!
        boost::this_thread::sleep(workTime);

        std::cout << "Worker: completed\n";
    }

private:

    boost::thread m_Thread;
};
#endif
