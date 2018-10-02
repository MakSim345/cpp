//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "video_buffer.h"

//-------------------CLASS definition----------------
video_buffer::video_buffer()
{   
    int i = 0;
    int _width = 640;
    int _height = 480;

    // init random:
    srand(time(NULL));
    _size = _width * _height;

    // pixels = new int[_size];
     // Usage
    // std::tr1::shared_ptr<int> array (new int [_size], ArrayDeleter<int> ());
    std::shared_ptr<int> sub_pixels (new int [_size], ArrayDeleter<int> ());
    pixels = sub_pixels;
    
    for (i = 0; i<_size; i++)
    {
        int a = rand() % 2;
        pixels.get()[i] = a;     
    }
    
}

video_buffer::~video_buffer()
{   
    std::cout << sizeof(pixels);
    
    int size=sizeof pixels/sizeof(int);      //total size of array/size of array data type
    cout << size; 
    
    // delete [] pixels;
    //delete pixels;
}

void video_buffer::makeFrame()
{
    for (int i = 0; i<_size; i++)
    {
        //int a=rand() % matrix_array.size();
        // cout << i << " = " << pixels[i];
        cout << " " << pixels.get()[i];
        //cout << " ";
    }
    cout << endl;
}
//---------------END of CLASS Definition--------------

