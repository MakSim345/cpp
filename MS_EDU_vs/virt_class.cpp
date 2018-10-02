#pragma once

#include "gen.h"
#include "utils.h"
#include "timectr.h"
#include "virt_class.h"
#include <stdlib.h>


InherDriverA::InherDriverA()
{
	m_IntegerN = 0;
}
/*
int InherDriverA::GetInteger()
{
 return m_IntegerN;
}

void InherDriverA::PrintMyVal() 
{
  printf ("VirtualDriver::m_IntegerN=%d\n", m_IntegerN);
}
*/

void InherDriverA::SetInteger(int i)
{
 m_IntegerN = i;
}
/* */