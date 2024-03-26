// main.cpp : Defines the entry point for the console application.
//
// #include "stdafx.h"
#include "gen.h"


class DataBaseConnect
{
public:
    virtual bool login (string username, string password) {return true;}
    virtual bool logout (string username) {return true;}
    virtual int fetchRecord()  {return -1;}
};

class MyDataBase
{
    DataBaseConnect& dbC;
public:
    MyDataBase (DataBaseConnect& _dbC) : dbC(_dbC) {}

    int mdbInit (string username, string password)
    {
        if (dbC.login(username, password) != true) {
            cout<<"DB FAILURE"<<endl;
            return -1;
        } else {
            cout<<"DB SUCCESS"<<endl;
            return 1;
        }
    }
};

class Stack
{
    vector<int> vstack;
public:
    void push(int pValue)
    {
        vstack.push_back(pValue);
    }
    int pop()
    {
        if (vstack.size() > 0)
        {
            int retValue = vstack.back();
            vstack.pop_back();
            return retValue;
        }
        else
        {
            return -1;
        }
    }
    int size() {return vstack.size();}
};

enum Numbers
{
    ONE=1,
    TWO,
    THREE
};

const char* NumbersToString(int pNumberToConvert)
{
    switch (pNumberToConvert)
    {
        case ONE:
            return "one";
        case TWO:
            return "two";
        case THREE:
            return "three";
        default:
            return "Nan";
    }
}

TEST(BasicTest, NumberCompare)
{
    EXPECT_EQ(1, ONE);
    EXPECT_GT(TWO, ONE);
}

TEST(BasicTest, ToString)
{
    EXPECT_STREQ("one", NumbersToString(1));
    EXPECT_STRCASEEQ("TWO", NumbersToString(2));
    //EXPECT_STREQ("zero", NumbersToString(0));
    EXPECT_STREQ("Nan", NumbersToString(-9));
}
//===============================================

struct stackTest: public testing::Test
{
    Stack st;
    void SetUp()
    {
        int value[] = {1,2,3,4,5,6,7,8,9};
        const int arr_size = sizeof(value)/sizeof(int);
        // for (auto &val : value)
        for (int i = 0; i < arr_size; i++)
        {
            st.push(value[i]);
        }
    }

    void TearDown () {}
};

TEST_F (stackTest, popTest)
{
    int lastPoppedValue = 9;
    while (lastPoppedValue != 1)
    {
        ASSERT_EQ(st.pop(), lastPoppedValue--);
    }
}

TEST_F (stackTest, sizeValidatedTest)
{
    // check that popped value is NOT "-1"
    int val = st.size();
    for (val; val > 0; val--)
    {
        ASSERT_NE(st.pop(), -1);
    }
}

TEST(StackTest, DISABLED_testPop)
{
    Stack st;
    st.push(9);
    EXPECT_EQ(9, st.pop());
}

TEST(StackTest, testAll)
{
    Stack st;
    st.push(9);
    st.push(28);
    int val = st.pop();

    EXPECT_EQ(28, val);
    EXPECT_NE(0, val); // Expect val not to be 0
    EXPECT_GT(29, val); // Greater than
    EXPECT_LE(27, val); // Less or equal than
}

int main(int argc, char** argv)
{
    int returnValue = 0;

    testing::InitGoogleTest(&argc, argv);
    returnValue = RUN_ALL_TESTS();

    printf ("Application complete.\n");
    system ("PAUSE");

    return returnValue;
}
