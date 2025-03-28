#include "gen.h"
bool is_Finished = false; // (origin - s_Finished )

class Semaphore
{
public:
    Semaphore(unsigned long initCountP)
    {
        counterSemaphoresM = initCountP;
    }
    // decrement the internal counter:
    void acquire()
    {
        std::unique_lock <std::mutex> theLock(mutexM);
        while (!counterSemaphoresM)
        {
            conditionalVariableM.wait(theLock);
        }
        counterSemaphoresM--;
    }

    // increment the internal counter:
    void release()
    {
        std::unique_lock <std::mutex> lck(mutexM);
        counterSemaphoresM++;
        lck.unlock();
        conditionalVariableM.notify_one();
    }
    // ~Semaphore();

private:
    unsigned long counterSemaphoresM;
    std::mutex mutexM;
    std::condition_variable conditionalVariableM;
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


void doSomeWork(void)
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

class do_work
{
public:
    void operator () ()
    {
        std::cout << "This is my function object" << endl;
    }
};

int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("Info: main() started. \n");
    srand(time(NULL));

    do_work dw;
    std::thread thread_to_run(dw);
    thread_to_run.join();
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

    printf ("Application complete.\n");
    system("pause");
    return EXIT_SUCCESS;
}
