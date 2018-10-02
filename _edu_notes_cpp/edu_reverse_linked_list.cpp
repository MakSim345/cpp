2015-FEB

Technical questions on the interview. Varian Medical oy
- write a Reverse() method for linked list class

//----------------------
void reverselist(void)
{
    if(head==0)
        return;
    if(head->next==0)
        return;
    if(head->next==tail)
    {
        head->next = 0;
        tail->next = head;
    }
    else
    {
        node* pre = head;
        node* cur = head->next;
        node* curnext = cur->next;
        head->next = 0;
        cur->next = head;

        for(; curnext!=0; )
        {
            cur->next = pre;
            pre = cur;
            cur = curnext;
            curnext = curnext->next;
        }
        curnext->next = cur;
    }
}

//----------------------
Node * reverse( Node * ptr )
{
    Node * temp;
    Node * previous = NULL;
    while(ptr != NULL) 
    {
        temp = ptr->next;
        ptr->next = previous;
        previous = ptr;
        ptr = temp;
    }
    return previous;
}

//----------------------
The trick to this algorithm is you need 3 "node_t" pointers to accomplish the reversal.

"next" - Tracks the pointer to the next item in the list.
"head" - Initially contains the original head of the list but will then be set to the pointer to the next item in the list until the NULL pointer is encountered.
"cursor" - Initially is set to NULL but then tracks the new head of the list. At the end of the list, head equals NULL and the value of cursor is returned to the caller.

typedef struct node_t node_t;

struct node_t
{
    int     m_value;
    node_t* m_next;
};

node_t* reverseList(node_t* head)
{
    node_t* cursor = NULL;
    node_t* next;
    while (head)
    {
        next = head->m_next;
        head->m_next = cursor;
        cursor = head;
        head = next;
    }
    return cursor;
}

[Lines 8-9] The reversal step occurs when "head->m_next" is set to the value contained in "cursor" which always contains the pointer to the previous item in the list. 
When the function reaches the end of the list the new head pointer is returned in "cursor".

This one is working for sure:

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


