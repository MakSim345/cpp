#include "gen.h"
#include "linked_list_02.h"

class App
{
public: 
    int Run()
    {   
        test();
        // create_list();
        // show_list( create_list() );
        a_node* _my_list = create_list();
        show_list(_my_list);
        
        //reverseList(_my_list);
        //show_list(_my_list);
        
        a_node* rev_list = reverse(_my_list);
        show_list(rev_list);

        return 1;
    }

    a_node* create_list()
    {
        std::cout << "Create a linked list of nodes: \n";

        a_node *list = NULL;
        //list->data=0;
        //list->next=NULL;
        int max_items = 5;

        //std::cout << sizeof(list) << "\n";
        for (int j = 0; j < max_items; j++)
        {
            // std::cin >> i;
            // if (!i) break;
            int rnd_num = this->get_rnd_number();
            a_node *pA_node = new a_node;
            std::cout << "New number: " << rnd_num << ". Free Addr: " << pA_node << "\n";

            pA_node->data = rnd_num;            
            pA_node->next = list;
            // show_list(pA_node);
            list = pA_node;
            show_list(list);
        }

     return list;   
    }
    
    a_node* reverseList(a_node* head)
    {
        a_node* cursor = NULL;
        a_node* next;
        while (head)
        {
            next = head->next;
            head->next = cursor;
            cursor = head;
            head = next;
        }
        return cursor;
    }

    a_node* reverse(a_node* ptr)
    {
        a_node* temp = NULL;;
        a_node* previous = NULL;
        while(ptr != NULL) 
        {
            // std::cout << "a_node* temp = "<< temp << "\n";
            // print_node("a_node* temp = ", temp);
            std::cout << "a_node* temp: " << "\n";
            show_list(temp);
            std::cout << "a_node* ptr :" << "\n";
            show_list(ptr);

            temp = ptr->next;
            std::cout << "temp = ptr->next:" <<  ptr->next << "\n";           

            ptr->next = previous;
            std::cout << "ptr->next = previous:" <<  ptr->next << "\n";  

            previous = ptr;
            std::cout << "previous = ptr:" << previous << "\n";  

            ptr = temp;
            std::cout << "ptr = temp:" << ptr << "\n";  
        }
        return previous;
    }

    void print_node(std::string text, a_node* ptr)
    {
        if (ptr)
        {
            std::cout << text << ptr << ":" << ptr->data << "-" << ptr->next << "\n";
        }
        else
            std::cout << text << "NULL" << "\n";
    }


    void show_list(a_node *list)
    {
        int list_len = 0;        
        while(list != NULL)
        {
            std::cout << list << ":[" << list->data<< "]->" << list->next << "\n";
            
            list = list->next;
            list_len++;
            // print pointer tu NULL:
            //if (list == NULL)
            //{
            //    std::cout << list << ":[Nan]-NULL" << "\n";            
            //}            
        }
        std::cout << "List len = " << list_len << "\n";
    }

    int test()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        //-----------------------------
        ItemList *item_list = new ItemList();
        item_list->AddFirst(100);
        cout << '\n';           
    
        return 0;
    }

    int get_rnd_number(int iMin=10, int iMax=100)
    {
        int _tmp_rand_value = 0;
        int _retValue = 0;
        static int _fake_rnd = 1;

        _tmp_rand_value = rand();
        _retValue = _fake_rnd++; //( iMin + int( (iMax - iMin + 1) * _tmp_rand_value /(RAND_MAX + 1.0) ) );
        return _retValue;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

    App()
    {
        // init random generator:
        srand((unsigned)time(0));
        rand();
    }
};

int main()
{
    std::auto_ptr <App> my_list(new App());
    try
    { 
        long a1 = std::clock();
        std::cout << "Time Start: " << a1 << "\n";

        my_list->Run();

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
    //std::string p;
    system("PAUSE");
    //std::cout << "\nPress any key to exit...\n";
    //cin >> p;
    return 1;
}
