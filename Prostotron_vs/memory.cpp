#include "gen.h"
#include "memory.h"

Memory::Memory()
    : m_nCellValue(0)
    , m_nCellNumber(0)
    , activeCellNumber(0)
{
    for (int i=0; i<MEMORY_SIZE; i++)
    {
     RAM[i].setCellNumber(i);
    }
}

void Memory::printCurCellNumber()
{
    RAM[activeCellNumber].printCellNumber();
}

int Memory::setCellValue(const char* cVal)
{
    // Method takes a number as a string and 
    // load it to a currently active cell.
    return RAM[activeCellNumber].setCellValue(cVal);
}

int Memory::setCellValue(int nVal)
{

    // Method takes an int number and 
    // load it to a currently active cell. 
    return RAM[activeCellNumber].setCellValue(nVal);
}

int Memory::getCellValue(int _index)
{
    return RAM[_index].getCellValue();
}

int Memory::getCellValue()
{
    /************************************************************************/
    /*  returns currently selected cell value
    /************************************************************************/
    return RAM[activeCellNumber].getCellValue();
}


int Memory::getCellNumber()
{
    return RAM[activeCellNumber].getCellNumber();
}

void Memory::cellCtrIncrement()
{
    int _tmp = activeCellNumber;
    _tmp++;
    this->setCellCounter(_tmp);
}

void Memory::cellCtrDecrement()
{
    int _tmp = activeCellNumber;
    _tmp--;
    this->setCellCounter(_tmp);
}

void Memory::setCellCounter(int nValue)
{
    if (nValue > MEMORY_SIZE - 1)
    {
        printf ("ERROR! Number %d is the last memory address.", MEMORY_SIZE - 1);
        activeCellNumber = MEMORY_SIZE - 1;
        return;
    }

    if (nValue < 0)
    {
        activeCellNumber = 1;
        return;
    }

    activeCellNumber = nValue;
}

void Memory::printMemoryDump()
{
    int row;
    int column;
    int RowsNumber;
    // MemCell* memory /*pointer to an array!*/

    RowsNumber = (MEMORY_SIZE / 10);

    printf ("\n    ");

    for (row = 0; row<10; row++)
        printf("    %d  ", row);

    for (row = 0; row<10; row++)
        {
         if (row == 0)
            printf ("\n %d ", row * RowsNumber); // for ZERO it is shifted left once
         else
            printf ("\n%d ", row * RowsNumber);

         for (column = 0; column<10; column++)
             RAM[row * RowsNumber + column].printCellValue();
        }
    printf("\n\n");
};

void Memory::printCellValue(int index)
{
    RAM[index].printCellValue();
}

void Memory::printCellValue()
{
    RAM[activeCellNumber].printCellValue();
}

Memory::~Memory()
{

}
