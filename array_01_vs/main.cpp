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
    Programmers():
        weightM(0),
        ageM(0)
    {
    }

    Programmers(int iWeightP, int iAgeP)
    {
        this->weightM = iWeightP;
        this->ageM = iAgeP;
    }

    // simply get references to value created in main and change them
    void getParams(int &getWeightP, int &getAgeP)
    {
        getWeightP=weightM;
        getAgeP=ageM;
    }

private:
    int weightM;
    int ageM;
};

class Log
{
public:
    static const int LogLevelError   = 0;
    static const int LogLevelWarning = 1;
    static const int LogLevelInfo    = 2;

    Log():
        logLevelM(LogLevelInfo)
    {
        // mLogLebel = LogLevelInfo;
    }

private:
    int logLevelM;

public:
    void SetLevel(int pLevel)
    {
        logLevelM = pLevel;
    }

    void Warn(const char* pMessage)
    {
        if (logLevelM >= LogLevelWarning)
            std::cout << "[WARNING]:" << pMessage << "\n";
    }

    void Info(const char* pMessage)
    {
        if (logLevelM >= LogLevelInfo)
            std::cout << "[INFO]:" << pMessage << "\n";
    }

    void Error(const char* pMessage)
    {
        if (logLevelM >= LogLevelError)
            std::cout << "[ERROR]:" << pMessage << "\n";
    }
};


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

void testEntity()
{
    Entity* en = new Entity();
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
}

class Entity02
{
public:
    int* example;
    Entity02()
    {
        example = new int[5];
        for (int i = 0; i < 5; i++)
        {
            example[i] = 101;
        }
    }
};

int main(int argc, char *argv[], char *envp[])
{
    long LastTimeInMS = 0;
    int RValue = false;
    int nResult = 0;
    int DelayInMiliseconds = 1000; // 1000 is one second
    // msTimer t;
    CTimer t;

    printf ("main - start\n");

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Warn("Hello");

    // std::cout << "enter somethig:\n";
    // std::cin.get();

    printf("1. Time: %ld\n", t.Get1msTimeMS());

    Entity02 e;

    int example[5];
    int* another = new int[5]; // need a delete [] !

    for (int i = 0; i < 5; i++)
    {
        example[i] = 2;
        another[i] = 3;
    }
    // testPlayer(newPlayer);

    // printf ("Application complete.\n");
    // system ("PAUSE"); // wait for press any key in VS mode
    // return 0;

//*************MAIN LOOP*****************//
 do
 {
    //This is simple Windows way:
    // Sleep(1000);

    // and this is complicated one-thread way:
    if (((t.Get1msTimeMS() - LastTimeInMS) > DelayInMiliseconds - 1) || (LastTimeInMS > t.Get1msTimeMS() ))
    {
        nResult = produceRND();
        printf ("Time in ms: %ld.\n", t.Get1msTimeMS());
        printf ("Random: %d\n", nResult);
        std::cout << "Elapsed time:" << t.GetElapsedTimeMs() << endl;

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
