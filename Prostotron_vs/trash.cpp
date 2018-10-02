pProc->InstructionCounter(START_ADDRESS); // set counter to the start == 0
 
do  
{
        // copy next memory cell to the Register:
        pProc->InstructionRegister(memory[pProc->InstructionCounter()].Get_CellValue() );
        // get an operation code and operand from Register:
        pProc->GetCOPO(); 
        // save an address of memory cell where data is:
        operand = pProc->Operand();

        switch ( pProc->OperationCode() )
        {
         case READ: // 10 - read a word from the terminal to the memory cell
            printf (" > ");
            gets(cInput);
            memory[operand].Set_CellValue(cInput); //
            pProc->InstructionCounterInc();
            break;

         case WRITE:// 11 - print a word from the memory cell to the terminal
            memory[operand].Print_CellValue(); 
            printf ("\n");
            pProc->InstructionCounterInc();
            break;
         
         case LOAD: // 20 - save a word from the memory cell to an accumulator
            pProc->Accumulator( memory[operand].Get_CellValue() ); 
            pProc->InstructionCounterInc();
            break;

        case STORE: // 21 - //save a word from accumulator to memory cell
            memory[operand].Set_CellValue( pProc->Accumulator() ); 
            pProc->InstructionCounterInc();
            break;

         case ADD:
            pProc->Accumulator(pProc->Accumulator() + memory[operand].Get_CellValue()); //
            pProc->InstructionCounterInc();
            break;

         case SUBTRACT:
            pProc->Accumulator(pProc->Accumulator() - memory[operand].Get_CellValue()); //
            pProc->InstructionCounterInc();
            break;

         case DIVIDE:
            if (pProc->Accumulator() == 0)
            {
                printf ("ERROR: divide to zero!\n");
                printf ("Program complete by error.\n");
                StopFlag = 1;
            }
            else
            {
                pProc->Accumulator(memory[operand].Get_CellValue() / pProc->Accumulator());
            }            
            pProc->InstructionCounterInc();
            break;

         case MULTIPLY:
            pProc->Accumulator(pProc->Accumulator() * memory[operand].Get_CellValue()); //
            pProc->InstructionCounterInc();
            break; 

         case BRANCH:
            pProc->InstructionCounter(operand);
            break;

         case BRANCHNEG: // branch if accumulator is negative
            if (pProc->Accumulator() < 0) 
                pProc->InstructionCounter(operand);
            else
                pProc->InstructionCounterInc();
            break;

         case BRANCHZERO:
            if (pProc->Accumulator() == 0) 
                pProc->InstructionCounter(operand);
            else
                pProc->InstructionCounterInc();
            break;

         case HALT:
            printf ("Program complete.\n");
            StopFlag = 1;
            break;      
                
         default: 
            printf ("Unexpected value in the address %d\n", operand);
            StopFlag = 1;
        }// case        
     
