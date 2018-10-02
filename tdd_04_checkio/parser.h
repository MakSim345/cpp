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

class checkio
{
public:
   checkio();
   checkio(int max_num);
   ~checkio();   

   void set_max(int max_num);
   int  get_max(void);
   vector <int> run(vector <int>);
   
private:
   int _max;
};

#endif
