#include "parser.h"

/*
You are given a text, which contains different english letters and punctuation symbols. 
You should find the most frequent letter in the text. The letter returned must be in lower case.
While checking for the most wanted letter, casing does not matter, so for the purpose of your search, "A" == "a". Make sure you do not count punctuation symbols, digits and whitespaces, only letters.
If you have two or more letters with the same frequency, then return the letter which comes first in the latin alphabet. For example -- "one" contains "o", "n", "e" only once for each, thus we choose "e".
Input: A text for analysis as a string (unicode for py2.7).
Output: The most frequent letter in lower case as a string.
Precondition:
The password contains only ASCII symbols.
0 < len(text) <= 10^5

* */

checkio::checkio():
    _ret_letter ('a'),
    _max_n (0)
{
    //std::cout << "Parser constructor - created\n";
}

checkio::~checkio()
{
    //std::cout << "Parser destructor - erased\n";
}

char checkio::set_pass(std::string _pass_str)
{    
    // std::cout << "\npass: " << _pass_str << " len:" << _pass_str.length() << "\n";
    //
    
    for ( int i = 0; i < _pass_str.length(); i++ )
    {
        // std::cout << _pass_str[i] << " - " <<  std::tolower(_pass_str[i], loc) << "\n";
        this->chk_one_letter(_pass_str[i]);
    }
    
    // this->show_map();
    this->find_max();
    return _ret_letter;
}

void checkio::chk_one_letter(char _char_i)
{   
    char i;
    if (isalpha(_char_i))
    {
        i = std::tolower(_char_i, loc);
        // std::cout << " - " <<  std::tolower(i, loc) << "\n";
        // std::cout << " - " <<  i << "\n";
        it=mymap.find(i);
        //std::cout << " => " << it->second << '\n';
        if (it->second == 0)
        {
            mymap.insert ( std::pair<char, int>(i, 1) );
        }
        else
        {
            mymap[i]=mymap[i]+1; // mymap[i] = 1;
        }
    }    
    
}

void checkio::show_map()
{
    // show content:
    for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " --> " << it->second << '\n';
}

void checkio::find_max()
{
    int _tmp_ctr = 0;
    char _tmp_char;

    for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    {
        _tmp_char = it->first;
        _tmp_ctr = it->second;
        //std::cout << _tmp_char << " has " << _tmp_ctr << " occures \n";
        //std::cout << "current: " << _max_n << ", " << _ret_letter << "\n";
        if (_max_n < _tmp_ctr)
        {
            // std::cout << "New favourite: " << _tmp_char << " has " << _tmp_ctr << "\n";
            _max_n = _tmp_ctr;
            _ret_letter = _tmp_char;
        }
    }
}

/*
 * vector <int> checkio::run(vector <int> _viParameter)
{
    const int iSize = this->_max;

    vector <int> viRetArray;    
    viRetArray.clear();

    for ( int i = 0; i < _viParameter.size(); i++ )
    {
        // viRetArray.push_back(i);
        // cout << "_viParameter: " << _viParameter[i]  << "\n";
        if( std::count(_viParameter.begin(), _viParameter.end(), _viParameter[i]) > 1 )
        {            
            viRetArray.push_back(_viParameter[i]);
        }
    }
    
    // cout << "Count: viNumbers: " << std::count(_viParameter.begin(), _viParameter.end(), 3) << "\n";
    
    return viRetArray;
}
*/
