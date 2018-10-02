#include "gen.h"
#include "utils.h"
#include "dbits.h"
#include "cTimer.h"
#include <Windows.h>

void outputLine (ostream&, clientData);
void CreateDFile();
void outputData();
void InputData();

double readFileLoop(string s_logFileName, int nPrintValue);

#define CLIENT_NUM 100

double dGlobCounter = 0;
double ctrZERO = 0;
double ctrONE = 0;

int main(int argc, char *argv[] )
{
    int i=0;
    FILE *fres = NULL;
    long ZeroTime;
    int Diff_L;
    int nCtr;
    CTimer *t = new CTimer();
    int cp;
    int nPrintValue = 0;
    char StartTime[100]; 
    char EndTime[100];
    std::string ww;

    ZeroTime = t->Get1msTimeMS();
    // cout << "ZeroTime = " << ZeroTime;
    // cout << "argc = " << argc << "\n";
    
    if (argc <= 1)
    {
        printf ("Error: no input file!\n");
        printf ("Usage: app.exe File_to_calc_bits  <Print_output> \n");
        printf ("Example: file 'file_bit_calc.exe'... \n");        
        ww = "file_bit_calc.exe";
        cout << "File to open: " << ww << "\n";
    }
    else
    {
        ww = argv[1];
        cout << "File to open: " << ww << "\n";
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
    
    dGlobCounter = readFileLoop(ww, nPrintValue);

    printf ("\nFile '%s'", ww);
    printf (" consists %.0f bits, %.0f bytes\n", dGlobCounter * 8, dGlobCounter);
    printf ("Result: One = %.0f, Zero = %.0f\n", ctrONE, ctrZERO );
    printf ("Diff Time = %ld milliseconds\n ",  t->Get1msTimeMS() - ZeroTime);

    if ( (fres = fopen("CtrRes.log", "a+") ) != NULL)
    {
        fprintf (fres, "Counting ones and zeroes for file '%s':\n", argv[1]);
        // fprintf (fres, "Start: %s\n", StartTime);
        fprintf (fres, "File consists %.0f bits, %.0f bytes\n", dGlobCounter * 8, dGlobCounter);
        fprintf (fres, "Result: One = %.0f, Zero = %.0f\n", ctrONE, ctrZERO );
        fprintf (fres, "End:   %ld\n",  t->Get1msTimeMS());
        fprintf (fres, "\n");
    }
    
    return 0;
}

double readFileLoop(string s_logFileName, int nPrintValue)
{
    int c;
    double charCounter = 0;
    arrZero _arr;
    // cout << PrintTime();
    time_t start_time, end_time;
    
    // FILE* pStream = fopen(s_logFileName.c_str(), "a");
    FILE *fi = fopen(s_logFileName.c_str(), "r");
    
    std::cout << "readFileLoop - after open file... \n";
    
    if (!fi)
    {
        std::cout << "Unable to open file " << s_logFileName << " !!\n";
        return 0;
    }
    else
    {
        std::cout << "File " << s_logFileName << " was open. Processing.....\n";
    }
    
    std::time(&start_time);
    std::cout << "Start: " << start_time << "\n";

    while ((c= getc(fi)) != EOF)
    {
        //if (nPrintValue)
        //printf ("c = %d, *cp = %d\n", c, *cp);
        BitCalculation((unsigned)c, nPrintValue, &ctrONE, &ctrZERO);
        /*
        _arr = bitCalc((unsigned)c, nPrintValue);        
        ctrONE = ctrONE + _arr.one;
        ctrZERO = ctrZERO + _arr.zero;
        */
        charCounter++;
        // Sleep(3);
    }
    std::time(&end_time);
    std::cout << "\nTime diff: " << std::difftime(end_time, start_time) << "sec.\n";
    
    fclose (fi);
    return charCounter;
}

void CreateDFile()
{
    ofstream outCredit("credit.dat", ios::ate);
    clientData blankCLient = {0, "", "", 0.0}; // create one empty client
    for (int i=1; i <=CLIENT_NUM; i++)
    {
        outCredit.write((char*) &blankCLient, sizeof(blankCLient) );
    }
}

void outputData()
{
    clientData client;
    ifstream inCredit("credit.dat", ios::in);

    if (! inCredit)
    {
        cerr << "Can't open file!" << endl;
        exit (1);
    }

    //   cout << setiosflags(ios::left) << setw(6)  << "Account"
    cout << setw(6)  << "Account"
        << setw(16) << "Surname" << setw(11) << "Name"
        << setiosflags(ios::right)
        << setw(10) << "Balance" << endl;

    inCredit.read( (char*) &client, sizeof(clientData) );

    while (!inCredit.eof())
    {
        if (client.acctNum != 0)
            outputLine(cout, client);

        inCredit.read((char*) &client, sizeof(clientData));
    }
}

void InputData()
{
    // Input data to the file.....
    ofstream f_outCredit("credit.dat", ios::ate);

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

        f_outCredit.seekp((client.acctNum - 1) * sizeof (clientData));
        f_outCredit.write((char*) &client, sizeof(clientData));

        cout << "Enter an account number..." << endl << "? ";
        cin >> client.acctNum;
    }
    cout << "Thank you. Session is over now." << endl;
}

void outputLine (ostream &output , clientData c)
{
    output << setw(6) << c.acctNum;

    output << setw(16) << c.lastName << setw (11) << c.firstName
        << setw(10) << setprecision(5)
        << setiosflags(ios::showpoint | ios::right)
        << c.balance << endl;
}

