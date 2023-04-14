#include "gen.h"
#include "memory.h"

Memory::Memory()
    :cellValueM(0)
    ,cellNumberM(0)
    ,activeCellNumberM(0)
{
    for (int i=0; i<MEMORY_SIZE; i++)
    {
        RAM[i].setCellNumber(i);
    }
}

void Memory::printCurCellNumber()
{
    RAM[activeCellNumberM].printCellNumber();
}

int Memory::setCellValueChar(const char* cVal)
{
    // Method takes a number as a string and 
    // load it to a currently active cell.
    return RAM[activeCellNumberM].setCellValue(cVal);
}

int Memory::setCellValueInt(const int valP)
{
    // Method takes an integer number and
    // load it to a currently active cell. 
    return RAM[activeCellNumberM].setCellValue(valP);
}

int Memory::getCellValue(const int indexP)
{
    return RAM[indexP].getCellValue();
}

int Memory::getCellValue()
{
    /***********************************************************************
    *  Method returns value of currently selected cell
    ************************************************************************/
    return RAM[activeCellNumberM].getCellValue();
}

int Memory::getCellNumber()
{
    return RAM[activeCellNumberM].getCellNumber();
}

void Memory::cellCtrIncrement()
{
    int _tmp = activeCellNumberM;
    _tmp++;
    this->setCellCounter(_tmp);
}

void Memory::cellCtrDecrement()
{
    int _tmp = activeCellNumberM;
    _tmp--;
    this->setCellCounter(_tmp);
}

void Memory::setCellCounter(int newCellNumberP)
{
    if (newCellNumberP > MEMORY_SIZE - 1)
    {
        printf ("ERROR! Number %d is the last memory address.", MEMORY_SIZE - 1);
        activeCellNumberM = MEMORY_SIZE - 1;
        return;
    }

    if (newCellNumberP < 0)
    {
        /* value can not be less than 0, so set it to 1:*/
        activeCellNumberM = 1;
        return;
    }

    activeCellNumberM = newCellNumberP;
}

void Memory::printMemoryDump()
{
    int row;
    int column;
    int RowsNumber;
    /* MemCell* memory - pointer to an array!*/

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
    RAM[activeCellNumberM].printCellValue();
}

Memory::~Memory()
{

}
