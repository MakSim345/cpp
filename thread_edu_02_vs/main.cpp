#include "gen.h"


class Semaphore
{
public:
    Semaphore(unsigned long init_countP)
    {
        count_ = init_countP;
    }
    // decrement the internal counter:
    void acquire()
    {
        std::unique_lock <std::mutex> lck(m_);
        while (!count_)
        {
            cv_.wait(lck);
        }
        count_--;
    }

    // increment the internal counter:
    void release()
    {
        std::unique_lock <std::mutex> lck(m_);
        count_++;
        lck.unlock();
        cv_.notify_one();
    }
    // ~Semaphore();

private:
    unsigned long count_;
    std::mutex m_;
    std::condition_variable cv_;
};

Semaphore charger(4);

void cell_phone(int phoneIdP)
{
    charger.acquire();
    printf("Phone %d is charging....\n", phoneIdP);
    srand(phoneIdP); // charge for "random" amount between 1-3 seconds
    // int ms_to_wait = std::chrono::milliseconds(rand() % 2000 + 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000 + 1000));
    printf("Phone %d DONE charging....\n", phoneIdP);
    charger.release();
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
        std::cout << "hello from thread " << this_thread::get_id() << "\tdoSomeWork\t" << i << std::endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    
    return;
}

int soup_servings = 10;
std::mutex slow_cooker_lid;
std::condition_variable soup_taken;

void hungry_person_err(int personIdP)
{
    int put_lid_back = 0;
    printf("Person %d enters\n", personIdP);
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
    printf("Person %d put the lid back %u times.", personIdP, put_lid_back);
}

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


void soup_producer()
{
    for (size_t i = 0; i < 1000000; i++)
    {
        serving_line.serve_soup(1);
    }
    serving_line.serve_soup(-1); // indicate there is no more soup
    printf("Producer is done serving soup.\n");
}

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


int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("Info: main() started. \n");

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
    std::thread hungry_threads[2];
    for (int i = 0; i < 2 ; i++)
    {
        hungry_threads[i] = std::thread(hungry_person, i);
    }

    for (auto& ht : hungry_threads)
    {
        ht.join();
    }
    */

    /*
    std::thread olivia(soup_producer);
    std::thread barron(soup_consumer);
    std::thread steve(soup_consumer);
    olivia.join();
    barron.join();
    steve.join();
    */

    std::thread phones[10];
    for (size_t i = 0; i < 10; i++)
    {
        phones[i] = std::thread(cell_phone, i);
    }
    for (auto& p : phones)
    {
        p.join();
    }
    
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


