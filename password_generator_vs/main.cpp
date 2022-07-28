#include "gen.h"
#include "password_generator.h"

using namespace std;

int main(int argc, char *argv[])
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    int mainLoopCtr = 0;
    const int mainLoopMax = 10;
	const int passLen=20;

    printf ("Password generation app - start:\n");

    PassGenerator *pPassGen = new PassGenerator();

#define FILE_OUTPUT
#ifdef FILE_OUTPUT
	int nOpenFileToken = 0;
	char *FileNameF = "PasswordsResult.log";
	FILE *fi = NULL;

    // open the file for input:
    if ( (fi = fopen(FileNameF, "a+") ) != NULL)
    {
        printf ("file %s was open succesfully\n", FileNameF);
        nOpenFileToken = 1;
    }
    else
    {
        printf ("ERR: file %s was not open\n", FileNameF);
        // getchar(); // pause
        nOpenFileToken = 0;
    }

    // fprintf(fi, "Start time: %d\n", Get1msTime());
    fprintf(fi, "Start time: %ld\n", getTimeMs());
#endif// FILE_OUTPUT

    if (argc >= 2)
    {
        // i = atoi(argv[1]);
        if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
        {
            PrintIntroduction();
            return 1;
        }
    }


//*************MAIN LOOP*****************//
do
{
#ifdef WIN32_APP
    //This is simple Windows way:
    Sleep(1000);
#else
    //This is simple UNIX way:
    sleep(1);
#endif

    string curPass = pPassGen->genPass(passLen);
    cout << curPass;
    fprintf(fi, "%s\n", curPass.c_str());
    cout << endl;

    nResult = produceRND();
    //printf ("1-Time: %ld. RND: %d\n", Get1msTimeMS(), nResult);

    nResult = produceRND();
    //printf ("2-Time: %ld. RND: %d\n", Get1msTimeMS(), nResult);

    // control of endless loop (may be also in monitor.cpp)
    mainLoopCtr++;

    if (mainLoopCtr >= mainLoopMax)
    {
        RValue = true; // END mark
    }

} while (!RValue);

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

printf ("Application complete.\n");
return 0;
}
