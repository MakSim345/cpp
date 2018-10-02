#include "gen.h"


// Node class
class Node 
{ 
public:
    int         data;
    Node*       next;
 
    // create a new node: a = new Node (1, NULL);
    Node(int x, Node* addr) 
    {
        data = x;
        next = addr;
    }
};

class LinkedList
{
private:
    Node* head;

public:
    // initialize Linked list with a NULL head:
    LinkedList() { head = NULL; }

    // determinate if list is empty:
    bool is_empty()
    {
        if (head == NULL) return 1;
        else return 0;
    }

    // add an item to LinkedList:
    void node_push(int val)
    {
        Node* n = new Node(val, NULL);
        // n->data = val;
        n->next = head;
        head = n;
    }
    
    // add an item to LinkedList:
    void node_add(int val)
    {
        if (head == NULL) 
        {
            head = new Node(val, NULL);
        }
        else
        {
            Node* n = head;
            while(n->next != NULL) n = n->next;
            n->next = new Node(val, NULL);            
        }
    }

    // print a linked list
    void print() 
    {
        cout<<"[";
        if(head != NULL) 
        {
            if(head->next == NULL) 
            {
                cout << head->data << "-" << head->next;
            }
            else 
            {
                Node* n = head;
                while(n->next != NULL) 
                {
                    cout << n << ":" << n->data << "-" << n->next << " -> " ;
                    n = n->next;
                }
                cout<<n->data;
            }
        }
        cout<<"]\n";
    }
    
};


class App
{
public: 
    int Run()
    {   
        test();
        // create_list();
        // show_list( create_list() );
        // reverse( create_list() );
        
        return 1;
    }
    
    void test()
    {
        LinkedList L;
        LinkedList L2;
        for (int i = 0; i<10; i++)
        {
            // std::cout << i << " - " << this->get_rnd_number() << "\n";
            int i_rnd = get_rnd_number();
            L.node_add(i_rnd);
            L2.node_add(i_rnd);
        }
        L.print();
        L2.print();
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
