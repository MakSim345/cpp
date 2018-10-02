#include "parser.h"

/*
'''
Stephan and Sophia forget about security and use simple passwords for everything. 
Help Nikola develop a password security check module. The password will be considered 
strong enough if its length is greater than or equal to 10 symbols, it has at least one 
digit, as well as containing one uppercase letter and one lowercase letter in it. 
The password contains only ASCII latin letters or digits.
Input: A password as a string (Unicode for python 2.7).
Output: Is the password safe or not as a boolean or any data type that can 
be converted and processed as a boolean. In the results you will see the converted results.
* */

checkio::checkio():
    res(false),
    one_letter(false),
    one_digit(false),
    len_pass(false),
    cap_letter(false),
    is_alphanum(true),
    small_letter(false)
{
    //std::cout << "Parser constructor - created\n";
}

checkio::checkio(int _max_val)
    :_max(_max_val)
{
    //std::cout << "Parser constructor - created\n";
}

checkio::~checkio()
{
    //std::cout << "Parser destructor - erased\n";
}

bool checkio::set_pass(std::string _pass_str)
{
    // std::cout << "\npass: " << _pass_str << " len:" << _pass_str.length() << "\n";
    
    std::regex e ("[a-zA-Z0-9]+"); 

    chk_len_pass(_pass_str.length());

    for ( int i = 0; i < _pass_str.length(); i++ )
    {
        // std::cout << _pass_str[i] << "\n";
        this->chk_one_letter(_pass_str[i]);
    }
    
    this->set_res();
    return res;
}

void checkio::chk_one_letter(char i)
{
    if (isalnum (i))
    {
        if (isalpha(i))
        {
            one_letter = true;
            // check is capital:
            if (islower(i))
                {
                    small_letter = true;
                    //printf("chk_one_letter: %c is Low-case\n", i);
                }
            else
                {
                    cap_letter = true;
                    //printf("chk_one_letter: %c is Upper-Case\n", i);
                }
        }
        else
        {
            one_digit = true;
            //printf("chk_one_letter: %c is not letter\n", i);    
        }
    }
    else
    {
        //printf("chk_one_letter: %c is NOT alphanum\n", i);
        is_alphanum=false;
    }
}


void checkio::chk_len_pass(int len_pass_to_chk)
{
    if (len_pass_to_chk > 9)
    {
        len_pass = true;
        //printf("chk_len_pass: %d. OK passed. \n", len_pass_to_chk);    
    }    
    else
    {
        //printf("chk_len_pass: %d. NOT passed. \n", len_pass_to_chk);
    }
}

void checkio::set_res()
{
    if (one_letter && one_digit && len_pass && cap_letter && small_letter && is_alphanum)
        res = true;
    else
        res = false;
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

Parser::Parser()
{
    //std::cout << "Parser constructor - created\n";
}

Parser::~Parser()
{
    //std::cout << "Parser destructor - erased\n";
}

bool Parser::surrounded_by(const string& s, char left, char right)
{
    return s.at(0) == left && s.at(s.length()-1) == right;
}

void Parser::strip(string& s)
{
     static const string filter = "\r\n\t ";
     size_t right = s.find_last_not_of(filter);

     if (string::npos == right)
     {
        s.clear();
        return;
     }     
     size_t left = s.find_first_not_of(filter);
     if (string::npos == left)
     {
        left = 0;
     }

     s = s.substr(left, (right-left) + 1);
}

