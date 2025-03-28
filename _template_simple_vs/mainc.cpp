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

/*
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

*/
long g_lTimeTick = 0;

int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int nRandomVal = -1;
    auto mainCounter = 0;
    int msTarget = 100;  // 1000 is one second

    // msTimer t;

    CTimer* cTimerCtr = new CTimer();

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

    // ForEach(values, PrintValue);

    //printf ("1. Time: %ld\n", Get1msTimeMS());

    //for (int i = 0; i < 5000000; i++)
    //    ;
    //std::cout << "Elapsed time:" << t.elapsedMs() << endl;
    //printf ("2. Time: %ld\n", Get1msTimeMS());

    auto start = std::chrono::steady_clock::now();
    cout << "Press Ctr-X to exit." << std::endl;
    //*************MAIN LOOP****************
    //
    do
    {

        auto now = std::chrono::steady_clock::now();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start)>= std::chrono::milliseconds(msTarget))
        {
            mainCounter++;
            nRandomVal = produceRND();
            printf ("%d - Time: %u. RND: %d\n", mainCounter, cTimerCtr->GetElapsedTimeMs(), nRandomVal);
            printf ("Time: %ld.\n", cTimerCtr->Get1msTimeMS());
            start = now;
        }

        if (nRandomVal == 0) // wait for random ZERO!
        {
            RValue = true;
        }

        // std::string cInTrace("0");
        // std::getline (std::cin, cInTrace);
    } while (!RValue);

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

    auto endTime = cTimerCtr->GetElapsedTimeMs();
    std::cout << "Application complete after " << mainCounter << " iterations. EndTime: " << endTime <<"\n";
    
    // wait for press any key in VS mode: 
    // Note: "Tool->Options->Debugging->Automatically close console"
    //system ("PAUSE"); 

return 0;

}
