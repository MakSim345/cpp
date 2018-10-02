#ifndef _MINI_GUI_H_
#define _MINI_GUI_H_
//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

class mini_gui
{
 public:
    mini_gui();
    void showErrMesage(const std::string err_msg) const;
 private:
    const char * message;
};
    
// float quotient(int num1, int num2);

#endif
