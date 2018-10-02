#include "gen.h"
#include "linked_list.h"
#include "node_if.h"
#include <Windows.h>

class App
{
public:
    int Run()
    {
        // test();
        a_node* my_list = create_list();
        show_list(my_list);
        std::cout << "Reverse linked list...\n";
        a_node* rv_list = reverse(my_list);
        show_list(rv_list);
        return 1;
    }

    a_node * create_list()
    {
        std::cout << "Create a linked list of nodes: \n";

        a_node *list = NULL;

        //std::cout << sizeof(list) << "\n";
        for (int j = 0; j < 5; j++)
        {
            // std::cin >> i;
            // if (!i) break;
            int rnd_num = this->get_rnd_number();
            std::cout << "New number: " << rnd_num << "\n";

            a_node *pA_node = new a_node;
            pA_node->data = rnd_num;

            pA_node->next = list;
            list = pA_node;
        }

     return list;   
    }

    a_node* reverse(a_node* ptr)
    {
        a_node* temp;
        a_node* previous = NULL;
        while(ptr != NULL) 
        {
            temp = ptr->next;
            ptr->next = previous;
            previous = ptr;
            ptr = temp;
        }
        return previous;
    }

    void show_list(a_node *list)
    {
        while(list != NULL)
        {
            //std::cout << list->data << ", ";
            std::cout << list << ":[" << list->data << "]->" << list->next << "\n";
            list = list->next;
        }

    }

    int test()
    {
        std::cout << "Hello cruel world! \n";

        Item *first = 0;
        Item *p;
        std::cout << sizeof(first) << "\n";
        int i;
        for (int j = 0; j < 5; j++)
        {
            // std::cin >> i;
            i = this->get_rnd_number();
            std::cout << "Enter new number: " << i << "\n";
            if (!i) break;

            p = new Item;
            p->info = i;

            p->next = first;
            first = p;
        }

        p = first;
        while (p)
        {
            //std::cwout << "p->Item = " << p->Item << "\n";
            // std::cout << hex << "0x" << p << " - ";
            //std::cout << sizeof(p) << "\n";
            std::cout << "Address: "<< p << "\n";
            std::cout << "- info = " << p->info << "\n";
            std::cout << "- next cell address:" <<p->next << "\n\n";
            p = p->next;
        }

        /*
         * long num_to_search = 345345325;
        std::cout << "search by number " << num_to_search << " - "<< search_by_number(num_to_search) << "\n";
        Number t;
        std::cout << "\nEnter new name:\n";
        cin >> t.name;

        std::cout << "Enter new number:\n";
        cin >> t.number;

        add_data_to_file(t.name, atol(t.number.c_str()));
        */
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
    std::auto_ptr <App> my_maps(new App());
    try
    {
        my_maps->Run();
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
    return 1;
}
