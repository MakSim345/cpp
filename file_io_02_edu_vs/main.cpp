#include "gen.h" 
#include "utils.h"
#include "dbits.h"
#include "cTimer.h"
    
#define mkdir(path) mkdir(path,0700)
 
struct date
{
    int da_year;   
    char da_day;   
    char da_mon;   
};    

union number
{
    int x;
    float y;
};

struct clientData
   {
     int acctNum;   
     char lastName[15];
     char firstName[10];
     float balance;
   };    
   
void outputLine (ostream&, clientData);
void CreateDFile();
void outputData();
void InputData();

#define CLIENT_NUM 100

double GlobCounter = 0;
double ctrZERO = 0;
double ctrONE = 0;


int main( int argc, char *argv[] )
{
    int i=0;      
 
// #define YS9039384  
#ifdef YS9039384  
    char* FileNameF = "Result.log";
    FILE *fi = NULL;     
#endif          
    FILE *fi = NULL;
    FILE *fres = NULL;
    long SatelZeroTime;
    CTimer *t = new CTimer();
    int cp;

    printf ("argc = %d\n", argc);

    SatelZeroTime = t->Get1msTimeMS();    
    printf ("SatelZeroTime = %ld\n", SatelZeroTime);    

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

    system ("PAUSE");
    return 0;
                
         
#ifdef YS9039384   
    if ( (fi = fopen(FileNameF, "a+") ) != NULL)     
    {
        fclose (fi);    
    }
#endif 

    return 0;   
}

void CreateDFile()
{
    ofstream fileOutCredit("credit.dat", ios::ate);
    clientData blankCLient = {0, "", "", 0.0}; // create one empty client
    for (int i=1; i <=CLIENT_NUM; i++)
    {
        fileOutCredit.write((char*) &blankCLient, sizeof(blankCLient) );
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
 
