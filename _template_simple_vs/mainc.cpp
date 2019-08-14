#include "gen.h"
#include "utils.h"

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
        getWeightP=weight;
        getAgeP=age;
    }

private:
    int weight;
    int age;
};


long g_lTimeTick = 0;

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









//*************MAIN LOOP*****************//
 do
 {
   //This is simple Windows way:
   Sleep(1000);

   nResult = produceRND();
   printf ("1-Time: %ld. RND: %d\n",Get1msTimeMS(), nResult);

   nResult = produceRND();
   printf ("2-Time: %ld. RND: %d\n",Get1msTimeMS(), nResult);

  // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
      RValue = true; // END mark
    }


}while (!RValue);

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
 {
   fclose (fi);
 }
#endif

printf ("Application complete.\n");

system ("PAUSE"); // wait for press any key in VS mode

return 0;

}



