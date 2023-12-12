#include "semaphore.h"

Semaphore semaphoreCharger(4);

void cell_phone(int phoneIdP)
{
    semaphoreCharger.acquire();
    printf("Phone %d is charging....\n", phoneIdP);
    srand(phoneIdP); // charge for "random" amount between 1-3 seconds
    // int ms_to_wait = std::chrono::milliseconds(rand() % 2000 + 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000 + 1000));
    printf("Phone %d DONE charging....\n", phoneIdP);
    semaphoreCharger.release();
}

class ServingLine
{
public:
    void serve_soup(int i)
    {
        std::unique_lock <std::mutex> ladle_lock(ladle);
        soup_queue.push(i);
        ladle_lock.unlock();
        soup_served.notify_one();
    }

    int take_soup()
    {
        std::unique_lock <std::mutex> ladle_lock(ladle);
        while (soup_queue.empty())
        {
            soup_served.wait(ladle_lock);
        }

        int bowl = soup_queue.front();
        soup_queue.pop();
        return bowl;
    }
    //ServingLine();
    //~ServingLine();

private:
    std::queue<int> soup_queue;
    std::mutex ladle;
    std::condition_variable soup_served;
};

ServingLine serving_line; // = ServingLine();

void doSomeWork( void )
{
    const size_t length = 10;
    for (size_t i = 0; i < length; i++)
    {
        std::cout << "hello from thread " << std::this_thread::get_id() << "\tdoSomeWork\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return;
}

void cell_phone(int phoneIdP, int rndDelayP)
{
    Semaphore charger(4);

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

/*
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
*/

void someTestFoo()
{
    // std::thread threadAdder(doAddWork, 3009, 8990);

    for (size_t i = 0; i < 1000; i++)
    {
        //auto randomDelay = rand() % 5000 + 1000;
        //printf("%d, ", randomDelay);
        std::cout << "Main() thread id = " << std::this_thread::get_id() << ". iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    // printf("---\n");

    // threadAdder.join();

    // runPhonesThreads();
}


void thread_func1(char symbolP)
{
    for (int i = 0; i < 2000; i++)
    {
        std::cout << symbolP;
    }
}

void thread_func2(char symbolP)
{
    for (int i = 0; i < 2000; i++)
    {
        std::cout << symbolP;
    }
}

void refreshForecast(std::map <std::string, int> forecastMapP)
{
    for (int i = 0; i < 100; ++i)
    {

        for (auto &item : forecastMapP)
        {
            item.second++;
            std::cout << item.first << " - " << item.second << "\n";
        }

        std::this_thread::sleep_for(100ms);
    }
}
