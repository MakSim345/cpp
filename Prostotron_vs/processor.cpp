//
#include "processor.h"


//*****************************************
// Class Processor implementation

void Processor::runProgramInMemory(const int isTraceP)
    /*
      MemCell* memory //pointer to an array!,
      Processor* pProc,
      int Trace*/
{
    int  StopFlag = 0;
    std::string cInput("0");
    std::string cInTrace("0");

    setProgramCounter(MEMORY_START_ADDRESS); // set counter to the start == 0

    do
     {
        // copy next memory cell to the instruction register IR:
        this->setInstructionRegister(mMemory->getCellValue(this->getProgramCounter()) );
        // get an operation code and operand from IR:
        this->decodeInstruction();
        // save an address of memory cell where data is:
        mMemory->setCellCounter(getOperand());

        if (isTraceP)
        {
            mMemory->printMemoryDump ();
            this->printProcessorState();
            std::cout << "\nPress Enter to TRACE >> ";
            std::getline (std::cin, cInTrace);
            if (cInTrace.length())
            {
                printf ("*******************************************************\n");
                printf ("STOP. TRACE interrupted by user!\n");
                printf ("\n*******************************************************\n");
                StopFlag = 1;
                break;
            }
        }

        switch ( this->getOpCode() )
        {
         case READ: // 10 - read a word from the terminal to the memory cell
            std::cout << " Enter value: > ";
            std::getline (std::cin, cInput);

            mMemory->setCellValue(cInput.c_str()); //
            this->incProgramCounter();
            break;

         case WRITE:// 11 - print a word from the memory cell to the terminal
            // memory->PrintCurCellNumber();
            printf ("\nOutput: \n");
            printf ("*******************************************************\n");
            mMemory->printCellValue();
            printf ("\n*******************************************************\n");
            this->incProgramCounter();
            break;

         case LOAD: // 20 - save a word from the memory cell to an accumulator
            this->setAccumulator( mMemory->getCellValue() );
            this->incProgramCounter();
            break;

        case STORE: // 21 - save a word from accumulator to memory cell
            mMemory->setCellValue(this->getAccumulator());
            this->incProgramCounter();
            break;

         case ADD: // 30 - 
            this->setAccumulator(this->getAccumulator() + mMemory->getCellValue());
            this->incProgramCounter();
            break;

         case SUBTRACT: // 31
            this->setAccumulator(this->getAccumulator() - mMemory->getCellValue()); //
            this->incProgramCounter();
            break;

         case DIVIDE: // 32
            if (this->getAccumulator() == 0)
            {
                printf ("ERROR: divide to zero!\n");
                printf ("Program complete by error.\n");
                StopFlag = 1;
            }
            else
            {
                this->setAccumulator(mMemory->getCellValue() / this->getAccumulator());
            }
            this->incProgramCounter();
            break;

         case MULTIPLY:
            this->setAccumulator(this->getAccumulator() * mMemory->getCellValue()); //
            this->incProgramCounter();
            break;

         case BRANCH: //GOTO
            this->setProgramCounter(getOperand());
            break;

         case BRANCHNEG: // branch if accumulator is negative
            if (this->getAccumulator() < 0)
                this->setProgramCounter(getOperand());
            else
                this->incProgramCounter();
            break;

         case BRANCHZERO:
            if (this->getAccumulator() == 0)
                this->setProgramCounter(getOperand());
            else
                this->incProgramCounter();
            break;

         case HALT:
            printf ("Program complete.\n");
            StopFlag = 1;
            break;

         case NOOP:
             this->incProgramCounter();
             break;

         default:
            printf ("Unexpected value in the address %d\n", getOperand());
            StopFlag = 1;
        }// case

        if (isTraceP)
        {
          //mMemory->printMemoryDump ();
          //this->printProcessorState();
          //printf("\nPress Enter to TRACE >> ");
          //gets_s(cInTrace);
        }

    } while (!StopFlag);

    mMemory->printMemoryDump ();
    this->printProcessorState();

};
// constructor / destructor:
Processor::Processor()
{
    setAccumulator(0);
    setProgramCounter(0);
    setInstructionRegister(0);
    setOpCode(0);
    setOperand(0); // this is an address of cell in the current command
}

Processor::~Processor()
{
    //printf ("destructor called!\n");
}

void Processor::decodeInstruction()
{
    setOpCode(mInstructionRegister / 100);
    setOperand(mInstructionRegister % 100);
}

void Processor::printProcessorState()
{
    printAccumulator();
    printProgramCounter();
    printInstrRegister();
    printOpCode();
    printOperand();
}

void  Processor::setAccumulator (int nAccum)
{
    mAccumulator = nAccum;
}

int  Processor::getAccumulator ()
{
    return mAccumulator;
}

void Processor::printAccumulator()
{
    printf ("- Accumulator  = %d\n", mAccumulator );
}

void Processor::setProgramCounter(int newProgramCounterP)
{
    mProgramCounter = newProgramCounterP;
}

int Processor::getProgramCounter()
{
    return mProgramCounter;
}

void Processor::printProgramCounter()
{
    printf ("- ProgCounter  = %d\n", mProgramCounter);
}

int Processor::incProgramCounter()
{
    return mProgramCounter++;
}

void Processor::setInstructionRegister(int newInsRegP)
{
    mInstructionRegister = newInsRegP;
}

int Processor::getInstructionRegister()
{
    return mInstructionRegister;
}

void Processor::printInstrRegister()
{
    printf ("- InstrRegister= %d\n", mInstructionRegister);
}

void Processor::setOpCode(int newOpCodeP)
{
    mOpCode = newOpCodeP;
}

int  Processor::getOpCode()
{
    return mOpCode;
}

void Processor::printOpCode()
{
    printf ("- OpCode       = %d, %s\n", mOpCode, getOpCodeDesctiption(mOpCode).c_str());
}

void Processor::setOperand(int newOperandP)
{
    mOperand = newOperandP;
}

int  Processor::getOperand()
{
    return mOperand;
}

void Processor::printOperand()
{
    printf ("- Operand      = %d\n", mOperand);
}

std::string Processor::getOpCodeDesctiption(int _opCode)

{
    static std::map<int, std::string> OpCodeMap;
    if(OpCodeMap.empty()) // Only runs once.
    {
        OpCodeMap[0]  = "NO OPERATION - program will stop";
        OpCodeMap[10] = "READ - read from terminal to selected memory address";
        OpCodeMap[11] = "WRITE - print to terminal value of selected memory";
        OpCodeMap[20] = "LOAD - from selected memory address to accumulator";
        OpCodeMap[21] = "SAVE - from accumulator to selected memory address";
        OpCodeMap[30] = "ADD - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[31] = "SUBTRACT - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[32] = "DIVIDE - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[33] = "MULTIPLY - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[40] = "BRANCH - Goto selected memory address, unconditional";
        OpCodeMap[41] = "BRAMCHNEG - Goto selected memory address, if accumulator is negative";
        OpCodeMap[42] = "BRANCHZERO - Goto selected memory address, if accumulator is zero";
        OpCodeMap[43] = "HALT - full stop";
    }
    return OpCodeMap[_opCode];
}
