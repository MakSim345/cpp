//
#include "gen.h" 
#include "printHex.h"
#include "virtual_foo.h"

#include <boost/ptr_container/ptr_list.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <iterator>
#include <algorithm>


class myABC
{
public:    
    myABC(string arg) {_my_name = arg;}
    ~myABC() {std::cout << _my_name << " Destroyed!!!" << "\n";} 
    std::string _my_name;
    int i;
    float j;
};

class CFucntDouble
{
public:
    CFucntDouble(double value)
    {
        x=value;
    }
    double GetValue()
    {
        return (x*x)-(2*x);
    }

private:
    double x;
};

int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    
    const char* ClassFileNaMe = "allegro.log";    
    
    printHex(ClassFileNaMe);

    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    // std::for_each( in(std::cin), in(), std::cout << (_1 * 3) << " " );
    //
    
    boost::ptr_list<myABC> intList;

    myABC *a = new myABC("One");
    myABC *b = new myABC("Two");
    myABC *c = new myABC("Three");
     
    a->i = 1;
    b->i = 2;
    c->i = 3;

    intList.push_back(a);
    intList.push_back(b);
    intList.push_back(c);

    intList.clear();

    // std::auto_ptr <myABC> m_pState;
    std::shared_ptr<myABC> srd_pointer;
    //srd_pointer
    //std::vector < boost::shared_ptr<myABC> > BunchOfObjects;
    //BunchOfObjects.push_back(boost::shared_ptr<A>(new B));
    
    // Test scoped_ptr:
    {
        boost::scoped_ptr<myABC> sPtr_myABC(new myABC("TECT_1"));
        sPtr_myABC->i = 12;
    }

    //*************MAIN LOOP*****************//
    cout << "\n$ > Press Any KEY to EXIT!" << std::endl;
    do 
    {
        //This is simple Windows way:
        Sleep(55);
        // active_matrix->run_matrix();
       
        //nResult = produceRND();   
        //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
       
        //nResult = produceRND();   
        //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            NewChar=(unsigned char)_getch();
            RValue = true;
            if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
            {
                RValue = true; // END mark
            }     
            if (NewChar == 'd')  // pressed
            {
                if (1 == CaptureModeHex) 
                    CaptureModeHex = 1;
                else
                    CaptureModeHex = 0;
            }
        }
    } while (!RValue); 

    printf ("Application complete.\n");
    return 0;
}


