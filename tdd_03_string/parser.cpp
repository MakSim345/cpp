#include "parser.h"

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

