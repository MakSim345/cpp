#pragma once
/*********************************************************************

  utils.h  
  
**********************************************************************/

void AddTimeStamp(int *pos,char * msg);
void AddStringPan(char * destStr, char * strToAdd,int len);
void AddShortTimeStamp(int *pos,char * msg);

int RND_Array(int);
long  Get1msTime(void);
long  Get1msTimeMS(void);
char* PrintTime(void); // return string with time
void PrintIntroduction();
void SendStr(char * SendString, int dest, int length);

int produceRND();

class CTimer
{
public:
    CTimer();
	~CTimer();
    void Start();
    unsigned int GetElapsedTimeMs() const;
	unsigned __int64 GetElapsedTimeMks() const; 
    
private:
    LARGE_INTEGER m_liFreq;
    LARGE_INTEGER m_liStart;
    LARGE_INTEGER m_liEnd;
};


class COPSvCommunication
{
public:
    COPSvCommunication()
        : isCOPSvM(true)
    {

    }

    // simply get references to value created in main and change them
    void getParams(int &getWeightP, int &getAgeP)
    {
        getWeightP = weight;
        getAgeP = age;
    }

    const char* getModuleVersionString()
    {
        return this->getString();
    }

    const char* getString () const
    {
        char vstrM[] = " COP SW Pr. 889071-3.2   1996-04-26"; 
        return vstrM;
    }

    bool isModuleCompatible() const
    {
        int minorVer = 9;
        int majorVer = 3;// rConfigurationM.getModuleVersions(&minorVer);

        // rConfigurationM.getModuleVersionString();

        // std::lock_guard<Os::Mutex> lock(mutexM);

        if (isCOPSvM || // all COPSv are supported
            (majorVer == 3 && minorVer >= 2) || (majorVer > 3) || // all COP versions >= 3.2 are supported
            (majorVer == 0 && minorVer == 3)) // this is an exception. The module with the 
            // version 0.3 is also compatible
        {
            return true;
        }

        return false;
    }

private:
    int weight;
    int age;
    bool isCOPSvM;
    enum { maxSlowStringChar = 64 };
    // char vstrM[maxSlowStringChar];

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
        getWeightP = weight;
        getAgeP = age;
    }

private:
    int weight;
    int age;
};