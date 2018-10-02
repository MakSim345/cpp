// Linked List in C/C++ - Inserting a node at beginning
// link:
// https://www.youtube.com/watch?v=cAZ8CyDY56s&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=6
// Reverse a linked list - Iterative method
// https://www.youtube.com/watch?v=sYcOK51hl-A&index=9&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P

#include "gen.h"
#include <Windows.h>

struct Item
{
    int info;
    Item* next;
};

struct Node
{
    int data;
    Node* next;
};

class App
{
public:
    int Run()
    {
        // test1();
        test2();
        return 0;
    }

    App()
    {
        init_random_gen();
    }

    void Insert(int x)
    {
        Node* temp = new Node();
        temp->data = x;
        temp->next = head;
        head = temp;
    }

    // Node* Reverse(Node* tmp_head)
    void Reverse()
    {
        // reverse a linked list:
        Node* current;
        Node* prev;
        Node* tmp_next;
        current = head;
        prev = NULL;
        while (current != NULL) 
        {
            tmp_next = current->next;
            current->next = prev;
            prev = current;
            current = tmp_next;
        }
        head = prev;
        //return
    }

    void ReversePrint(Node* tmp_head)
    {
        // recursive print of a linked list:
        if (tmp_head == NULL) return;
        ReversePrint(tmp_head->next);
        std::cout << tmp_head << ":[" << tmp_head->data << "]->" << tmp_head->next << "\n";
    }

    void Print()
    {
        Node* temp = head;
        while (temp != NULL)
        {
            std::cout << temp << ":[" << temp->data << "]->" << temp->next << "\n";
            temp=temp->next;
        }
    }

    void test2()
    {
        head = NULL; // empty list

        int i;
        for (int j = 0; j < 5; j++)
        {
            Insert(get_rnd_number());
        }
        std::cout << "Print: \n";
        Print();
        std::cout << "ReversePrint: \n";
        ReversePrint(head);
        // Reverse(head);
        std::cout << "Reverse list: \n";
        Reverse();
        Print();
    }

    void test1()
    {
        std::cout << "Hello cruel world! \n";

        Item *first = 0;
        Item *p;
        std::cout << sizeof(first) << "\n";
        int i;
        for (int j = 0; j < 5; j++)
        {
            i = this->get_rnd_number();
            std::cout << "Enter new number: " << i << "\n";
            std::cin >> i;
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

private:
    Node* head;

};

int main()
{
    std::auto_ptr <App> linked_list_test(new App());
    try
    {
        linked_list_test->Run();
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
