#ifndef _CREATE_ARRAY_H_
#define _CREATE_ARRAY_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"
#include "RandomNumbers.h"

class Create_RND_Array
{
public:    
    Create_RND_Array();
    Create_RND_Array(std::string _file_name);
    ~Create_RND_Array();
    void save_to_file(int arraySize);

protected:    
    void create_file();
    CRandomNumbers *_myRND;

private:
    std::string _rnd_filename;
    ofstream rnd_file;
};


#endif
