#include "gen.h"
#include "utils.h"

long g_lTimeTick = 0;

class String
{
private:
    char* m_Buffer;
    unsigned int m_Size;

public:
    String(const char* stringP)
    {
        m_Size = strlen(stringP);
        m_Buffer = new char[m_Size];
        memcpy(m_Buffer, stringP, m_Size);
    }
};

class Programmers
{
public:
    Programmers()
    {

    }

    Programmers(int iWeightP, int iAgeP)
    {
        this->weight = iWeightP;
        this->age = iAgeP;
    }

    // simply get references to value created in main and change them
    void getParams(int &getWeightP, int &getAgeP)
    {
        getWeightP=weight;
        getAgeP=age;
    }

private:
    int weight;
    int age;
};

class Log
{
public:
    static const int LogLevelError   = 0;
    static const int LogLevelWarning = 1;
    static const int LogLevelInfo    = 2;

    Log():
        mLogLevel(LogLevelInfo)
    {
        // mLogLebel = LogLevelInfo;
    }

private:
    int mLogLevel;

public:
    void SetLevel(int pLevel)
    {
        mLogLevel = pLevel;
    }

    void Warn(const char* pMessage)
    {
        if (mLogLevel >= LogLevelWarning)
            std::cout << "[WARNING]:" << pMessage << "\n";
    }

    void Info(const char* pMessage)
    {
        if (mLogLevel >= LogLevelInfo)
            std::cout << "[INFO]:" << pMessage << "\n";
    }

    void Error(const char* pMessage)
    {
        if (mLogLevel >= LogLevelError)
            std::cout << "[ERROR]:" << pMessage << "\n";
    }
};


void HelloWorld()
{
    std::cout << "Hello world!" << std::endl;
}


/*
 * Define a callback functions:
*/
float cb_square(int numP)
{
    return numP * numP;
}

float cb_cube(int numP)
{
    return numP * numP * numP;
}

float cb_square_root(int numP)
{
    return sqrt(numP);
}
/*
 * Define a calculate function that takes in
 * an integer and an operation (i.e. a method)
 * @TODO
*/

float calc(int num, float (*opP)(int))
{
    return opP(num);
}


int main(int argc, char *argv[], char *envp[])
{
    long LastTimeInMS = 0;
    int RValue = false;
    int nResult = 0;
    int DelayInMiliseconds = 1000; // 1000 is one second
    msTimer ms_tm;

    // msTimer t;
    CTimer t;

    printf ("main - start\n");

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Warn("Hello");

    printf("1. Time: %ld\n", t.Get1msTimeMS());

    printf("square:\t%2f\n", calc(5, cb_square));
    printf("cube:\t%2f\n", calc(5, cb_cube));
    printf("sqrt:\t%2f\n", calc(5, cb_square_root));

    printf ("3. Time: %ld\n", t.Get1msTimeMS());

    printf ("Application complete.\n");
    system ("PAUSE"); // wait for press any key in VS mode
    return 0;

//*************MAIN LOOP*****************//
 do
 {
    //This is simple Windows way:
    // Sleep(1000);

    // and this is complicated one-thread way:
    if ((( t.Get1msTimeMS() - LastTimeInMS) > DelayInMiliseconds - 1) || (LastTimeInMS > t.Get1msTimeMS() ))
    {
        nResult = produceRND();
        printf ("Time: %ld. Random: %d\n", t.Get1msTimeMS(), nResult);

        std::cout << "Elapsed time:" << ms_tm.elapsedMs() << endl;

        Sleep(1);

        LastTimeInMS = t.Get1msTimeMS();
    }

    // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        RValue = true; // END mark
    }
} while (!RValue);

printf ("Application complete.\n");
system ("PAUSE"); // wait for press any key in VS mode
return 0;
}
