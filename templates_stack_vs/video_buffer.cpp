//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "video_buffer.h"

//-------------------CLASS definition----------------
video_buffer::video_buffer()
{   
    _size = 64 * 48;
    // init random:
    srand(time(NULL));
    
    this->pixels = new int[_size];
    
    for (int i = 0; i<_size; i++)
    {
        int a = rand() % 2;
        pixels[i] = a;        
    }

}

video_buffer::~video_buffer()
{   
    delete [] pixels;
}

void video_buffer::makeFrame()
{
    for (int i = 0; i<_size; i++)
    {
        //int a=rand() % matrix_array.size();
        // cout << i << " = " << pixels[i];
        cout << " " << pixels[i];
        //cout << " ";
    }
    cout << endl;
}
//---------------END of CLASS Definition--------------

