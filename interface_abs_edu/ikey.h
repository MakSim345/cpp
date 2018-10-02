#ifndef _IKEY_H_
#define _IKEY_H_

class iKey
{
public:
    virtual ~iKey(){}        
    virtual void Open() =0;    
private:
    int _key_type;
};

#endif