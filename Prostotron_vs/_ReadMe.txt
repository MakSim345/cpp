2002

Simple emulator of a micro-computer.
Provide ability to make ASM programming, memory dump and so on.

Implemented as a lab work during reading book:
"C++ How to Program" by Deitel. 

--------------------------
cmd is a command instead of -9999
--------------------------

Set of instructions:

// Input-Output operations:
#define READ   10 // read a word from the terminal to the memory cell
#define WRITE  11 // print a word from the memory cell to the terminal

// Save-Load operations:
#define LOAD   20 //save a word from the memory cell to an accumulator
#define STORE  21 //save a word from accumulator to memory cell

// Arithmetic operations:
#define ADD      30
#define SUBTRACT 31
#define DIVIDE   32
#define MULTIPLY 33

//Brunching operations:
#define BRANCH     40
#define BRANCHNEG  41
#define BRANCHZERO 42
#define HALT       43 // Total stop

#define START_ADDRESS 0	
#define MEMORY_SIZE   100


        switch ( this->OperationCode() )
        {
         case READ: // 10 - read a word from the terminal to the memory cell
            printf (" Enter value: > ");
            gets(cInput);
            memory->SetCellValue(cInput); //
            this->InstructionCounterInc();
            break;

         case WRITE:// 11 - print a word from the memory cell to the terminal
            // memory->PrintCurCellNumber(); 
            printf ("Output: \n");
            printf ("**************\n");
            memory->PrintCellValue();
            printf ("\n**************\n\n");
            this->InstructionCounterInc();
            break;
         
         case LOAD: // 20 - save a word from the memory cell to an accumulator
            this->Accumulator( memory->GetCellValue() ); 
            this->InstructionCounterInc();
            break;

        case STORE: // 21 - //save a word from accumulator to memory cell
            memory->SetCellValue(this->Accumulator()); 
            this->InstructionCounterInc();
            break;

         case ADD:
            this->Accumulator(this->Accumulator() + memory->GetCellValue());
            this->InstructionCounterInc();
            break;

         case SUBTRACT:
            this->Accumulator(this->Accumulator() - memory->GetCellValue()); //
            this->InstructionCounterInc();
            break;

         case DIVIDE:
            if (this->Accumulator() == 0)
            {
                printf ("ERROR: divide to zero!\n");
                printf ("Program complete by error.\n");
                StopFlag = 1;
            }
            else
            {
                this->Accumulator(memory->GetCellValue() / this->Accumulator());
            }            
            this->InstructionCounterInc();
            break;

         case MULTIPLY:
            this->Accumulator(this->Accumulator() * memory->GetCellValue()); //
            this->InstructionCounterInc();
            break; 

         case BRANCH: //GOTO
            this->InstructionCounter(Operand());
            break;

         case BRANCHNEG: // branch if accumulator is negative
            if (this->Accumulator() < 0) 
                this->InstructionCounter(Operand());
            else
                this->InstructionCounterInc();
            break;

         case BRANCHZERO:
            if (this->Accumulator() == 0) 
                this->InstructionCounter(Operand());
            else
                this->InstructionCounterInc();
            break;

         case HALT:
            printf ("Program complete.\n");
            StopFlag = 1;
            break;      
                
         default: 
            printf ("Unexpected value in the address %d\n", Operand());
            StopFlag = 1;
        }// case

