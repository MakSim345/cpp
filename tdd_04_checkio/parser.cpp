#include "parser.h"

checkio::checkio()
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

void checkio::set_max(int _max_val)
{
    this->_max = _max_val;
}

int checkio::get_max(void)
{
   return  this->_max;
}

vector <int> checkio::run(vector <int> _viParameter)
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
    
    //replace this for solution
    //result= []
    //for elme in data:
    //    if data.count(elme) > 1:
    //        result.append( elme )
    //return result
    
    return viRetArray;
}




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

