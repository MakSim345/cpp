//main.cpp
#include "gen.h"
#include "CompressionIf.h"
#include "transport.h"


using namespace std;

class Compressor
{
public:
    Compressor(CompressionIf* comp)
        : pCompression(comp)
    {
        // empty constructor;
    }
    ~Compressor() { delete pCompression; }
    
    void compress(const string & str_file_name) 
    {
      pCompression->compress(str_file_name);
    }

private:
    CompressionIf* pCompression;
};

int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;

    printf ("main - start\n");
    
    Compressor* pCmp;
    pCmp = new Compressor(new ZIP_Compression);
    pCmp->compress( "file.txt");

    pCmp = new Compressor(new ARJ_Compression);
    pCmp->compress( "file.txt");

    RAR_Compression *p_rar = new RAR_Compression();
    pCmp = new Compressor(p_rar);
    pCmp->compress( "file.txt");

    delete pCmp;

    //own_car *pOwn_Car = new own_car();
    //pOwn_Car->drive();
    TakeTransport * pTakeTransp = new TakeTransport();
    pTakeTransp->setStrategy(2);
    pTakeTransp->doIt();
    
    //
    //
    //
       
    //*************MAIN LOOP*****************//
    cout << "\n$ > Press any key to exit....." << std::endl;
    do
    {
        //This is simple Windows way:
        Sleep(55);
        // active_matrix->run_matrix();
       
        //nResult = produceRND();   
        //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   
        //nResult = produceRND();   
        //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

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
