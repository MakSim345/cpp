#ifndef _ID_CARD_H_
#define _ID_CARD_H_

#include "gen.h"

class idcard
{
public:

    idcard(int n);
    idcard();

    ~idcard()
    {
        _number = 0;
    }

    void setDateExpire(string newDate)
    {

        this->_date_expire = newDate;
    }

    string getDateExpire()
    {

        return _date_expire;
    }

    void setNumber(const int newNumber)
    {
        _number = newNumber;
    }

    int getNumber();    

    string _date_expire;
    int _number;

};


#endif
