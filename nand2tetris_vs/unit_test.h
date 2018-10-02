// MyTestSuite1.h
#include <cxxtest/TestSuite.h>

#include "nand.h"

class NOTTestSuite : public CxxTest::TestSuite
{
public:

    void testNOTConstructor()
    {
        NOT* not = new NOT();
        TS_ASSERT_EQUALS(0, not->in);
        TS_ASSERT_EQUALS(1, not->out);
    }

    void testNOTOutput()
    {
        NOT* not = new NOT();
        printf("\n");
    
        not->in = 0;
        not->run();
        printf("not(%d) out=%d\n", not->in, not->out);
        TS_ASSERT_EQUALS(1, not->out);

        not->in = 1;
        not->run();
        printf("not(%d) out=%d\n", not->in, not->out);
        TS_ASSERT_EQUALS(0, not->out);
   }
};


class NANDTestSuite : public CxxTest::TestSuite
{
public:

    void testNANDConstructor()
    {
        NAND* nand = new NAND();
        TS_ASSERT_EQUALS(0, nand->a);
        TS_ASSERT_EQUALS(0, nand->b);
        TS_ASSERT_EQUALS(1, nand->out);
    }

    void testNANDOutput()
    {
        NAND* nand = new NAND();
        printf("\n");

        nand->a = 0;
        nand->b = 0;
        nand->run();
        printf("%d nand %d = %d\n", nand->a, nand->b, nand->out);
        TS_ASSERT_EQUALS(1, nand->out);

        nand->a = 1;
        nand->b = 0;
        nand->run();
        printf("%d nand %d = %d\n", nand->a, nand->b, nand->out);
        TS_ASSERT_EQUALS(1, nand->out);

        nand->a = 0;
        nand->b = 1;
        nand->run();
        printf("%d nand %d = %d\n", nand->a, nand->b, nand->out);
        TS_ASSERT_EQUALS(1, nand->out);

        nand->a = 1;
        nand->b = 1;
        nand->run();
        printf("%d nand %d = %d\n", nand->a, nand->b, nand->out);
        TS_ASSERT_EQUALS(0, nand->out);
    }

};

