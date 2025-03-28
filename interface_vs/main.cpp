/*
* By Cherno -
* https://www.youtube.com/watch?v=UWAdd13EfM8
*
* Interfaces in C++ (Pure Virtual Functions)
*/
#include "gen.h"
#include "utils.h"

long g_lTimeTick = 0;

// using String = std::string
#define String std::string

class StrEntity
{
public:
    StrEntity() : m_Name("Unknown") {};
    StrEntity(const String& nameP) : m_Name(nameP) {};

    // ~StrEntity();
    const String& GetName() const { return m_Name; }

private:
    String m_Name;
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

class Printable // interface.
{
public:
    // pure virtual method:
    virtual std::string GetClassName() = 0;
};

class Entity : public Printable
{
public:
    std::string GetName()  {return "I am Entity";}
    // virtual std::string GetName();

    // override pure virtual method from Printable
    std::string GetClassName() override
    {
        return "I am Entity";
    }

    virtual void Erase()
    {
        std::cout << "I am virtual Eraser() " << std::endl;
    }
};

class Player : public Entity
{
public:

    Player()
        :m_Name("I am Player (default)") {}

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

    std::string GetName() {return m_Name;}

    std::string GetClassName() override {return m_Name;}

private:
    std::string m_Name;
};

class myClassA : public Printable
{
public:
    myClassA()
        :m_Name("myClassA") {}

    std::string GetClassName() override {return m_Name;}

private:
    std::string m_Name;
};

void PrintName(Entity* entityP)
{
    std::cout << entityP->GetName() << std::endl;
    //nPlayerP->Name = "Cherno";
    //nPlayerP->PrintName();
}

void PrintMyClassName(Printable* objToPrintP)
{
    std::cout << objToPrintP->GetClassName() << std::endl;
}


int main(int argc, char *argv[], char *envp[])
{
    long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int nResult = 0;
    int nTdiff = 100; // 1000 is one second

    // msTimer t;
    CTimer t;

    printf ("main - start\n");

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Warn("Hello");

    printf("1. Time: %ld\n", t.Get1msTimeMS());

    Entity *entity = new Player();
    // PrintName(en);
    // PrintMyClassName (entity);
    // std::cout << en->GetName() << std::endl;

    Player* newPlayer = new Player("Player - Cherno");
    //PrintName(newPlayer);
    // std::cout << newPlayer->GetName() << std::endl;

    // Entity* entity = new Player();
    PrintMyClassName (newPlayer);
    PrintMyClassName (entity);
    PrintMyClassName(new myClassA());
    //PrintName(entity);
    // std::cout << entity->GetName() << std::endl;

    //en = newPlayer;
    //en->Erase();

    // testPlayer(newPlayer);

    const StrEntity* es = new StrEntity("Cherno - StrEntity");

    std::cout << es->GetName() << std::endl;

    printf ("Application complete.\n");

    system ("PAUSE"); // wait for press any key in VS mode

    return 0;
//*************MAIN LOOP*****************//
 do
 {
    //This is simple Windows way:
    // Sleep(1000);

    // and this is complicated one-thread way:
    if ((( t.Get1msTimeMS() - LastTimeInMS) > nTdiff - 1) || (LastTimeInMS > t.Get1msTimeMS() ))
    {
        nResult = produceRND();
        printf ("Time: %ld. Random: %d\n", t.Get1msTimeMS(), nResult);
        // std::cout << "Elapsed time:" << t.elapsedMs() << endl;

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



