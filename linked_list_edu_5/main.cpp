#include "iostream"
using std::cout;
using std::cin;
using std::endl;
#include "linked_list.h"

int main()
{
    node<int>* r = new node<int>;
    r->data = 8;

    node<int>* s = new node<int>;
    s->data = 5;

    list<int>* l = new list<int>;

    int arr[] = { 7, 6, 1, 4};
    for(int i=0; i<=3; i++)
    {
        node<int>* nodeTemp = new node<int>(arr[i]);
        l->insert(nodeTemp);
    }

    l->print();


    l->insertBefore(r,1);
    cout<<endl;
    l->print();
    cout<<endl;
return 0;
    l->insertAfter(s, 5);
    cout<<endl;
    l->print();
    cout<<endl;

    l->delNode(4);
    cout<<endl;
    l->print();
    
    l->delAtLoc(4);
    cout<<endl;
    l->print();

    l->delNode(7);
    cout<<endl;
    l->print();

    return 0;
}
