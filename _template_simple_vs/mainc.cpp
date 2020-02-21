#include "gen.h"
#include "utils.h"

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
        mLogLebel(LogLevelInfo)
    {
        // mLogLebel = LogLevelInfo;
    }

private:
    int mLogLebel;

public:
    void SetLevel(int pLevel)
    {
        mLogLebel = pLevel;
    }

    void Warn(const char* pMessage)
    {   
        if (mLogLebel >= LogLevelWarning)
            std::cout << "[WARNING]:" << pMessage << "\n";
    }

    void Info(const char* pMessage)
    {
        if (mLogLebel >= LogLevelInfo)
            std::cout << "[INFO]:" << pMessage << "\n";
    }

    void Error(const char* pMessage)
    {
        if (mLogLebel >= LogLevelError)
            std::cout << "[ERROR]:" << pMessage << "\n";
    }
};



void PrintValue(int value)
{
    std::cout << "Value: " << value;
}

void ForEach(const std::vector<int>& values, void (*func)(int))
{
    //for (int value : values) 
    //    func (values[2]);
    vector<int>::iterator iter;
    iter = values.begin(); 
    values.end();
    //for(iter = values.begin(); iter != values.end(); iter++ )
    {
        // func (values[2]);
    }
}

long g_lTimeTick = 0;

int main(int argc, char *argv[], char *envp[])
{
    long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int Counter=0;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int nTdiff = 100; // 1000 is one second
    msTimer t;

    printf ("main - start\n");

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Warn("Hello");
    // std::cout << "enter somethig:\n";
    // std::cin.get();

    std::vector <int> values;// = {1, 5, 4, 2, 3};
    values.push_back(1);
    values.push_back(5);
    values.push_back(4);
    values.push_back(2);
    values.push_back(3);

    vector<int>::iterator iter;
    iter = values.begin(); 
    values.end();

    ForEach(values, PrintValue);

    //printf ("1. Time: %ld\n", Get1msTimeMS());
    
    //for (int i = 0; i < 5000000; i++)
    //    ;
    //std::cout << "Elapsed time:" << t.elapsedMs() << endl;
    //printf ("2. Time: %ld\n", Get1msTimeMS());



//*************MAIN LOOP*****************//
 do
 {
    //This is simple Windows way:
    // Sleep(1000);
    
    // and this is complicated one-thread way:
    if ((( Get1msTimeMS() - LastTimeInMS) > nTdiff - 1) || (LastTimeInMS > Get1msTimeMS() ))
    {    
        nResult = produceRND();
        printf ("Time: %ld. Random: %d\n",Get1msTimeMS(), nResult);
        std::cout << "Elapsed time:" << t.elapsedMs() << endl;

        Sleep(1);

        LastTimeInMS = Get1msTimeMS();
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
