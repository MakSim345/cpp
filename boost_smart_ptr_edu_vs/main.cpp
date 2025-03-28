//
#include "gen.h"
#include "virtual_foo.h"
#include "myABC.h"
#include "sPtrClass.h"

#include <boost/ptr_container/ptr_list.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

void simple_ptr_foo()
{
  sPtrClass* ptr = new sPtrClass();
  delete ptr;
}

void smart_ptr_foo()
{
   boost::scoped_ptr<sPtrClass> ptr(new sPtrClass);
   // boost::shared_ptr<A> ptr(new A);
   // boost::intrusive_ptr<A> ptr(new A);
}


int main(int argc, char *argv[], char *envp[])
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;

    printf ("main - start\n");

    // test pointer_list:
    {
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

        // this is not too necessary, but also works:
        intList.clear();
    }

    // Test boost::scoped_ptr:
    {
        boost::scoped_ptr<myABC> sPtr_myABC(new myABC("sPtr_myABC"));
        sPtr_myABC->i = 12;
        // In the end of the block the sPtr_myABC variable is destroyed and auto destroy the object.
    }

    // Test boost::shared_ptr:
    {
        boost::shared_ptr<myABC> spobj1; // Create non-initialized pointer
        boost::shared_ptr<myABC> spobj2(new myABC("spobj2"));; // Create non-initialized pointer
        spobj1 = spobj2; // increment reference counter

    }

    // Test std::shared_ptr:
    {
        // std::shared_ptr<myABC> srd_pointer1;
        std::shared_ptr<myABC> srd_pointer2(new myABC("std::shared_ptr srd_pointer2"));
    }

    // test std::auto_ptr:
    {
        std::auto_ptr <myABC> m_pState(new myABC("boost::auto_ptr m_pState"));
        m_pState->i = 29;

        std::auto_ptr<int> int_memory_manager(new int);
        *int_memory_manager = 5;
        std::auto_ptr<int> int_array_manager(new int[10]);
        // int_array_manager.get()[2] = 23;
        // std::cout << "int_array_manager" <<  int_array_manager.get()[2] << std::endl;
    }

    smart_ptr_foo();

    //std::vector < boost::shared_ptr<myABC> > BunchOfObjects;
    //BunchOfObjects.push_back(boost::shared_ptr<A>(new B));

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
    _CrtDumpMemoryLeaks();
    return 0;
}


