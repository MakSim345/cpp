//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "mini_gui.h"

mini_gui::mini_gui() : 
    message("geLeHue Ha HoLb!\n")
{
 
}

void mini_gui::showErrMesage(std::string err_msg) const 
{
    MessageBoxA(NULL, err_msg.c_str(), "Exception catched!", NULL);
}
