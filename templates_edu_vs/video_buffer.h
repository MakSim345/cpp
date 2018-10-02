#ifndef _VIDEO_BUFFER_H_
#define _VIDEO_BUFFER_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class video_buffer
{
public:    
    video_buffer();
    ~video_buffer();
    
    void makeFrame();

private:
    int *pixels;
    vector <string> main_array;    
    int _size;
};


#endif
