#ifndef _OVEN_H_
#define _OVEN_H_

#include "gen.h"

class iOven
{
public:
    virtual ~iOven(){}

    virtual void start()=0;
    virtual void stop()=0;
    //virtual void open()=0;
    //virtual void close()=0;
    virtual bool canBake()=0;

private:
    int _oven_type;
};


class ElectricOven: public iOven
{
public:
    ElectricOven();
    virtual ~ElectricOven();


    virtual bool canBake();   
    virtual void start();
    virtual void stop();

private:
    std::string mCurrency; // 110 - 220 volt
    std::string mColor;
    bool isCurrency;
    //...
};

class GasOven: public iOven
{
public:
    GasOven();
    
    virtual ~GasOven();
    
    virtual void start();
    virtual void stop();
    virtual bool canBake();   

private:
    int _gas_level;
    std::string mColor;
    //...
};
#endif
