#include "gen.h"
#include "cTimer.h"
#include "RandomNumbers.h"
#include "phone_book.h"
#include "Person.h"

int main(int argc, char *argv[], char *envp[]) 
{
	long LastTimeIn=0;	
	long LastTimeInMS = 0;	
	int RValue = false;
	int Counter=0;  
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;

    printf ("main - start\n");
    CTimer *_time = new CTimer ();
    
// #define FILE_OUTPUT
#ifdef FILE_OUTPUT
	int nOpenFileToken = 0;
	char *FileNameF = "TimeSt.log";
	FILE *fi = NULL; 
    CTimer *t = new CTimer();
 
    // open the file for input:	
    if ( (fi = fopen(FileNameF, "a+") ) != NULL)
    {
        // printf ("file %s was open succesfully\n", FileNameF);
        nOpenFileToken = 1;
    }
    else
    {
        printf ("file %s was not open\n", FileNameF);
        getchar();
        nOpenFileToken = 0;
    }
	      
    fprintf(fi, "Start time: %d\n", t->Get1msTimeMS());
#endif// FILE_OUTPUT

    if (argc >= 2)
    {
        // i = atoi(argv[1]);
        if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
        {
            // t->PrintIntroduction();
            return 1;
        }
    }   

    std::fstream fileSource("text.txt");
    vector <Number> phoneBookArray;

    while (true) // till EOF will occur
    {
        Number _tmpNumber;
        fileSource >> _tmpNumber.name;
        
        if (fileSource.eof()) {break;}

        fileSource >> _tmpNumber.number;
        
        if (fileSource.eof()) { break;}

        phoneBookArray.push_back(_tmpNumber);
    }

    while (true)
    {
        string inputName;
        cout << "Enter name (or :q)\n";
        cin >> inputName;

        if (inputName == ":q")  { break; }

        for (unsigned int i = 0; i < phoneBookArray.size(); i++)
        {
            if (phoneBookArray[i].name == inputName)
            {
                cout << inputName << " - " << phoneBookArray[i].number << "\n";
            }
        }
     }

    //*************MAIN LOOP*****************//
    cout << "Press any key to exit." << std::endl;
    do 
    {
        //This is simple Windows way:
        Sleep(1000);      
        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            NewChar=(unsigned char)_getch();
            RValue = true;            
        } 
} while (!RValue);  

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
printf ("Application complete.\n");
return 0;
}

