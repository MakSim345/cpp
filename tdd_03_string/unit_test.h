#include <cxxtest/TestSuite.h>

#include "parser.h"

class ParserTestSuite : public CxxTest::TestSuite
{
public:
    void testParserConstructor()
    {
        Parser _my_parser;
    }

    void testStrip()
    {
        string s = " strip me  ";
        Parser _my_parser;
        _my_parser.strip(s);
        TS_ASSERT_EQUALS(s, "strip me");
    }

    void testNoStrip()
    {
        string s = "don't strip me";
        string s1 = s;
        Parser _my_parser;
        _my_parser.strip(s);
        TS_ASSERT_EQUALS(s, s1);
    }

    void testStripLeft()
    {
        string s = " left strip me";
        Parser _my_parser;
        _my_parser.strip(s);
        TS_ASSERT_EQUALS(s, "left strip me");
    }

    void testStripRight()
    {
        string s = "right strip me ";
        Parser _my_parser;
        _my_parser.strip(s);
        TS_ASSERT_EQUALS(s, "right strip me");
    }

    void testSurroundedBy()
    {
        const string s = "?am I surrounded by question marks?";
        Parser _my_parser;        
        TS_ASSERT(_my_parser.surrounded_by(s, '?', '?'));
    }

    void testNotSurroundedBy()
    {
        const string s = "I'm the authority";
        Parser _my_parser;        
        TS_ASSERT(!_my_parser.surrounded_by(s, ' ', ' '));
    }

    void testLeftOnlySurroundedBy()
    {
        const string s = "?Left yes but right no.";
        Parser _my_parser;        
        TS_ASSERT(!_my_parser.surrounded_by(s, '?', '!'));
    }

    void testRightOnlySurroundedBy()
    {
        const string s = "Left no but right yes!";
        Parser _my_parser;        
        TS_ASSERT(!_my_parser.surrounded_by(s, '?', '!'));
    }

    void testNotSurroundedByNullChar()
    {
        const string s = "Am I terminated by a null char? Are we all?";
        Parser _my_parser;        
        TS_ASSERT(!_my_parser.surrounded_by(s, 'A', 0));
    }

};
 
