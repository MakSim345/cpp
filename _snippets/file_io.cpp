#include "gen.h"
//#include "utils.h"
//#include "dbits.h"
#include "timer.h"
#include <Windows.h>

struct clientData
{
    int acctNum;   
    char lastName[15];
    char firstName[10];
    float balance;
};

struct arrZero
{
    int zero;
    int one;
};

void outputLine (ostream&, clientData);
void CreateDFile();
void outputData();
void InputData();
double readFileLoop(string s_logFileName, int nPrintValue);
void BitCalculation(unsigned Val, int nPrintRes, double* ArrONE, double* ArrZERO);

#define CLIENT_NUM 100

double COUNTER_ZEROS = 0;
double COUNTER_ONES = 0;

int main(int argc, char *argv[] )
{
    int i=0;
    FILE *fres = NULL;    
    int Diff_L;
    int nCtr;
    int cp;
    int nPrintValue = 0;
    char StartTime[100]; 
    char EndTime[100];
    double fileCharCounter = 0;

    std::string openFileName = "gen.h"; // "_test_project.sdf"; // "file_bit_calc.exe";
    // CTimer *t = new CTimer();
    // 
    // cout << "argc = " << argc << "\n";
    
    // cout << "PrintTime():  " << PrintTime() << "\n";
    long ZeroTime = Get1msTimeMS();
    cout << "ZeroTime = " << ZeroTime;

    if (argc <= 1)
    {
        printf ("Error: no input file!\n");
        printf ("Usage: app.exe File_to_calc_bits  <Print_output> \n");
        printf ("Example: file 'file_bit_calc.exe'... \n");                
        cout << "File to open: " << openFileName << "\n";
    }
    else
    {
        openFileName = argv[1];
        cout << "File to open: " << openFileName << "\n";
    }

    if (argc > 1)
    {
        if (argv[2] == NULL)
        {
            nPrintValue = 0;
            printf ("argv[1] =%s\n",argv[1]);
        }
        else // if (argv[2] == 1)
        {
            nPrintValue = 1;
            printf ("argv[2] =%s\n",argv[2]);
        }    
    }

    // nPrintValue = 1;    
    fileCharCounter = readFileLoop(openFileName, nPrintValue);

    printf ("\nFile '%s'", openFileName.c_str());
    printf ("consists %.0f bits, %.0f bytes\n", fileCharCounter * 8, fileCharCounter);
    printf ("Result: One = %.0f, Zero = %.0f\n", COUNTER_ONES, COUNTER_ZEROS );
    printf ("Diff Time = %ld milliseconds\n ",  Get1msTimeMS() - ZeroTime);    

    if ( (fres = fopen("CtrRes.log", "a+") ) != NULL)
    {
        fprintf (fres, "Counting ones and zeros for file '%s':\n", argv[1]);
        // fprintf (fres, "Start: %s\n", StartTime);
        fprintf (fres, "File consists %.0f bits, %.0f bytes\n", fileCharCounter * 8, fileCharCounter);
        fprintf (fres, "Result: One = %.0f, Zero = %.0f\n", COUNTER_ONES, COUNTER_ZEROS );
        // fprintf (fres, "End:   %ld\n",  t->Get1msTimeMS());
        fprintf (fres, "\n");
    }

    cp = 49;// argv[1];

    if (cp == 49) // input 1
    {
        printf ("Input data\n");
        InputData();
    }
    else if (cp == 50) // create empty 2
    {
        printf ("Create empty dataFile with 100 records\n");
        CreateDFile(); 
    }
    else
    {
        printf ("Output dataFile.\n");
        outputData(); 
    }

    printf ("Selection is over!\n");

    // system ("PAUSE");
    return 0;
}

double readFileLoop(string fileNameP, int printValueP)
{
    int nextChar;
    double charCounter = 0;
    // arrZero _arr;
    // cout << PrintTime();
    time_t start_time, end_time;

    std::time(&start_time);
    // std::cout << "Start: " << start_time << "\n";
    
    // FILE* pStream = fopen(s_logFileName.c_str(), "a");
    FILE *fileToRead = fopen(fileNameP.c_str(), "r");
    
    std::cout << "readFileLoop - after open file... \n";
    
    if (!fileToRead)
    {
        std::cout << "Unable to open file " << fileNameP << " !!\n";
        return 0;
    }
    else
    {
        std::cout << "File " << fileNameP << " was open. Processing.....\n";
    }
    while ((nextChar= getc(fileToRead)) != EOF)
    {
        //if (printValueP)
        //printf ("c = %d, *cp = %d\n", c, *cp);
        BitCalculation((unsigned)nextChar, printValueP, &COUNTER_ONES, &COUNTER_ZEROS); // TODO: remove global variables!
        /*
        _arr = bitCalc((unsigned)nextChar, printValueP);        
        COUNTER_ONES = COUNTER_ONES + _arr.one;
        COUNTER_ZEROS = COUNTER_ZEROS + _arr.zero;
        */
        charCounter++;
        // Sleep(3);
    }
    
    std::time(&end_time);
    std::cout << "\nTime spend for calculation: " << std::difftime(end_time, start_time) << " sec.\n";

    fclose (fileToRead);
    return charCounter;
}

void CreateDFile()
{
    ofstream fileOutCredit("credit.dat", ios::ate);
    clientData blankCLient = {0, "", "", 0.0}; // create one empty client
    for (int i=1; i <=CLIENT_NUM; i++)
    {
        fileOutCredit.write((char*) &blankCLient, sizeof(blankCLient) );
        //fileOutCredit << std::putf("this is a number: %d\n",i);
    }
}

void outputData()
{
    clientData client;
    ifstream fileInCredit("credit.dat", ios::in);

    if (!fileInCredit)
    {
        cerr << "Can't open file!" << endl;
        exit (1);
    }

    // cout << setiosflags(ios::left) << setw(6)  << "Account"
    
    // REM: setw() need #include <iomanip>
    // print TABLE HEADER:
    cout << setw(6)  << "Account"
        << setw(16) << "Surname" << setw(11) << "Name"
        << setiosflags(ios::right)
        << setw(10) << "Balance" << endl;

    fileInCredit.read( (char*) &client, sizeof(clientData) );

    while (!fileInCredit.eof())
    {
        if (client.acctNum != 0)
        {
            outputLine(cout, client);
        }
        fileInCredit.read((char*) &client, sizeof(clientData));
    }
}

void InputData()
{
    // Input data to the file.....
    ofstream fileOutCredit("credit.dat", ios::ate);

    cout << "Enter an account number..."
        << "(from 1 to 100, 0 - for complete input)" << endl << "? ";

    clientData client;
    cin >> client.acctNum;

    while (client.acctNum >0 && client.acctNum <=100)
    {
        cout << "Input Surname" << endl << "? ";
        cin >> client.lastName;

        cout << "Name" << endl << "? ";
        cin >> client.firstName;

        cout << "Balance" << endl << "? ";
        cin >> client.balance;

        fileOutCredit.seekp((client.acctNum - 1) * sizeof (clientData));
        fileOutCredit.write((char*) &client, sizeof(clientData));

        cout << "Enter an account number..." << endl << "? ";
        cin >> client.acctNum;
    }
    cout << "Input data complete." << endl;
}

void outputLine (ostream &output , clientData c)
{
    output << setw(6) << c.acctNum;

    output << setw(16) << c.lastName << setw (11) << c.firstName
        << setw(10) << setprecision(5)
        << setiosflags(ios::showpoint | ios::right)
        << c.balance << endl;
}

void BitCalculation(unsigned Val, int nPrintRes, double* ArrONE, double* ArrZERO)
{
    unsigned BIT = 7;
    //unsigned BIT = 15;
    //unsigned   BIT = 30;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;
 
    /*if (nPrintRes)
    {
        printf ("0x%X ", Val);
    //printf ("%c", Val);
    }*/
     
    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? 1 : 0 ;
        if (1==nBin)
        {
            *ArrONE = *ArrONE +1;
            //printf ("ONE = %.0f\n", *ArrONE);
        }
        else if (0==nBin)
        {
            *ArrZERO = *ArrZERO + 1;
            //printf ("ZERO = %.0f\n", *ArrZERO);
        }
        if (nPrintRes)
        {
            printf ("%d", nBin);
        }     
        Val<<=1;
         
        //if ((c%8 == 0) && nPrintRes)
        //    printf (" ");       
    }
 
    if (nPrintRes)
        printf (" ");
}

