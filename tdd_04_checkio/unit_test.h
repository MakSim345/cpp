#include <cxxtest/TestSuite.h>

#include "parser.h"

class ParserTestSuite : public CxxTest::TestSuite
{
public:

    void testStart()
    {
        cout << "\n";
    }

    void testArrayType()
    {
        // assert isinstance(checkio([1]), list), "The result must be a list"
        vector <int> viNumbers;
        checkio _obj = checkio();
        
        int _my_max = 100;
        _obj.set_max(_my_max);
        
        TS_ASSERT_EQUALS(typeid(viNumbers).name(), typeid(_obj.run(viNumbers)).name() );

    }

    void testArrayMax()
    {
        // assert isinstance(checkio([1]), list), "The result must be a list"        
        checkio _obj = checkio();
        
        int _my_max = 100;
        int _my_max_bad = 10;
        _obj.set_max(_my_max);
        TS_ASSERT_EQUALS( _my_max, _obj.get_max() );
       
    }
    
    void testArray1stExample()
    {
        // assert checkio([1, 2, 3, 1, 3]) == [1, 3, 1, 3], "1st example"
        int _my_max = 5;
        checkio _obj = checkio(_my_max);
        vector <int> viNum;
        viNum.push_back(1);
        viNum.push_back(2);
        viNum.push_back(3);
        viNum.push_back(1);
        viNum.push_back(3);

        vector <int> viEtalon;
        viEtalon.push_back(1);
        viEtalon.push_back(3);
        viEtalon.push_back(1);
        viEtalon.push_back(3);

        
        TS_ASSERT_EQUALS( viEtalon, _obj.run(viNum) );
    }

    void testArray2ndExample()
    {
        // assert checkio([1, 2, 3, 4, 5]) == [], "2nd example"
        int _my_max = 5;
        checkio _obj = checkio(_my_max);
        vector <int> viNum;
        viNum.push_back(1);
        viNum.push_back(2);
        viNum.push_back(3);
        viNum.push_back(4);
        viNum.push_back(5);

        vector <int> viEtalon;
        
        TS_ASSERT_EQUALS( viEtalon, _obj.run(viNum) );
    }

    void testArray3ndExample()
    {
        // assert checkio([5, 5, 5, 5, 5]) == [5, 5, 5, 5, 5], "3rd example"
        int _my_max = 5;
        checkio _obj = checkio(_my_max);
        vector <int> viNum;
        viNum.push_back(5);
        viNum.push_back(5);
        viNum.push_back(5);
        viNum.push_back(5);
        viNum.push_back(5);

        vector <int> viEtalon;
        viEtalon.push_back(5);
        viEtalon.push_back(5);
        viEtalon.push_back(5);
        viEtalon.push_back(5);
        viEtalon.push_back(5);
        
        TS_ASSERT_EQUALS( viEtalon, _obj.run(viNum) );
    }

    void testArray4thExample()
    {
        // assert checkio([10, 9, 10, 10, 9, 8]) == [10, 9, 10, 10, 9], "4th example"
        int _my_max = 6;
        checkio _obj = checkio(_my_max);
        vector <int> viNum;
        viNum.push_back(10);
        viNum.push_back(9);
        viNum.push_back(10);
        viNum.push_back(10);
        viNum.push_back(9);
        viNum.push_back(8);

        vector <int> viEtalon;
        viEtalon.push_back(10);
        viEtalon.push_back(9);
        viEtalon.push_back(10);
        viEtalon.push_back(10);
        viEtalon.push_back(9);
        
        TS_ASSERT_EQUALS( viEtalon, _obj.run(viNum) );
    }
    /*
     *
    +assert isinstance(checkio([1]), list), "The result must be a list"
    +assert checkio([1, 2, 3, 1, 3]) == [1, 3, 1, 3], "1st example"
    +assert checkio([1, 2, 3, 4, 5]) == [], "2nd example"
    +assert checkio([5, 5, 5, 5, 5]) == [5, 5, 5, 5, 5], "3rd example"
    +assert checkio([10, 9, 10, 10, 9, 8]) == [10, 9, 10, 10, 9], "4th example"
     
     */

};
 
