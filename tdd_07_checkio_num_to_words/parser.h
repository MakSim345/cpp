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
   std::string set_num(int num_to_convert);
   void set_res();
   void chk_one_letter(char i);
   void chk_len_pass(int _len_pass);
   void show_map();
   void find_max();
   bool is_out_of_range(int _to_check);
   
private:
   int _max;
   char res;
   
   vector <std::string> FIRST_TEN;
   vector <std::string> SECOND_TEN;
   vector <std::string> OTHER_TENS;
   
   std::string HUNDRED;
      
   std::locale loc;
   std::map<char, int> mymap;
   std::map<char,int>::iterator it;
   int _max_n;
   char _ret_letter;
};

#endif
