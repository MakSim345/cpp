#include "gen.h"
#include "utils.h"
#include "memory.h"
#include "processor.h"

class Prostotron
{
public:
    Prostotron()
        :strInput("0")
        ,strDump("dump")
        ,nClNum(0)
        ,nClVal(0)
        ,nData(0)
        ,AsmModeFlag(0)
        ,EndFlag(0)
        ,DebugModeFlag(0)
    {
        pProc  = new Processor();
        memory = new Memory();
    
        pProc->getMemory(memory);
    }

    void Run()
    {
     while (!EndFlag) 
     {
      do 
      { 
        if (memory->getCellNumber() == 0)
        {
            memory->printMemoryDump();
            // do nothing, because dump print anyway.
        }
        memory->printCurCellNumber();
        std::cout << " [";
        memory->printCellValue();
        std::cout << "] > ";
        std::getline (std::cin, strInput);

        if (strInput.compare("") == 0) // no changes to current memory cell, increment program counter.
        {
            memory->cellCtrIncrement();
        }
        else if (strInput.compare("/?") == 0)
            PrintHelpInfo(ASM);
        else if (strInput.compare("help") == 0)
            PrintHelpInfo(ASM);
        else if (strInput.compare("cmd") == 0)
            AsmModeFlag = 1;

        // goto:
        else if ( (strInput.c_str()[0] == 'g') && (strInput.c_str()[1] == 'o') && (strInput.c_str()[2] == 't') && (strInput.c_str()[3] == 'o'))
          {
            // sprintf_s(tmpbuf, "%s", cInput.c_str() + 5);
            // nData = atoi(tmpbuf);

            nData = atoi(strInput.c_str() + GOTO_LEN);
            if (nData > MEMORY_SIZE || nData < 0)
                std::cout << "This cell number is out of range!\n";
            else
                memory->setCellCounter(nData);
          }
        else if ( (strInput.compare("exit") == 0) || ( strInput.compare("quit") == 0)
                  || ( strInput.compare(":q") == 0) ) // end
          {
             AsmModeFlag = 1;
             DebugModeFlag = 1;
             EndFlag = 1;
          }
        else
          {
            if (memory->setCellValueChar(strInput.c_str())) // avoid incorrect values!
            {
                // and increment cell counter:
                memory->cellCtrIncrement();
            }
          }

        memory->printMemoryDump();

     } while (!AsmModeFlag);

     AsmModeFlag = 0;

     if (!EndFlag) //print dump only if no exit command entered
      {
         memory->printMemoryDump();
         std::cout << "*** Program load complete. Enter the next command or '/?' for help.***\n";
      }

     while (!DebugModeFlag) // debug mode
     {
        std::cout << " > ";
        std::getline (std::cin, strInput);

        if (strInput.compare(strDump) == 0) // show dump immediately
            memory->printMemoryDump();

        else if (strInput.compare("run") == 0) // run current program
        {
            pProc->runProgramInMemory();
            memory->printMemoryDump();
            memory->setCellCounter(0);
        }
        else if (strInput.compare("trace") == 0) // trace current program
        {
            pProc->runProgramInMemory(TRACE_ENABLED);
            memory->setCellCounter(0);
        }
        else if (strInput.compare("/?") == 0)
            PrintHelpInfo(CMD);
        else if (strInput.compare("asm") == 0) // go to assembler mode
            DebugModeFlag = 1;
        else if ( (strInput.c_str()[0] == 's') && (strInput.c_str()[1] == 'a') && (strInput.c_str()[2] == 'v') && (strInput.c_str()[3] == 'e'))
        {
            // save current dump to binary(!) file
            if (strInput.length() <= SAVE_LEN)
            {
                sprintf(cFileName, "%s", "asm_10.asm", strlen("asm_10.asm"));
            }
            else
            {
                sprintf(tmpbuf, "%s", strInput.c_str() + SAVE_LEN);
                sprintf(cFileName, "%s", tmpbuf, strlen(tmpbuf));
            }
            std::ofstream outFile(cFileName, std::ios::binary);
            outFile.write((char *)memory, sizeof(*memory));
            outFile.close();
            std::cout << "Saving to binary file " << cFileName << "complete.\n";
        }
        else if (strInput.compare("dir") == 0) //
            std::cout << "Operation DIR is not implemented!\n";

        else if ( (strInput.c_str()[0] == 'l') && (strInput.c_str()[1] == 'o') && (strInput.c_str()[2] == 'a') && (strInput.c_str()[3] == 'd'))
        {
            // load memory dump from file:

            if (strInput.length() <= LOAD_LEN)
            {
                std::cout << "Please, provide a filename!\n";
            }
            else
            {
                sprintf(tmpbuf, "%s", strInput.c_str() + LOAD_LEN);
                sprintf(cFileName, "%s", tmpbuf, strlen(tmpbuf));

                std::ifstream ifs(cFileName, std::ios::binary);

                while(ifs.read((char *)memory, sizeof(*memory)))
                {
                    memory->printMemoryDump();
                }

                std::cout << "Load from binary file " << cFileName << " complete.\n";
            }
        }

        else if ( (strInput.c_str()[0] == 'p') && (strInput.c_str()[1] == 'r') && (strInput.c_str()[2] == 'i') && (strInput.c_str()[3] == 'n') && (strInput.c_str()[4] == 't') )
        {
            // save current program to ASCII file

            if (strInput.length() <= PRINT_LEN)
            {
                sprintf(cFileName, "%s", "list10.txt", strlen("list10.txt"));
            }
            else
            {
                sprintf(tmpbuf, "%s", strInput.c_str() + PRINT_LEN);
                sprintf(cFileName, "%s", tmpbuf, strlen(tmpbuf));
            }
            
            std::ofstream outputAsciiFile;
            outputAsciiFile.open (cFileName, std::ios::app);
            // char tmpbuf[20];

            for (i=0; i<MEMORY_SIZE; i++)
            {
                nClNum = i;
                memory->setCellCounter(i);
                nClVal = memory->getCellValue();
                //nClVal = memory->getCellNumber();
                // outputAsciiFile << formatMemoryCellToPrint(nClNum, nClVal) << std::endl;
                formatMemoryCellToPrint(nClNum, nClVal, tmpbuf);
                outputAsciiFile << tmpbuf << std::endl;
                // std::putf("this is a number: %d\n",i);
            }
            outputAsciiFile.close();
            std::cout << "Saving to ASCII file " << cFileName << " complete.\n";

            /*
            TODO: if error
                printf ("File %s can not be open for write!\n", cFileName);
            */

        }
        else if ( (strInput.compare("exit") == 0) || ( strInput.compare("quit") == 0)
                  || ( strInput.compare(":q") == 0) ) // end
        {
            EndFlag = 1;
            DebugModeFlag = 1;
        }
     } //while (!DBFlag);
     DebugModeFlag = 0;
    } // while (!EndFlag);

    pProc->printProcessorState();
    memory->printMemoryDump();
    }

    ~Prostotron()
    {
        std::cout << "*** Program complete. Bye***\n";
    }

private:
    int  i;
    int  nClNum;
    int  nClVal;
    int  nData;
    int  AsmModeFlag;
    int  EndFlag;
    int  DebugModeFlag;
    char tmpbuf[20];
    char cFileName[20];

    std::string strInput;
    std::string strDump;

    Processor *pProc;
    Memory *memory;
};


int main()
{
    // std::auto_ptr <Prostotron> pc(new Prostotron());
    std::unique_ptr <Prostotron> pc(new Prostotron());
    
    PrintIntroduction();

    try
    {
        pc->Run();
    }
       
    catch (std::runtime_error)
    {
        std::cout << "ATTN! Exception handler alarm!\n";
    }
    
    /*
    catch (error_message err)
    {
        std::cout << "ERROR: ";
        err.printMessage();
        std::cout << "\n";
    }
    */

    return 1;
}
