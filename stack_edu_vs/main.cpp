#include "gen.h"
#include "stack_impl.h"

// linked_list

class App
{
public: 
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        //-----------------------------
        Node *top=NULL;          //Start with init a pointer to top steck with null
        top = first(1);          //Create first element on the stack
 
        for(int i = 2; i < 10; i++)
        {
            push( &top, this->get_rnd_number() );       //Add four new elements to stack
            //std::cout << "p->Item = " << p->Item << "\n";
            // std::cout << hex << "0x" << p << " - ";
            //std::cout << sizeof(p) << "\n";
            std::cout << "Address: "<< top << "\n";
            std::cout << "- info = " << top->d << "\n";
            std::cout << "- next cell address:" <<top->p << "\n\n";
            // p = p->next;
        }

        while(top)            //Print every element of the stack and remove it from memory. in the loop.
        {                     //loop is running till top!=null
            cout << '\n';           
            cout << pop(&top) << ' '; // print results of pop() function
        }
        cout << '\n';           
    
        return 0;
    }
    
    App()
    {
        init_random_gen();
    }

    void init_random_gen()
    {
        srand((unsigned)time(0));
        rand();
        return;
    }

    int get_rnd_number(int iMin=0, int iMax=101)
    {
        int _tmp_rand_value = 0;
        int _retValue = 0;

        _tmp_rand_value = rand();
        _retValue = ( iMin + int( (iMax - iMin + 1) * _tmp_rand_value /(RAND_MAX + 1.0) ) );
        return _retValue;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    std::auto_ptr <App> my_stack(new App());
    try
    { 
        long a1 = std::clock();
        std::cout << "Time Start: " << a1 << "\n";

        my_stack->Run();

        long b1 = std::clock();
        std::cout << "Time END: " << b1 << "\n\n";
        std::cout << "Open file Time TOTAL: " << (b1-a1)/1000.0 << " sec.\n";
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }    
    */
    
    //std::cout << "\nPress any key to exit...\n";
    system("PAUSE");
    
    return 1;
}
