#ifndef _CREATE_ARRAY_H_
#define _CREATE_ARRAY_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"
#include "RandomNumbers.h"

class create_array
{
public:    
    create_array();
    create_array(std::string _file_name);
    ~create_array();
    void save_to_file(const int arraySizeP);

protected:    
    void create_file();
    RandomNumbers *rndArrayM;

private:
    std::string rndFilenameM;
    ofstream rndFileM;
};


#endif
