#include "gen.h"
#include "LinkedList.h"

/**
 * Definition for singly-linked list.
 * struct ListNode
 * {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };

 You are given two non-empty linked lists representing two non-negative integers.
 The digits are stored in reverse order and each of their nodes contain a single digit.
 Add the two numbers and return it as a linked list.

 You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 Example:
 Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 Output: 7 -> 0 -> 8
 Explanation: 342 + 465 = 807.
 */

int getRndNumber(int, int);

class Solution
{
public:
    Solution()
    {
        //lnNode = new ListNode();
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        return lnNode;
    }

    ListNode* lnNode;
    ListNode* lnNodePM;

    void createLists()
    {
        int iRnd = getRndNumber(0, 10);
        lnNode = new ListNode(iRnd, NULL);

        ListNode* tmpNode = NULL;

        iRnd = getRndNumber(0, 10);
        tmpNode = new ListNode(iRnd, NULL);
        tmpNode->next = lnNode;
        lnNode = tmpNode;

        iRnd = getRndNumber(0, 10);
        tmpNode = new ListNode(iRnd, NULL);
        tmpNode->next = lnNode;
        lnNode = tmpNode;

        //---------------------------------
        iRnd = getRndNumber(0, 10);
        lnNodePM = new ListNode(iRnd, NULL);

        iRnd = getRndNumber(0, 10);
        addToList(iRnd);
        iRnd = getRndNumber(0, 10);
        addToList(iRnd);

    }

    void addToList(int iValP)
    {
        ListNode* tmpTail = lnNodePM;
        while(tmpTail->next != NULL)
        {
            tmpTail = tmpTail->next;
        }
        tmpTail->next = new ListNode(iValP, NULL);
    }

    void Run()
    {
        this->createLists();
        this->addTwoNumbers(lnNode, lnNodePM);
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
            int i_rnd = getRndNumber();
            L.addNode(i_rnd);
            L2.addNode(i_rnd);
        }
        L.printMe();
        L2.printMe();
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
    std::unique_ptr <App> my_list(new App());
    std::unique_ptr <Solution> mySolution(new Solution());
    try
    {
        long a1 = std::clock();
        std::cout << "Time Start: " << a1 << "\n";

        //my_list->Run();
        mySolution->Run();

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
