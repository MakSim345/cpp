#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "gen.h"
#include "utils.h"
#include "memory.h"
#include "mem_cell.h"

class Memory
{
public:
    Memory ();
    ~Memory ();
    void printMemoryDump();
    void printCurCellNumber();
    void printCellValue(int);
    void printCellValue();
    
    void setCellCounter(int);
    void cellCtrIncrement();
    void cellCtrDecrement();
    
    int setCellValueChar(const char *);
    int setCellValueInt(const int valP);

    int getCellValue(const int indexP);
    int getCellValue();

    int getCellNumber();

private:
    int activeCellNumberM;
    int cellNumberM;
    int cellValueM;
      
    MemCell RAM [MEMORY_SIZE];
};

#endif
