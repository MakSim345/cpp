#ifndef WATCHDOG_THREAD_CPP
#define WATCHDOG_THREAD_CPP

#include <iostream>
#include <boost/thread.hpp>

class WatchdogThread
{
public:
    
    WatchdogThread() 
    {
        // the thread is not-a-thread until we call start()
		running = false;
    }

    void start(int sleepMillis)
    {
		running = true;
        m_Thread = boost::thread(&WatchdogThread::watch, this, sleepMillis);
    }

	void stop()
    {
		running = false;
    }

    void join()
    {
        m_Thread.join();
    }
    
    void watch(unsigned sleepMillis)
    {
        //float ms = N * 1e3;
        boost::posix_time::milliseconds workTime(sleepMillis);
		while (running) {
			std::cout << "Watchdog: started, will sleep for "
                  << sleepMillis << "ms"
                  << std::endl;
			boost::this_thread::sleep(workTime);
			// now do some watching....
		}

        std::cout << "Watchdog: completed" << std::endl;
    }

private:
	bool running;
    boost::thread m_Thread;
};
#endif