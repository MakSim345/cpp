#include "IDGenerator.h"

int IDGenerator::s_nIDGenerator = 1;

IDGenerator::IDGenerator() 
{
    m_nID = s_nIDGenerator++; 
}
 
int IDGenerator::GetID() const 
{ 
    return m_nID; 
}
 



