#include "parser.h"

/*
"""
Stephen's speech module is broken. This module is responsible for his number pronunciation. 
He has to click to input all of the numerical digits in a figure, so when there are big 
numbers it can take him a long time. Help the robot to speak properly and increase his number 
processing speed by writing a new speech module for him. All the words in the string must be 
separated by exactly one space character. Be careful with spaces -- it's hard to see if you place 
two spaces instead one.
Input: A number as an integer.
Output: The string representation of the number as a string.
How it is used: This concept may be useful for the speech synthesis software or automatic reports systems. 
This system can also be used when writing a chatbot by assigning words or phrases numerical 
values and having a system retrieve responses based on those values.
Precondition: 0 < number < 1000

"""
*/

checkio::checkio():
    _ret_letter ('a'),
    _max_n (0)
{
    //std::cout << "Parser constructor - created\n";
    FIRST_TEN.push_back ("zero"); // ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
    FIRST_TEN.push_back ("one");
    FIRST_TEN.push_back ("two");
    FIRST_TEN.push_back ("three");
    FIRST_TEN.push_back ("four");
    FIRST_TEN.push_back ("five");
    FIRST_TEN.push_back ("six");
    FIRST_TEN.push_back ("seven");
    FIRST_TEN.push_back ("eight");
    FIRST_TEN.push_back ("nine");

    // ["ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"]
    SECOND_TEN.push_back ("ten");
    SECOND_TEN.push_back ("eleven");
    SECOND_TEN.push_back ("twelve");
    SECOND_TEN.push_back ("thirteen");
    SECOND_TEN.push_back ("fourteen");
    SECOND_TEN.push_back ("fifteen");
    SECOND_TEN.push_back ("sixteen");
    SECOND_TEN.push_back ("seventeen");
    SECOND_TEN.push_back ("eighteen");
    SECOND_TEN.push_back ("nineteen");

    // OTHER_TENS = ["0", "1", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]
    OTHER_TENS.push_back("0");
    OTHER_TENS.push_back("1");
    OTHER_TENS.push_back("twenty");
    OTHER_TENS.push_back("thirty");
    OTHER_TENS.push_back("forty");
    OTHER_TENS.push_back("fifty");
    OTHER_TENS.push_back("sixty");
    OTHER_TENS.push_back("seventy");
    OTHER_TENS.push_back("eighty");
    OTHER_TENS.push_back("ninety");

    HUNDRED = "hundred";
    //
}

checkio::~checkio()
{
    //std::cout << "Parser destructor - erased\n";
}

bool checkio::is_out_of_range(int _to_check)
{
    bool _ret_val = false;

    if ((0 > _to_check) ||  (_to_check > 1000))
        _ret_val = true;

    return _ret_val;
}

std::string checkio::set_num(int _num_to_check)
{
    std::cout << "number to check:" << _num_to_check << "\n";
    
    if (is_out_of_range(_num_to_check))
        return "out of range";
    
    int _fir = 0;
    int _sec = 0;
    int _tre = 0;

    if( _num_to_check <= 9)       
        return FIRST_TEN[_num_to_check];
    
    if ((9 < _num_to_check) && (_num_to_check < 20))
        {
         int a = _num_to_check % 10;
         return SECOND_TEN[a];
        }

    if ((20 <= _num_to_check) && (_num_to_check < 100))
    {
        _fir = int(_num_to_check / 10);
        _sec = _num_to_check % 10;

        if (_sec == 0)
            return OTHER_TENS[_fir];
        else
            return OTHER_TENS[_fir] + " " + FIRST_TEN[_sec];
    }
    
    if ((100 <= _num_to_check) && (_num_to_check < 1000))
    {
        std::string _ret_val;
        _fir = int(_num_to_check / 100);
        _sec = int ((_num_to_check % 100 - _num_to_check % 10) / 10);
        _tre = _num_to_check % 10;
        // print _fir , " " , _sec , " " , _tre
        _ret_val = FIRST_TEN[_fir] + " " +  HUNDRED;

        if (_sec == 1)
        {
             _ret_val = _ret_val + " " + SECOND_TEN[_tre];
             return _ret_val;
        }
        else if (_sec > 1)
        {
             _ret_val = _ret_val + " " + OTHER_TENS[_sec];
        }
        
        if (_tre != 0)
            _ret_val = _ret_val + " " + FIRST_TEN[_tre];
        
        return _ret_val;
    }
    return _num_to_check, " - False";
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
