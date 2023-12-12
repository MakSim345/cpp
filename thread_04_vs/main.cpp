#include "gen.h"
/*
* Multi thread programming (RUS):
* #SimpleCode
* https://www.youtube.com/watch?v=UEtWLpDOg68
*/
bool is_Finished = false; // (origin - s_Finished )

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

Semaphore charger(4);

void cell_phone(int phoneIdP, int rndDelayP)
{
    charger.acquire();
    printf("Phone %d is charging....\n", phoneIdP);
    // srand(phoneIdP); // charge for "random" amount between 1-3 seconds
    // int ms_to_wait = std::chrono::milliseconds(rand() % 2000 + 1000);
    auto randomDelay = rand() % 5000 + 1000;
    printf("Phone %d charging takes about %d milliseconds.\n", phoneIdP, rndDelayP);
    std::this_thread::sleep_for(std::chrono::milliseconds(rndDelayP));
    printf("Phone %d DONE charging.\n", phoneIdP);
    charger.release();
}

void runPhonesThreads(void)
{
    std::thread phones[10];
    for (size_t i = 0; i < 10; i++)
    {
        auto randomDelay = rand() % 5000 + 1000;
        phones[i] = std::thread(cell_phone, i, randomDelay);
    }
    for (auto& p : phones)
    {
        p.join();
    }
}


void doSomeWork( void )
{
    const size_t length = 10;
    for (size_t i = 0; i < length; i++)
    {
        std::cout << "hello from thread " << this_thread::get_id() << "\tdoSomeWork\t" << i << std::endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    return;
}

void doAddWork(int operandAxP, int operandBxP)
{
    std::this_thread::sleep_for(chrono::milliseconds(500));
    std::cout << "doAddWork: STARTED thread id = " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(chrono::milliseconds(1500));
    std::cout << "a+b=" << operandAxP + operandBxP << std::endl;
    std::this_thread::sleep_for(chrono::milliseconds(500));
    std::cout << "doAddWork: STOPPED thread id = " << std::this_thread::get_id() << std::endl;
}


void doWork(void)
{
    std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;
    while (!is_Finished)
    {
        std::cout << "doWork is working. Press any key to stop it.\n";
        // std::this_thread::sleep_for(1s);
        std::this_thread::sleep_for(chrono::milliseconds(200));
    }
    std::cout << "is_Finished == TRUE. doWork completed.\n";
}


int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("Info: main() started. \n");

    srand(time(NULL));

    // doAddWork(34, 98);

    // std::thread worker(doWork);
    // std::cin.get();
    // is_Finished = true;
    // worker.join();

    std::thread threadAdder(doAddWork, 3009, 8990);

    for (size_t i = 0; i < 1000; i++)
    {
        //auto randomDelay = rand() % 5000 + 1000;
        //printf("%d, ", randomDelay);
        std::cout << "Main() thread id = " << std::this_thread::get_id() << ". iteration: " << i << std::endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    // printf("---\n");
    threadAdder.join();

    // runPhonesThreads();

    /*
    thread th(doSomeWork);
    const size_t length = 10;
    for (size_t i = 0; i < length; i++)
    {
        std::cout << "hello from thread " << this_thread::get_id() << "\tMAIN\t" << i << std::endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    th.join();
    */

//*************MAIN LOOP*****************//
    cout << "\n$ > Press Any Key to exit." << std::endl;
    do
    {
        //This is simple Windows way:
        Sleep(55);

        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            NewChar=(unsigned char)_getch();
            RValue = true;
            if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
            {
                RValue = true; // END mark
            }
            if (NewChar == 'd')  // pressed
            {
                if (1 == CaptureModeHex)
                    CaptureModeHex = 1;
                else
                    CaptureModeHex = 0;
            }
        }
    } while (!RValue);

    printf ("Application complete.\n");
    return 0;
}
