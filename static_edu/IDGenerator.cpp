#include "IDGenerator.h"

// Static member variables always need to be defined in the code file:
int IDGenerator::s_nIDGenerator = 1;

IDGenerator::IDGenerator() 
{
    m_nID = s_nIDGenerator++; 
}
 
int IDGenerator::GetID() const 
{ 
    return m_nID; 
}
