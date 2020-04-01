#include "gen.h"
#include "cTimer.h"

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a=255)
{
    return (a<<24) + (b<<16) + (g<<8) + r;
}

void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
{
    r = (color >>  0) & 255;
    g = (color >>  8) & 255;
    b = (color >> 16) & 255;
    a = (color >> 24) & 255;
}

void drop_ppm_image_2(const std::string filename, const std::vector<uint32_t> &image, const size_t w, const size_t h)
{
    assert(image.size() == w*h);
    std::ofstream ofs(filename);
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for (size_t i = 0; i < h*w; ++i)
    {
        uint8_t r, g, b, a;
        unpack_color(image[i], r, g, b, a);
        ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
    }
    ofs.close();
}

void drop_ppm_image(const std::string filename, const std::vector<uint32_t> &image, const size_t w, const size_t h) 
{
    assert(image.size() == w*h);
    std::ofstream ofs(filename);
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for (size_t i = 0; i < h*w; ++i)
    {
        uint8_t r, g, b, a;
        unpack_color(image[i], r, g, b, a);
        ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
    }
    ofs.close();
}

int t()
{
    return 0;
}



// ===================================
int main(int argc, char *argv[], char *envp[])
{
    long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int Counter=0;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    long lNexTime;

    printf ("main - start\n");
    CTimer *_time = new CTimer ();

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

if (argc >= 2)
{
  // i = atoi(argv[1]);
  if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
  {
   // t->PrintIntroduction();
   return 1;
  }
}

    const size_t win_w = 512; // image width
    const size_t win_h = 512; // image height
    std::vector<uint32_t> framebuffer(win_w*win_h, 255); // the image itself, initialized to red

    for (size_t j = 0; j<win_h; j++) 
    { // fill the screen with color gradients
        for (size_t i = 0; i<win_w; i++) 
        {
            uint8_t r = (255*j)/float(win_h); // varies between 0 and 255 as j sweeps the vertical
            uint8_t g = (255*i)/float(win_w); // varies between 0 and 255 as i sweeps the horizontal
            uint8_t b = 0;
            framebuffer[i + j*win_w] = pack_color(r, g, b);
        }
    }

    drop_ppm_image("./out.ppm", framebuffer, win_w, win_h);


    printf ("Application complete.\n");
    return 0;

//*************MAIN LOOP*****************//
 cout << "Press Ctr-X to exit." << std::endl;
 do
  {
    //This is simple Windows way:
    // Sleep(1000);
    // std::cout << "Time GetTickCount:" << GetTickCount() << "\n";

    // nResult = produceRND();
    // printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

    //nResult = produceRND();
    //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

    /***************************************
    // This is complicated one-thread way:
    if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
    {
        printf ("Time: %ld.\n",Get1msTimeMS());
        Sleep(100);

        LastTimeInMS = Get1msTimeMS();
    }
    ***************************************/
    long lStartTime = get_time_ms();
    printf("Elapsed time: %ld milliseconds\n", lStartTime);
    for (int i = 0;i < 5000000; i++)
        ;
    
    lNexTime = get_time_ms();
    printf("Elapsed time: %ld milliseconds\n", lNexTime - lStartTime);
    sleep(2);
    
    lNexTime = get_time_ms();
    printf("Elapsed time: %ld milliseconds\n", lNexTime - lStartTime);    
    // control of endless loop (may be also in monitor.cpp)
    /*
    if (kbhit())  // has anything been pressed from keyboard ?
    {
        RValue = true;
        NewChar=(unsigned char)getch();
        if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
        {
            RValue = true; // END mark
        }
    }
    */


} while (!RValue);

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

printf ("Application complete.\n");
return 0;
}

