#include "idcard.h"

idcard::idcard(int n)
    :_number(n)
{
	// _number = n;
}

idcard::idcard()
{
	_number = 0;
}

int idcard::getNumber()
{
    return this->_number;
}

    