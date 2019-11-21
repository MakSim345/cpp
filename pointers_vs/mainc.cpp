#include "gen.h"
#include "utils.h"


class COPSvCommunication
{
public:
    COPSvCommunication()
        : isCOPSvM(true)
    {

    }

    // simply get references to value created in main and change them
    void getParams(int &getWeightP, int &getAgeP)
    {
        getWeightP = weight;
        getAgeP = age;
    }
    
    const char* getModuleVersionString()
    {
        return this->getString();
    }

    const char* getString () const
    {
        char vstrM[] = " COP SW Pr. 889071-3.2   1996-04-26"; 
        return vstrM;
    }

    bool isModuleCompatible() const
    {
        int minorVer = 9;
        int majorVer = 3;// rConfigurationM.getModuleVersions(&minorVer);

        // rConfigurationM.getModuleVersionString();

        // std::lock_guard<Os::Mutex> lock(mutexM);

        if (isCOPSvM || // all COPSv are supported
            (majorVer == 3 && minorVer >= 2) || (majorVer > 3) || // all COP versions >= 3.2 are supported
            (majorVer == 0 && minorVer == 3)) // this is an exception. The module with the 
            // version 0.3 is also compatible
        {
            return true;
        }

        return false;
    }

private:
    int weight;
    int age;
    bool isCOPSvM;
    enum { maxSlowStringChar = 64 };
    // char vstrM[maxSlowStringChar];
    
};

class Programmers
{
public:
    Programmers()
    {

    }

    Programmers(int iWeightP, int iAgeP)
    {
        this->weight = iWeightP;
        this->age = iAgeP;
    }

    // simply get references to value created in main and change them
    void getParams(int &getWeightP, int &getAgeP)
    {
        getWeightP = weight;
        getAgeP = age;
    }

private:
    int weight;
    int age;
};

void testProgrammers()
{
    // long g_lTimeTick = 0;
    const int ARR_SIZE = 9;
    Programmers *prog [ARR_SIZE];
    Programmers *ptr = nullptr;

    for (int i=0; i < ARR_SIZE; i++)
    {
        ptr = new Programmers(i + 100, i);
        prog[i] = ptr;
    }

    int w, a;
    int count = ARR_SIZE;

    //create pointer to pointer,
    //array's name ("prog") is a pointer to it's first element
    Programmers **iter = prog;

    for (int i=0; i < count; i++)
    {
        ptr = *iter++;
        ptr->getParams(w, a);
        if( *(iter-1) != nullptr )
        {
            delete *(iter-1);
            ptr = nullptr;
        }
        cout << w << "\t" << a << endl;
    }
}

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

#ifdef FILE_OUTPUT
    int nOpenFileToken = 0;
    char *FileNameF = "TimeSt.log";
    FILE *fi = NULL;

    // open the file for input:
    if ( (fi = fopen(FileNameF, "a+") ) != NULL)
    {
        // printf ("file %s was open succesfully\n", FileNameF);
        nOpenFileToken = 1;
    }
    else
    {
        printf ("file %s was not open\n", FileNameF);
        getchar(); // pause, xyLe...
        nOpenFileToken = 0;
    }

    fprintf(fi, "Start time: %d\n", Get1msTime());
#endif// FILE_OUTPUT

    char *FileNameF = "TimeSt.log";
    COPSvCommunication *tRun = new COPSvCommunication();
    
    printf ("string - %s\n", tRun->getModuleVersionString() );

    const char* snIndex = strstr(tRun->getModuleVersionString(), "Pr. 8");

   //if (strstr(tRun->getModuleVersionString(), "Pr. 8") == 0)
    if (snIndex)
    {
        printf ("Compare - MATCH, OK\n");
    }
    else
    {
        printf ("Compare - NOT MATCH\n");
    }
    

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
 {
   fclose (fi);
 }
#endif

printf ("\nApplication complete.\n");

system ("PAUSE"); // wait for press any key in VS mode

return 0;

}



