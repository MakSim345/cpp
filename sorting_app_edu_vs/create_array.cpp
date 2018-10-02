//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "create_array.h"

Create_RND_Array::Create_RND_Array()
{
    _rnd_filename = "file.txt";
    _myRND = new CRandomNumbers();
    create_file();
}

Create_RND_Array::Create_RND_Array(std::string _file_name)
{
    _rnd_filename = _file_name;
    _myRND = new CRandomNumbers();
    create_file();
}

void Create_RND_Array::create_file()
{    
    rnd_file.open(_rnd_filename);
}

void Create_RND_Array::save_to_file(int arraySize)
{
    int random_number = 0;

    // myfile << "Writing this to a file.\n";
    for (int i = 0; i < arraySize; i ++)
    {
        random_number = _myRND->getRandomNumber(0, arraySize-1);
        // cout << i << " - Random number: " << random_number << endl;
        rnd_file << random_number << endl;
    }

    rnd_file.close();
}



