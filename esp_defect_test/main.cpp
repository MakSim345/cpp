#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

int main()
{
    static const int BUF_SIZE = 100;
    char cmd[BUF_SIZE];
    const char* pLayoutName = "JAP"; 

    /*
     *
    const char* pLayoutName = pKeyboardLayoutsM->at(keyboardIndex); 
    
    cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
    
    printf("result %d DIV_10 %d = %d\n",a , b, i);
    float res = a / 10.0;
    
    */

    strcpy(cmd, "setxkbmap -layout ");
    int pos = strlen(cmd); //#lint !e713 Loss of precision (return) (unsigned long to int)
    strcpy(&cmd[pos], pLayoutName);
    /*
    MSF_ASSERT(pos + strlen(pLayoutName) < (BUF_SIZE - 1));
    MSF_TRACE("keyboard", ("Keyboard setting command is '%s'", cmd));
    system(cmd);
    */
    printf("Result: pos = %d\n", pos);
    printf("Keyboard setting command is '%s'\n", cmd);    

    return 1;
}

