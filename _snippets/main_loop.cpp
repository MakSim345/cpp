
template<class T>
void swapVal(T obj1, T obj2)
{
    T temp = obj1;
    obj1 = obj2;
    obj2 = temp;
}

template<class superType>
void swapRef(superType &obj1, superType &obj2)
{
    cout << "called swapRef..." << endl;
    superType temp = obj1;
    obj1 = obj2;
    obj2 = temp;
}


int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;

    printf ("main - start\n");

    int a = 100, b = 200;
    cout << "Value:" << endl;
    cout << "1: a = " << a << " b = " << b << endl;
    swapVal(a, b);
    cout << "2: a = " << a << " b = " << b << endl;

    float aRef = 10.19, bRef = 11.30;
    cout << "Value:" << endl;
    cout << "1: a = " << aRef << " b = " << bRef << endl;
    swapRef(aRef, bRef);
    cout << "2: a = " << aRef << " b = " << bRef << endl;

/*************MAIN LOOP*****************/
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
    }
    /*
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
    }*/
} while (!RValue);

#ifdef USE_PAUSE_OR_BUTTON_PRESS
    std::cout << "\nPress ENTER to exit...\n";
    cin.get();

    // this PAUSE will give a info text - press any key to continue, etc.
    // system("PAUSE");

    // this pause is silent. You have to know to press any key.
    // system("pause>0");
#endif

printf ("Application complete.\n");
return 0;
}
