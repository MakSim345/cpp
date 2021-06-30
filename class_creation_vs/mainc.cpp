#include "gen.h"
#include "utils.h"

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

class Entity
{
public:
    float X;
    float Y;

    Entity()
    {
        X = 10.0;
        Y = 12.0;
    }

    std::string GetName()  {return "I am Entity";}
    
    // void Erase()
    virtual void Erase()
    {
        std::cout << "I am virtual Eraser() " << std::endl;   
    }

    void Move (float xaP, float yaP)
    {
        X += xaP;
        Y += yaP;
    }
};

class Player : public Entity
{
public:
    std::string m_Name;

    Player(const std::string& nameP)
        :m_Name(nameP) {}

    void Erase()
    // void Erase() override // override means it is originally virtual function and recreated here    
    {
        std::cout << "Erased: " << m_Name << std::endl;   
    }

    void PrintName ()
    {
        std::cout << "Hi my name is: " << m_Name << std::endl;
    }

    std::string GetName()  {return m_Name;}
};


void PrintName(Entity* entityP)
{
    std::cout << entityP->GetName() << std::endl;
    //nPlayerP->Name = "Cherno";
    //nPlayerP->PrintName();
    
    // std::cout << "eP->X = " << eP->X << std::endl;
    // std::cout << "eP->Y = " << eP->Y << std::endl;
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

    printf ("main - start\n");

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Warn("Hello");
    // std::cout << "enter somethig:\n";
    // std::cin.get();

    printf ("1. Time: %ld\n", Get1msTimeMS());
    msTimer t;
    for (int i = 0; i < 500000; i++)
        ;
    std::cout << "Elapsed time:" << t.elapsedMs() << endl;
    printf ("2. Time: %ld\n", Get1msTimeMS());

    /*
    void(*cherno)();
    auto function = HelloWorld;
    cherno = HelloWorld;
    function();
    cherno();
    */

    Entity *en = new Entity();    
    PrintName(en);
    // std::cout << en->GetName() << std::endl;
    
    Player* newPlayer = new Player("Cherno");
    PrintName(newPlayer);
    // std::cout << newPlayer->GetName() << std::endl;
    
    Entity* entity = newPlayer;
    PrintName(entity);
    // std::cout << entity->GetName() << std::endl;
    
    en = newPlayer;
    en->Erase(); 
    
    // testPlayer(newPlayer);
    
    printf ("Application complete.\n");

    system ("PAUSE"); // wait for press any key in VS mode

    return 0;
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



