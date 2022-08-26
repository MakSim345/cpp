//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "create_array.h"

create_array::create_array()
{
    rndFilenameM = "file.txt";
    rndArrayM = new RandomNumbers();
    create_file();
}

create_array::create_array(std::string _file_name)
{
    rndFilenameM = _file_name;
    rndArrayM = new RandomNumbers();
    create_file();
}

void create_array::create_file()
{    
    rndFileM.open(rndFilenameM);
}

void create_array::save_to_file(const int arraySizeP)
{
    int random_number = 0;

    // myfile << "Writing this to a file.\n";
    for (int i = 0; i < arraySizeP; i ++)
    {
        random_number = rndArrayM->getRandomNumber(0, arraySizeP-1);
        // cout << i << " - Random number: " << random_number << endl;
        rndFileM << random_number << endl;
    }

    rndFileM.close();
}



