#ifndef _OVEN_IF_H_
#define _OVEN_IF_H_

#include "gen.h"

class OvenIf
{
public:
    virtual ~OvenIf(){}

    virtual void start()=0;
    virtual void stop()=0;
    //virtual void open()=0;
    //virtual void close()=0;
    virtual bool canBake()=0;

private:
    int _oven_type;
};

#endif
