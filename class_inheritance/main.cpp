#include <iostream>
#include <string>
#include "utils.h"

/*
Solving follow problem:
    - we have name declared in base class 
    - need to use it in derived class
    - how to initiate it in derived class?


*/
inline float cube (const float s) {return s*s*s;}

using namespace std;

class Person
{
public:
    std::string m_strName;
    int m_nAge;
    bool m_bIsMale;

    std::string getName() {return m_strName;}
    int getAge() {return m_nAge;}
    bool isMale() {return m_bIsMale;}

    Person(std::string strName = "Nan", int nAghe = 0, bool isMale = false)
    : m_strName(strName)
    , m_nAge(nAghe)
    , m_bIsMale(m_bIsMale)
    {
        // class implementation here.
    }
    ~Person();
};

class BaseBallPlayer : public Person
{
public:
    double m_dBattingAverage;
    int m_nHomeRuns;
    std::string m_strNm;

    BaseBallPlayer(std::string strName = "Nan", int nAghe = 0, bool isMale = false, double dBattingAverage = 0.0, int nHomeRuns = 0)
    : Person(strName, nAghe, isMale)
    , m_dBattingAverage(dBattingAverage)
    , m_nHomeRuns(nHomeRuns)
    , m_strNm ("Test")    
    {        
        std::cout << "BaseBallPlayer constructor called:\n";
        std::cout << "m_dBattingAverage: " << m_dBattingAverage << "\n";
        std::cout << "m_nHomeRuns: " << m_nHomeRuns << "\n";
        std::cout << "m_strName: " << m_strName << "\n";
        // std::cout << "m_strNm: " << m_strNm << "\n";        
    }

    ~BaseBallPlayer();

    /* data */
};

int main()
{
    // print_message();    
    BaseBallPlayer *bbp;
    bbp = new BaseBallPlayer("Pedro cerrano", 32, true, 0.9899, 42);
    printf("\n");
    
    return 1;
}

