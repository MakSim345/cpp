#ifndef _PARSER_H_
#define _PARSER_H_

#include "gen.h"


class Parser
{
public:
    // Patient(const std::string& name, const std::string& location);
    Parser();

   ~Parser();
    
   bool surrounded_by(const string& s, char left, char right);
   void strip(string& s);
private:
};

#endif
