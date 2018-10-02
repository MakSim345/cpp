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
    
    int setCellValue(const char *);
    int setCellValue(int nVal);

    int getCellValue(int _index);
    int getCellValue();

    int getCellNumber();
      
    int  activeCellNumber;
      
private:
    int m_nCellNumber;
    int m_nCellValue;
      
    MemCell RAM [MEMORY_SIZE];
};

#endif
