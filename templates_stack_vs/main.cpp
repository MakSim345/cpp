//
#include "gen.h" 
#include "printHex.h"

//#include "virtual_foo.h"
#include "my_smart_pointer.h"
#include "my_templates.h"



void StackTest()
{
    // Stack <int> myStack(5);
    
    /*
    Stack <int> myStack(5);
 
    // fill the stack:
    cout << "Push some items to Stack: ";
    int ct = 0;
    while (ct++ != 5)
    {
        int temp;
        cin >> temp;
        myStack.push(temp);
    }
 
    myStack.printStack();
 
    cout << "\nRemove 2 items from the Stack:\n";
 
    myStack.pop(); // Remove an item
    myStack.pop(); // Remove an item
    myStack.printStack(); // print to screen
 */
}


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
    
    int a = 100, b = 200;
    cout << "Value:" << endl;
    cout << "Before swapVal: a = " << a << " b = " << b << endl;
    swapVal(a, b);
    cout << "After swapVal: a = " << a << " b = " << b << endl;

    float aRef = 10.19, bRef = 11.30;
    cout << "Value:" << endl;
    cout << "Before swapRef: a = " << aRef << " b = " << bRef << endl;
    swapRef(aRef, bRef);
    cout << "After swapRef: a = " << aRef << " b = " << bRef << endl;
    
//*************MAIN LOOP*****************//
cout << "\n$ > Press Any Key to exit." << std::endl;
do 
{
    //This is simple Windows way:
    Sleep(55);

   // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        NewChar=(unsigned char)_getch();
        RValue = true;
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


