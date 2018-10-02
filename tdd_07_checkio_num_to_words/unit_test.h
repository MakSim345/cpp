#include <cxxtest/TestSuite.h>

#include "parser.h"

class ParserTestSuite : public CxxTest::TestSuite
{
public:
    /*
     *
    +assert checkio(4) == 'four'
    +assert checkio(133) == 'one hundred thirty three'
    +assert checkio(12) == 'twelve'
    +assert checkio(101) == 'one hundred one'
    +assert checkio(212) == 'two hundred twelve'
    +assert checkio(40) == 'forty'
    +assert not checkio(212).endswith(' '), "Don't forget strip whitespaces at the end of string"
     * 
     */
    void testStart()
    {
        cout << "\n";
    }        

    void testPass1stExample()
    {
        // assert checkio(4) == 'four'
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_num(4), "four");
    }
    
    void testPass2ndExample()
    {        
        // assert checkio(133) == 'one hundred thirty three'
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_num(133), "one hundred thirty three");
    }

    void testPass3dExample()
    {
        // assert checkio(12) == 'twelve'
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_num(12), "twelve");
    }
    
    void testPass4thExample()
    {
        // assert checkio(40) == 'forty'
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_num(40), "forty");
    }
    
    void testPass5thExample()
    {
        // assert checkio(101) == 'one hundred one'
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_num(101), "one hundred one");
    }

    void testPass6thExample()
    {
        // assert checkio(212) == 'two hundred twelve'
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_num(212), "two hundred twelve");
    }
    
    void testPass7thExample()
    {
        // assert not checkio(212).endswith(' '), "Don't forget strip whitespaces at the end of string"
        checkio _obj = checkio();
        TS_ASSERT_DIFFERS(*_obj.set_num(212).rbegin(), ' ');
    }
    

};
 
