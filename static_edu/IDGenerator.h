#ifndef _ID_GENERATOR_H_
#define _ID_GENERATOR_H_

#include "gen.h"

class IDGenerator
{
private:
    
    static int s_nIDGenerator;
    int m_nID;

public:
    
    IDGenerator(); 
    int GetID() const;

};

#endif 

/*
usage:
int main()
{
    IDGenerator cFirst;
    IDGenerator cSecond;
    IDGenerator cThird;
 
    using namespace std;
    cout << cFirst.GetID() << endl;
    cout << cSecond.GetID() << endl;
    cout << cThird.GetID() << endl;
    return 0;
}
*/

