#ifndef TIMECTR_H
#define TIMECTR_H    

#include <Windows.h>

void PrintTimeN(int nCounter);
void PrintTimeMS(int nCounter);

class CAuto
{
public:
    CAuto();
    ~CAuto();
    void Start();
    int GetAutoColor() const;
    int GetAutoHorsePwr()const; 
    //int GetAutoColor() const;
    //int GetAutoHorsePwr() const; 
    
private:
    int const m_Color;
    int m_HorsePwr;
    int m_Speed;
};

#endif // TIMECTR
