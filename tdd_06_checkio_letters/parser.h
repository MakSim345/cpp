#ifndef _PARSER_H_
#define _PARSER_H_

#include "gen.h"
#include <regex>

class checkio
{
public:
   checkio();
   ~checkio();   

   char set_pass(std::string _pass_str);
   void set_res();
   void chk_one_letter(char i);
   void chk_len_pass(int _len_pass);
   void show_map();
   void find_max();
   
private:
   int _max;
   char res;
   
   std::locale loc;
   std::map<char, int> mymap;
   std::map<char,int>::iterator it;
   int _max_n;
   char _ret_letter;
};

#endif
