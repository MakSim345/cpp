#ifndef _OVEN_H_
#define _OVEN_H_

#include "gen.h"

class ovenIf
{
public:
    virtual void start()=0;
    virtual void stop()=0;
    virtual bool canBake()=0;

    virtual ~ovenIf(){}

private:
    int _oven_type;
};


class electricOven: public ovenIf
{
public:
    electricOven();
    virtual ~electricOven();
    
    virtual bool canBake();   
    virtual void start();
    virtual void stop();

private:
    std::string mCurrency; // 110 - 220 volt
    std::string mColor;
    bool isCurrency;
    //...
};

class gasOven: public ovenIf
{
public:
    gasOven();
    
    virtual ~gasOven();
    
    virtual void start();
    virtual void stop();
    virtual bool canBake();   

private:
    int _gas_level;
    std::string mColor;
    //...
};
#endif
