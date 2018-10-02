#ifndef _MEM_CELL_H_
#define _MEM_CELL_H_

class MemCell
{
  public:
      MemCell(const MemCell &right);
      MemCell ();
      ~MemCell ();
      MemCell & operator=(const MemCell &right);
      int operator==(const MemCell &right) const;
      int operator!=(const MemCell &right) const;


      void setCellNumber (int nNumber);
      int setCellValue (const char* cValue);
      int setCellValue (int nValue);
      void printCellNumber ();
      void printCellValue ();
      int getCellValue ();
      int getCellNumber ();
      int getOpCode ();
      int getOperand ();

  private:
      const  int& _getCellNumber () const { return m_nCellNumber;}
      const  int& _getCellValue () const { return m_nCellValue;}
      int m_nCellNumber;
      int m_nCellValue;

};

#endif

