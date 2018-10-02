#include <cxxtest/TestSuite.h>

#include "parser.h"

class ParserTestSuite : public CxxTest::TestSuite
{
public:
    /*
     *
    +assert checkio('A1213pokl') == False, "1st example"
    +assert checkio('bAse730onE4') == True, "2nd example"
    +assert checkio('asasasasasasasaas') == False, "3rd example"
    +assert checkio('QWERTYqwerty') == False, "4th example"
    +assert checkio('123456123456') == False, "5th example"
    +assert checkio('QwErTy911poqqqq') == True, "6th example"
    +assert checkio('QWERTY911AA') == False, "7th example"
     
     */
    void testStart()
    {
        cout << "\n";
    }

    void testPass1stExample()
    {
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("A1213pokl"), false);       
    }
    
    void testPass2ndExample()
    {        
        // assert checkio('bAse730onE4') == True, "2nd example"
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("bAse730onE4"), true);       
    }

    void testPass3dExample()
    {
        // assert checkio('asasasasasasasaas') == False, "3rd example"
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("asasasasasasasaas"), false);       
    }

    void testPass4thExample()
    {
        // assert checkio('QWERTYqwerty') == False, "4th example"
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("QWERTYqwerty"), false);       
    }    

    void testPass5thExample()
    {
        // -assert checkio('123456123456') == False, "5th example"
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("123456123456"), false);       
    }

    void testPass6thExample()
    {
        // assert checkio('QwErTy911poqqqq') == True, "6th example"
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("QwErTy911poqqqq"), true);       
    }

    void testPass7thExample()
    {
        // assert checkio('QWERTY911AA') == False, "7th example"        
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("QWERTY911AA"), false);       
    }

    void testPass8thExample()
    {
        // assert checkio('QWERTY911AA') == False, "7th example"        
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("1Aa"), false);       
    }

    void testPass9thExample()
    {
        checkio _obj = checkio();        
        TS_ASSERT_EQUALS(_obj.set_pass("@QwErTy911poq"), false);       
    }
};
 
