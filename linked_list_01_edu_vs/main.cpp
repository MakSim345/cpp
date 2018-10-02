//
#include "gen.h" 
#include "linked_list_01.h"
#include "node_list.h"

struct Person
{
    int age;
    int height;
    int weight;

    string name;
    string job;
};

int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");

	Node n = Node (1);
	n.append(3);
	n.append(2);
	n.append(81);


//*************MAIN LOOP*****************//
cout << "\n$ > Press Ctr-X to exit." << std::endl;

//my_matrix *active_matrix  = new my_matrix();

do 
{
    //This is simple Windows way:
    Sleep(55);
        
    // active_matrix->run_matrix();
   
   //nResult = produceRND();   
   //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   
   //nResult = produceRND();   
   //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

   // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        RValue = true;
        NewChar=(unsigned char)_getch();    
        if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
        {
            RValue = true; // END mark
        }     
        if (NewChar == 'd')  // pressed
        {
            if (1 == CaptureModeHex) 
                CaptureModeHex = 1;
            else
                CaptureModeHex = 0;
        }
    }
} while (!RValue);  
printf ("Application complete.\n");
return 0;
}


