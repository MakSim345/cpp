#include "error_message.h"


// default constructor - init a string message
error_message::error_message():
	message("Attention - there is an error!")
{ }


void  error_message::printMessage() const
{
	std::cout << message << std::endl;
}

