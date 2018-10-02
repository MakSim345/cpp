#include <cxxtest/TestSuite.h>

#include "parser.h"

class ParserTestSuite : public CxxTest::TestSuite
{
public:
    /*
     *
    +assert checkio("Hello World!") == "l", "Hello test"
    +assert checkio("How do you do?") == "o", "O is most wanted"
    +assert checkio("One") == "e", "All letter only once."
    +assert checkio("Oops!") == "o", "Don't forget about lower case."
    +assert checkio("AAaooo!!!!") == "a", "Only letters."
    +assert checkio("abe") == "a", "The First."
    +assert checkio("a" * 9000 + "b" * 1000) == "a", "Long."
     */
    void testStart()
    {
        cout << "\n";
    }        

    void testPass1stExample()
    {
        // assert checkio("Hello World!") == "l", "Hello test"
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("Hello World!"), 'l');       
    }
    
    void testPass2ndExample()
    {        
        // assert checkio("How do you do?") == "o", "O is most wanted"
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("How do you do?"), 'o');       
    }

    void testPass3dExample()
    {
        // assert checkio("One") == "e", "All letter only once."
        checkio _obj = checkio();
        TS_ASSERT_EQUALS(_obj.set_pass("One"), 'e');
    }
    
    void testPass4thExample()
    {
        // assert checkio("Oops!") == "o", "Don't forget about lower case."
        checkio _obj = checkio();
        TS_ASSERT_EQUALS(_obj.set_pass("Oops!"), 'o');
    }
    
    void testPass5thExample()
    {
        // assert checkio("AAaooo!!!!") == "a", "Only letters."
        checkio _obj = checkio();
        TS_ASSERT_EQUALS(_obj.set_pass("AAaooo!!!!!!"), 'a');
    }

    void testPass6thExample()
    {
        // assert checkio("abe") == "a", "The First."
        checkio _obj = checkio();
        TS_ASSERT_EQUALS(_obj.set_pass("abe"), 'a');
    }
    
    void testPass7thExample()
    {
        // assert checkio("a" * 9000 + "b" * 1000) == "a", "Long."
        //
        // std::string _big_str;
        std::string _big_str_a(9000, 'a');
        std::string _big_str_b(1000, 'b');
        std::string _big_str = _big_str_a+_big_str_b;
        int i;
        /*
        for (i = 0; i < 9000; i++)
        {
            _big_str[i] = 'a';
            // std::cout << "\nbig string:" << _big_str << "\n";
        }
        // std::cout << "\nbig string:" << _big_str << "\n";
        for (int j = i; j < i+1000; j++)
        {
            _big_str[j] = 'b';
        }
        */
    
        std::cout << "\nbig string:" << _big_str << "\n";
        
        checkio _obj = checkio();
        TS_ASSERT_EQUALS(_obj.set_pass(_big_str), 'a');
        
    }
    

};
 
