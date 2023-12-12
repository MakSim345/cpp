#include "counter.h"

Counter::Counter()
	:counterM(0)
{
    // std::cout << "Hello! New Counter appears\n";
}

Counter::~Counter()
{
    // std::cout << "Counter: Good bye!\n";
}
    
int Counter::Increment() 
{
    // this->counterM++;
    return this->counterM++;
}

int Counter::Decrement() 
{
    if (0 == this->counterM)
    {
    	return this->counterM;
	} 
	else 
	{
		return this->counterM--;
	}
    
}

void Counter::PrintMe() const
{
    printf ("%d", this->counterM);
}

