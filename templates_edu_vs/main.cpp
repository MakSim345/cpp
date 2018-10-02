//
#include "gen.h" 
#include "printHex.h"
#include "my_smart_pointer.h"
#include "my_templates.h"

int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    //CFucntInt *_my_int = new CFucntInt(arraySize);
    Funct<int> cI(25);
	Funct<double> cD(3.12);
	cout << "cI " << cI.GetValue() << endl;
	cout << "cD " << cD.GetValue() << endl;
    cout << "cI " << endl;

    //my_smart_pointer<MyClass> pMyCLass

    const int cCount = 5;
    const int aCount = 6;
    char cArray[aCount] = "HELLO";
    int intArray[cCount] =  {1,2,3,4,5};
    float floatArray[cCount] =  {1.2 ,2.5, 3.0 ,4.9 ,5.5};

    printArray(cArray, cCount);
    printArray(intArray, cCount);
    printArray(floatArray, cCount);

    int n1 = 5, n2 = 10, n3;
    float f1 = 5.1f, f2 = 10.5f, f3;

    n3 = Max( n1, n2 );
    f3 = Max( f1, f2 );
    
//*************MAIN LOOP*****************//
cout << "\n$ > Press Any Key to exit." << std::endl;
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
        NewChar=(unsigned char)_getch();
        RValue = true;            
    } 
} while (!RValue);  
printf ("Application complete.\n");
return 0;
}


