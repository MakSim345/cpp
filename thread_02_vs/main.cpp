#include "gen.h"
/*
An example from LinkedIn course "Parallel and Concurrent Programming with C++ Part 2"
*/

int soup_servings = 10;
std::mutex slow_cooker_lid;
std::condition_variable soup_taken;
uint32_t i = 0;

void hungry_person_err(int personIdP)
{
    int put_lid_back = 0;
    //printf("Person %d enters\n", personIdP);
    //printf("(soup_servings)/2 =  %d \n", soup_servings % 2);
    while (soup_servings > 0)
    {
        // pick up the slow cooker lid:
        std::unique_lock <std::mutex> lid_lock(slow_cooker_lid);
        // is it your turn to take soup?
        if ((personIdP == soup_servings % 2) && (soup_servings > 0))
        {
            soup_servings--; // it is your turn; take some soup!
            printf("Person %d takes soup %d\n", personIdP, soup_servings);
        }
        else
        {
            put_lid_back++; // no, it is not your turn. Put the lid back...
        }
    }
    printf("Person %d put the lid back %u times.\n", personIdP, put_lid_back);
}
/*
void hungry_person(int personIdP)
{
    int put_lid_back = 0;
    printf("Person %d enters\n", personIdP);
    while (soup_servings > 0)
    {
        // pick up the slow cooker lid:
        std::unique_lock <std::mutex> lid_lock(slow_cooker_lid);
        // is it your turn to take soup?
        while ((personIdP != soup_servings % 2) && (soup_servings > 0))
        {
            put_lid_back++; // no, it is not your turn. Put the lid back...
            soup_taken.wait(lid_lock);
        }
        if (soup_servings > 0)
        {
            soup_servings--; // it is your turn; take some soup!
            lid_lock.unlock();
            soup_taken.notify_all();
            // soup_taken.notify_one();
            printf("Person %d takes soup %d\n", personIdP, soup_servings);
        }
    }
    printf("Person %d put the lid back %u times.\n", personIdP, put_lid_back);
}
*/
/*
void soup_producer()
{
    for (size_t i = 0; i < 1000000; i++)
    {
        serving_line.serve_soup(1);
    }
    serving_line.serve_soup(-1); // indicate there is no more soup
    printf("Producer is done serving soup.\n");
}
*/

/*
void soup_consumer()
{
    int soup_eaten = 0;
    while (true)
    {
        int bowl = serving_line.take_soup();
        // check for the last bowl of soup;
        if (bowl == -1)
        {
            printf("Consumer ate %d bowls of soup.\n", soup_eaten);
            serving_line.serve_soup(-1); // put back bowl for other to see it is over.
            return;
        }
        else
        {
            soup_eaten += bowl;
        }
    }
}
*/

void ConditionVariablesTest()
{

    //olivia.join();
    //barron.join();

    std::thread hungry_threads[2];
    for (int i = 0; i < 2 ; i++)
    {
        hungry_threads[i] = std::thread(hungry_person_err, i);
    }

    for (auto& ht : hungry_threads)
    {
        ht.join();
    }
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

    /*
    std::thread olivia(soup_producer);
    std::thread barron(soup_consumer);
    std::thread steve(soup_consumer);
    olivia.join();
    barron.join();
    steve.join();
    */

    /*
    std::thread phones[10];
    for (size_t i = 0; i < 10; i++)
    {
        phones[i] = std::thread(cell_phone, i);
    }
    for (auto& p : phones)
    {
        p.join();
    }

    LiveLockTest();
    */
}


int main()
{
    printf ("App started. \n");
    auto startTimeSteadyClock = std::chrono::steady_clock::now();
    auto startTimeHiResClock = std::chrono::high_resolution_clock::now();

    // ConditionVariablesTest();


    // system("PAUSE");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    auto elapsed_time = duration_cast<milliseconds>(steady_clock::now() - startTimeSteadyClock).count();
    std::cout << "Duration by SteadyClock: " << elapsed_time << " milliseconds\n";
    std::cout << "Duration by SteadyClock: " << elapsed_time/1000.0 << " seconds\n";

    auto endTimeHiResClock = std::chrono::high_resolution_clock::now(); // Get end time
    std::chrono::duration<float> durationHiResClock = endTimeHiResClock - startTimeHiResClock;
    std::cout << "Duration by HiResClock : " << durationHiResClock.count() << " sec." << std::endl;

    printf ("App completed.\n");
    return 0;
}
