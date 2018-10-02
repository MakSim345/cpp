#include "gen.h"
#include "mem_cell.h"

MemCell::MemCell()
{
    m_nCellValue = 0;
    m_nCellNumber = 0;
}

void MemCell::setCellNumber(int nNumber)
{
  m_nCellNumber = nNumber;
}

int MemCell::setCellValue(const char* newCellValueCharP)
{
    int nData = 0;
    int i      =0;

    if (strlen(newCellValueCharP)>5)
       return 0;

    for (i = 0; i<(int)strlen(newCellValueCharP); i++)
    {
      if (!isdigit(newCellValueCharP[i]))
        {
          if(newCellValueCharP[i] == '-')
            nData = 0;
          else
          {
            printf ("Input error: %s is not digit! Please try again.\n", newCellValueCharP);
            return 0;
          }
        }
     }

  nData = atoi(newCellValueCharP);
  if (nData > 9999 || nData < -9999)
  {
    nData = 0;
    return  0;
  }

  this->setCellValue(nData);
  return 1;
}

int MemCell::setCellValue(int newCellValueP)
{

    if (newCellValueP > 9999 || newCellValueP < -9999)
      return 0;

    m_nCellValue = newCellValueP;
    return 1;
}

void MemCell::printCellNumber()
{
    if (this->m_nCellNumber < 10)
        printf (" 0%d", m_nCellNumber);
    else
        printf (" %d", m_nCellNumber);
}

void MemCell::printCellValue()
{
    if (m_nCellValue == 0)
     {
         printf ("  +0000");
         return;
     }
    if (m_nCellValue > 0)
    {
     if (MemCell::m_nCellValue < 10)
        printf ("  +000%d", m_nCellValue);
    else if (MemCell::m_nCellValue < 100)
        printf ("  +00%d", m_nCellValue);
    else if (MemCell::m_nCellValue < 1000)
        printf ("  +0%d", m_nCellValue);
    else if (MemCell::m_nCellValue < 10000)
        printf ("  +%d", m_nCellValue);
    }
    else// (m_nCellValue < 0)
    {
    if (MemCell::m_nCellValue > -10)
        printf ("  -000%d", m_nCellValue *(-1) );
    else if (MemCell::m_nCellValue > -100 )
        printf ("  -00%d", m_nCellValue *(-1));
    else if (MemCell::m_nCellValue > -1000)
        printf ("  -0%d", m_nCellValue *(-1));
    else if (MemCell::m_nCellValue > -10000)
        printf ("  -%d", m_nCellValue *(-1));
    }
}

int MemCell::getCellValue()
{
    return m_nCellValue;
};

int  MemCell::getCellNumber()
{
    return m_nCellNumber;
}
int  MemCell::getOpCode()
{
    return m_nCellValue/100;
}
int  MemCell::getOperand()
{
    return m_nCellValue%100;
}

MemCell::~MemCell()
{

}

