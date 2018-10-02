#include "node_if.h"
#include "iostream"
using std::cout;
using std::cin;
using std::endl;

template <class T>
class list
{

private:
    node<T>* root;
    long int ll_index_count; 

public:
    list()
    {
        root = new node<T>;;
        ll_index_count = 0;
    }

    void insert(node<T>* newNode)
    {
        newNode->next = this->root;
        this->root = newNode;
        ll_index_count++;
    }
    
    void insertAfter(node<T>* newNode, long int count)
    {
        if(count==ll_index_count)
        {
            this->insert(newNode);
            return;
        }
        else
        {

            node<T>* prev = new node<T>;
            prev = root;
            long int intCount=1;

            node<T>* temp = new node<T>;
            temp = prev->next;
    
            while(intCount!=ll_index_count-count)
            {
                temp = temp->next;
                prev = prev->next;
                intCount++;
    
            }
            prev->next = newNode;
            newNode->next = temp;
            delete prev;
            delete temp;

        }
        ll_index_count++;
    }
    
    void insertBefore(node<T>* newNode, long int count)
    {
        node<T>* prev = new node<T>;
        prev = root;
        long int intCount=0;

        node<T>* temp = new node<T>;
        temp = prev->next;

        while(intCount!=ll_index_count-count)
        {
            temp = temp->next;
            prev = prev->next;
            intCount++;

        }
        prev->next = newNode;
        newNode->next = temp;
        //delete prev;  Not working for some reason. Causes the data of some node become 0.  TODO
        delete temp;
        ll_index_count++;

    }
    
    void delNode(T num)
    {
        node<T>* temp = new node<int>;
        temp = root->next;

        node<T>* prev = new node<T>;
        prev = root;
        while(temp->next!=NULL)
        {
            if(prev->data==num)
            {
                root = temp;
                delete prev;
                continue;
            }
            else if(temp->data==num)
            {
                prev->next = temp->next;
            }
        
            prev = prev->next;
            temp = temp->next;
        }
        ll_index_count--;
    }
    
    void delAtLoc(int count)
    {
        node<T>* temp = new node<int>;
        temp = root->next;

        node<T>* prev = new node<T>;
        prev = root;
        long int intCount=1;
    
        if(count==ll_index_count)
        {
            root = root->next;
        }
        else
        {
            
            while(intCount!=ll_index_count-count)
            {
                prev = prev->next;
                temp = temp->next;
                intCount++;
            }
        }
        prev->next = temp->next;
        ll_index_count--;
    }

    list<T>* search(list<T>* src)
    {
        list<T>* l = new list<T>;
    }

    void print()
    {
        node<T>* temp = this->root;
        while(temp->next!=NULL)
        {
            cout<<temp->data<<endl;
            temp = temp->next;

        }
    }
};
