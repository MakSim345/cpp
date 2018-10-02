#ifndef _PARSER_H_
#define _PARSER_H_

#include "gen.h"
#include <regex>

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

   bool set_pass(std::string _pass_str);
   void set_res();
   void chk_one_letter(char i);
   void chk_len_pass(int _len_pass);
   
private:
   int _max;
   bool res;
   bool one_letter;
   bool one_digit;
   bool len_pass;
   bool cap_letter;
   bool small_letter;
   bool is_alphanum;
};

#endif
