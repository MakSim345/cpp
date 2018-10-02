#include <iostream>
#include "utils.h"

using namespace std;

class Date
{
private:
    int m_nMonth;
    int m_nDay;
    int m_nYear;
    
    Date() {} // private default constructor


public:
    Date(int nDay, int nMonth, int nYear)
    {
        SetDate(nDay, nMonth, nYear);
    }
    ~Date() {} ;

    void SetDate(int nDay, int nMonth, int nYear)
    {
        m_nMonth = nMonth;
        m_nDay = nDay;
        m_nYear = nYear;
    }
    
    int GetMonth() {return m_nMonth;}
    int GetDay()   {return m_nDay;}
    int GetYear()  {return m_nYear;}

    int GetMonth() const {return m_nMonth;}
    int GetDay()   const {return m_nDay;}
    int GetYear()  const {return m_nYear;}
};

void PrintDate(const Date &cDate)
// void PrintDate(Date &cDate)
{
    std::cout << cDate.GetDay() << "/" <<
                 cDate.GetMonth() << "/" <<
                 cDate.GetYear() << std::endl;                
}

int main()
{
    // print_message();
    Date aDate(3, 11, 2016);
    const Date cDate(3, 11, 2016);
    PrintDate (cDate);
    return 1;
}

