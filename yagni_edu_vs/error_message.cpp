#include "error_message.h"

error_message::error_message():
	message("Attention - there is an error! Current oven cannot bake!\n") 	
{
    
}

void error_message::printMessage() const 
{
    printf ("%s", message);
}
