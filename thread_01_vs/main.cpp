#include "gen.h"
#include <iostream>
/*
* Parallel and Concurrent Programming with C++ Part 1
* LinkedIn MAY-2023
*/

bool s_Finished = false;
bool isChopping = true;
unsigned int garlic_count = 0;
unsigned int potato_count = 0;

int items_on_notepad = 0;

std::atomic <unsigned int> garlic_count_atomic(0);

// create the mutex for shopper:
std::mutex pencilMutex;

// or recursive mutex:
std::recursive_mutex pencilMutexRec;

char WEEKDAYS[7][10] = {
    "Sunday", "Monday", "Tuesday",
    "Wednesday", "Thursday", "Friday", "Saturday"
};

int today = 0;
// create the mutex for Shared Mutex:
std::mutex markerMutex;
std::shared_mutex markerSharedMutex;

// int sushiCount = 5000;
int sushiCount = 5000000;

void vegetable_chopper(const char* nameP)
{
    unsigned int vegetavle_count = 0;
    while (isChopping)
    {
        vegetavle_count++;
    }
    printf("%s chopped %u vegetables.\n", nameP, vegetavle_count);
}

void execution_scheduling()
{
    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");

    printf("Barron and Olivia are chopping Vegetables...\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    isChopping = false;

    barron.join();
    olivia.join();

}

void shopperDataRace()
{
    const int count = 1000000;
    for (int i = 0; i < count; i++)
    {
        garlic_count++;
    }
}

int DataRaceTest()
{
    std::thread olivia(shopperDataRace);
    std::thread barron(shopperDataRace);

    olivia.join();
    barron.join();

    printf("We should buy %u galic.\n", garlic_count);

    return 0;
}

void shopperWithMutex()
{
    /* Note that we need to lock only the mutex
     * for increment the garlic count in our list,
     * not the whole function
     */
    // const int count = 100000;
    const int count = 5;
    // pencilMutex.lock(); // - this take too long time!
    for (int i = 0; i < count; i++)
    {
        // printf("Shopper %llx is thinking... \n", std::this_thread::get_id());
        std::cout << "Shopper" << std::this_thread::get_id() << "is thinking... \n";
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        pencilMutex.lock();
        garlic_count++;
        pencilMutex.unlock();
    }

    // pencilMutex.unlock(); // - this take too long time!
}

int MutexTest()
{
    std::thread olivia(shopperWithMutex);
    std::thread barron(shopperWithMutex);

    olivia.join();
    barron.join();

    printf("We should buy %u garlic.\n", garlic_count);
    // printf("We should buy %u potato.\n", potato_count);
    return 0;
}

/*
* Part: Atomic variables.
*
*/
void shopperWithAtomic()
{
    const int count = 100000;
    for (int i = 0; i < count; i++)
    {
        //printf("Shopper %llx is thinking... \n", std::this_thread::get_id());
        //std::this_thread::sleep_for(std::chrono::milliseconds(200));
        garlic_count_atomic++;
    }
}

int AtomicTest()
{
    std::thread olivia(shopperWithAtomic);
    std::thread barron(shopperWithAtomic);

    olivia.join();
    barron.join();

    printf("We should buy %u atomic garlic.\n", garlic_count_atomic.load());
    // std::cout << "We should buy " << garlic_count_atomic <<" atomic garlic.\n";

    return 0;
}


/*
* Part: Recursive Mutex
*
*/
void add_garlic()
{
    // here we must use recursive mutex:
    pencilMutexRec.lock();
    garlic_count++;
    pencilMutexRec.unlock();
}

void add_potato()
{
    // here we must use recursive mutex:
    pencilMutexRec.lock();
    potato_count++;
    add_garlic(); // nested 2 calls of a mutex!
    pencilMutexRec.unlock();
}

void shopperWithRecursiveMutex()
{
    const int count = 10000;
    for (int i = 0; i < count; i++)
    {
        //printf("Shopper %llx is thinking... \n", std::this_thread::get_id());
        //std::this_thread::sleep_for(std::chrono::milliseconds(200));
        add_garlic();
        add_potato();
    }
}

int RecursiveMutexTest()
{
    // use recursive mutex here.
    // if use usual mutex, it will be a deadlock.
    std::thread olivia(shopperWithRecursiveMutex);
    std::thread barron(shopperWithRecursiveMutex);

    olivia.join();
    barron.join();

    // Note that add_garlic will cal 2 times more!
    printf("We should buy %u garlic.\n", garlic_count);
    printf("We should buy %u potato.\n", potato_count);
    return 0;
}

/*
* Part 4.1: Try Lock
*
*/
void shopperWithTryLock(const char* nameP)
{
    const int count = 10000;
    int items_to_add = 0;
    while (items_on_notepad <= 20)
    {
        if (items_to_add && pencilMutex.try_lock())
        {
            // pencilMutex.lock(); // use try_lock() instead!

            //add items to shared items_on_notepad
            items_on_notepad += items_to_add;
            printf("%s added %u items to notepad\n", nameP, items_to_add);
            // reset items_to_add:
            items_to_add = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(300)); // time to write

            pencilMutex.unlock();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // time to search
            items_to_add++;
            printf("%s found something else to buy\n", nameP);
        }
    }

}

int TryLockTest()
{
    using namespace std::chrono;
    // auto start = high_resolution_clock::now(); // Get start time
    auto start_time = steady_clock::now();
    // use recursive mutex here.
    // if use usual mutex, it will be a deadlock.
    std::thread olivia(shopperWithTryLock, "Olivia");
    std::thread barron(shopperWithTryLock, "Barron");

    olivia.join();
    barron.join();


    // auto stop = high_resolution_clock::now(); // Get end time
    auto elapsed_time = duration_cast<milliseconds>(steady_clock::now() - start_time).count();
    std::cout << "Time taken by function: " << elapsed_time/1000.0 << " milliseconds\n";

    //printf("We should buy %u garlic.\n", garlic_count);
    //printf("We shoulda buy %u potato.\n", potato_count);
    return 0;
}

/*
* Part Shared Mutex:
*
*/
void calendarReader(const int idP)
{
    const int count = 7;

    for (int i = 0; i < count; ++i)
    {
        markerMutex.lock();
        printf("Reader- %d sees today is %s\n", idP, WEEKDAYS[today]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        markerMutex.unlock();
    }
}

void calendarWriter(const int idP)
{
    // This can change today date.
    const int count = 7;

    for (int i = 0; i < count; i++)
    {
        //markerMutex.lock();
        markerSharedMutex.lock_shared();
        today = (today +1) % 7;
        printf("Writer- %d updated date to %s\n", idP, WEEKDAYS[today]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //markerMutex.unlock();
        markerSharedMutex.unlock_shared();
    }
}


int SharedMutexTest()
{
    std::array<std::thread, 10> aReadersThreads;
    std::array<std::thread, 2>  aWritersThreads;

    for (size_t i = 0; i < aReadersThreads.size(); i++)
    {
        aReadersThreads[i] = std::thread(calendarReader, i);
    }

    for (size_t i = 0; i < aWritersThreads.size(); i++)
    {
        aWritersThreads[i] = std::thread(calendarWriter, i);
    }

    // wait for readers and writers to finish:
    for (size_t i = 0; i < aReadersThreads.size(); i++)
    {
        aReadersThreads[i].join();
    }

    for (size_t i = 0; i < aWritersThreads.size(); i++)
    {
        aWritersThreads[i].join();
    }


    // Note that add_garlic will cal 2 times more!
    //printf("We should buy %u potato.\n", potato_count);
    return 0;
}

/*
* Part Deadlock Demo:
*
*/
void diningPhilosophers(
        std::mutex &firstChopstickP,
        std::mutex &secondChopstickP,
        const char* nameP
        )
{
    // here we have nested lock, so potential deadlock may happen
    while (sushiCount > 0)
    {
        printf("%s philosopher try to lock firstChopStick..\n", nameP);
        firstChopstickP.lock();
        printf("%s philosopher try to lock secondChopStick..\n", nameP);
        secondChopstickP.lock();
        if (sushiCount)
        {
            sushiCount--;
            printf("Sushi counter update: %d\n", sushiCount);
        }
        firstChopstickP.unlock();
        secondChopstickP.unlock();
    }
}

void diningPhilosophersNoDeadLock(
        std::mutex &firstChopstickP,
        std::mutex &secondChopstickP,
        const char* nameP
        )
{
    // The "scoped_lock" automatically releases the lock when the scope
    // in which it was created is exited, while a lock does not
    while (sushiCount > 0)
    {
        printf("%s philosopher try to lock firstChopStick..\n", nameP);
        std::scoped_lock(firstChopstickP);
        printf("%s philosopher try to lock secondChopStick..\n", nameP);
        std::scoped_lock(secondChopstickP);
        if (sushiCount)
        {
            sushiCount--;
            printf("Sushi counter update: %d\n", sushiCount);
        }
        // no need to unlock, as using scoped_lock:
        //firstChopstickP.unlock();
        //secondChopstickP.unlock();
    }
}

void DeadLockTest()
{

    std::mutex chopStickA;
    std::mutex chopStickB;

    // This may result in a deadlock situation. No CPU power used.
    // std::thread olivia(diningPhilosophers, std::ref(chopStickA), std::ref(chopStickB), "Olivia");
    // std::thread barron(diningPhilosophers, std::ref(chopStickB), std::ref(chopStickA), "Barron");

    //
    std::thread olivia(diningPhilosophersNoDeadLock, std::ref(chopStickA), std::ref(chopStickB), "Olivia");
    std::thread barron(diningPhilosophersNoDeadLock, std::ref(chopStickA), std::ref(chopStickB), "Barron");

    olivia.join();
    barron.join();
    printf("The philosophed are done eating\n");
}



/*
* Part Abandoned Lock:
*
*/
void diningPhilosophersAbandoned(
        std::mutex &chopstickP,
        const char* nameP
        )
{
    while (sushiCount > 0)
    {
        printf("%s philosopher try to lock chopstickP.\n", nameP);
        // The "scoped_lock" automatically releases the lock when the scope
        // in which it was created is exited, while a lock does not
        std::scoped_lock(chopstickP);
        if (sushiCount)
        {
            sushiCount--;
            printf("Sushi counter update: %d\n", sushiCount);
        }
        if (sushiCount == 10)
        {
            printf("%s - This philosopher has had enough\n", nameP);
            break; // stop the while loop and forget to unlock!
        }
        // chopstickP.unlock(); // not needed if use scoped_lock()
    }
}


void AbanodenLockTest()
{

    std::mutex chopSticks;

    //
    std::thread olivia(diningPhilosophersAbandoned, std::ref(chopSticks), "Olivia");
    std::thread barron(diningPhilosophersAbandoned, std::ref(chopSticks), "Barron");

    olivia.join();
    barron.join();
    printf("The philosophed are done eating\n");
}


/*
* Part Starvation:
*
*/
void diningPhilosophersStarvation(
        std::mutex &chopstickP
        )
{
    int sushiEaten = 0;
    while (sushiCount > 0)
    {
        std::scoped_lock(chopstickP);
        if (sushiCount)
        {
            sushiCount--;
            sushiEaten++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // chopstickP.unlock(); // not needed if use scoped_lock()
    }
    // printf(" Philosopher %x ate %d sushi.\n", std::this_thread::get_id(), sushiEaten);
    std::cout << "Philosopher" << std::this_thread::get_id() << "ate" << sushiEaten << "\n";
}


void StarvationTest()
{
    const int numberOfPhilosophers = 200;
    std::mutex chopSticks;

    std::array<std::thread, numberOfPhilosophers> aPhilosophers;
    //

    for (size_t i = 0; i < aPhilosophers.size(); i++)
    {
        aPhilosophers[i] = std::thread(diningPhilosophersStarvation, std::ref(chopSticks));
    }

    for (size_t i = 0; i < aPhilosophers.size(); i++)
    {
        aPhilosophers[i].join();
    }
    printf("The philosophed are done eating\n");
}

/*
* Part LiveLock Demo:
*
*/
void diningPhilosophersLiveLock(
        std::mutex &firstChopstickP,
        std::mutex &secondChopstickP,
        const char* nameP
        )
{
    int sushiEaten = 0;
    // here we have nested lock, so potential deadlock may happen
    while (sushiCount > 0)
    {
        // printf("%s philosopher try to lock firstChopStick..\n", nameP);
        firstChopstickP.lock();// lock first stick and TRY to lock second:
        // printf("%s philosopher try to lock secondChopStick..\n", nameP);
        if (!secondChopstickP.try_lock())
        {
            // unlucky, release taken first stick:
            firstChopstickP.unlock();
        }
        else
        {
            if (sushiCount)
            {
                sushiCount--;
                // printf("Sushi counter update: %d\n", sushiCount);
                sushiEaten++;
            }
            firstChopstickP.unlock();
            secondChopstickP.unlock();
        }
    }
    //std::cout << "Philosopher " << nameP << " ate " << sushiEaten << "\n";
    // firstChopstickP.unlock();
}

void LiveLockTest()
{
    using namespace std::chrono;
    // auto start = high_resolution_clock::now(); // Get start time
    auto start_time = steady_clock::now();

    std::mutex chopStickA;
    std::mutex chopStickB;

    // This may result in a deadlock situation. Actively use CPU power.
    std::thread olivia(diningPhilosophersLiveLock, std::ref(chopStickA), std::ref(chopStickB), "Olivia");
    std::thread barron(diningPhilosophersLiveLock, std::ref(chopStickB), std::ref(chopStickA), "Barron");
    std::thread kate(diningPhilosophersLiveLock, std::ref(chopStickA), std::ref(chopStickB), "Kate");
    std::thread nikky(diningPhilosophersLiveLock, std::ref(chopStickB), std::ref(chopStickA), "Nikky");

    olivia.join();
    barron.join();
    kate.join();
    nikky.join();

    printf("The philosophed are done eating\n");

    // auto stop = high_resolution_clock::now(); // Get end time
    auto elapsed_time = duration_cast<milliseconds>(steady_clock::now() - start_time).count();
    std::cout << "Time taken by function: " << elapsed_time/1000.0 << " milliseconds\n";
}



int main()
{
    printf ("App started. \n");

    // DataRaceTest();

    // MutexTest();

    // AtomicTest();

    // RecursiveMutexTest();

    // TryLockTest();

    // SharedMutexTest();

    // DeadLockTest();

    // AbanodenLockTest();

    // StarvationTest();

    LiveLockTest();


    // system("PAUSE");
    return 0;
}