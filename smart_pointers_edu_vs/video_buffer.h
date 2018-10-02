#ifndef _VIDEO_BUFFER_H_
#define _VIDEO_BUFFER_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

template <typename T>
class ArrayDeleter
{
public:
    void operator () (T* d) const
    {
        delete [] d;
    }
};

class video_buffer
{
public:    
    video_buffer();
    ~video_buffer();
    
    void makeFrame();

private:
    // int *pixels;
    std::shared_ptr<int> pixels;
    vector <string> main_array;    
    int _size;
};


#endif
