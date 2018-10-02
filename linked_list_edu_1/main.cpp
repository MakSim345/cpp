#include <iostream>
#include <vector>
#include <numeric>
#include "trace_logger.h"
#include "linked_list.h"
#include "print_util.h"

using namespace std;
class my_class;

void test_auto_list()
{
    auto_list *head;
    auto_list *tail;
    auto_list n;
 
    head = tail = NULL;
 
    strcpy(n._name, "yuriy");
    strcpy(n._auto, "dodge");
    n._number = 1;
    n._next = NULL;
}

struct node
{
    int num;
    node *link;
} *p;

void node_test()
{
    node *root;
    root = new node;
    root->num = 5;
    root->link = p;
    p = root;

    node *q;
    for (q = p; q != NULL; q = q->link)
    {
        cout << q->num;
        cout << "\n";
    }
}

void test_Item()
{
    Item *first = 0;
    Item *p;
    int i;

    cout << "Enter few elements for a list. End with zero. " << "\n";
    for (;;) 
    {
        // input till 0
        cin >> i;
        if (!i)
            break;

        // create new item
        p = new Item;
        p->info = i;

        // link new to list_begin
        p->next = first;
        first = p;
    }
    
    p = first;
    std::cout << "\nResult linked list: \n";
    while (p) 
    {
        cout << p->info << "\n";
        cout << p->next << "\n\n";
        p = p->next;
    }
}

int main()
{
    int array[5] = {1,2,3,4,5};
    int _fact = 4;
    // cout << "Enter a number for a factorial" << "\n";
    // std::cout << array << std::endl; 
    // cout << "Your name is " << name << "." << endl;
    // vector <int> int_arr (23, 10);   
    // vector<my_class> my_class_array;
    return 0;
}

class my_class
{
public:
    int get_var() {return var;}
    void run (int a) {var = a;} 
    
    void print_my_vector()
    {
        for (int i = 0; i < int_arr.size(); ++i)
        {
            cout << "int_arr[" << i << "] = " << int_arr[i] << "." << endl;    
        }
    }
    
    void make_my_vector(int _var, int _count)
    {     
        int_arr = vector <int>(_var, _count);
    }
    
    void add_to_vector(int _var)
    {
        int_arr.push_back(_var);
    }

    int vector_sum()
    {
        int _ret_val = std::accumulate (int_arr.begin(), int_arr.end(), 0);
        return _ret_val;
    }

private:
    int var;
    vector <int> int_arr;
};
