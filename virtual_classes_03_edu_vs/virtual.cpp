//

#include <stdio.h>

class myClass
{   
public:
    virtual void foo() = 0;
     
    myClass()
    {
        init();
    }
    virtual ~myClass() {}
    void start() {printf ("started\n");}
     
protected:
    virtual void init() {}       

};

class myClassR : public myClass
{
public:
    void foo()
    {
        printf("myClassR is derived from myClass\n");
    }
 
    void init()
    {
        printf("init : myClassR is derived from myClass\n");
    }
 
    myClassR::~myClassR()
    {
        printf("myClassR destructor\n");
    }
};
/*
int main(int argc, _TCHAR* argv[])
{
    printf ("test\n");
	myClassR *mCR = new myClassR();
	mCR->foo();
	mCR->start();
	return 0;
}
*/
