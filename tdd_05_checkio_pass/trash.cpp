/*
 *
void helper_foo()
    {
        int n = 0;
        int j = 0;
        int try_conter = 0;
        bool done = false;
        srand(time(0));
        n = rand() % max_num;
        std::cout << "I have a number up to " << max_num;
        std::cout << ". Guess what is it?\n";
        do
        {
        try_conter ++;
        std::cout << "Attempt number: " << try_conter << "\n";
        std::cin >> j;
        if (n >j)
            {
            std::cout << "Mine is bigger.\n";
            }
        else
            {
            if (n < j)
                std::cout << "Mine is less.\n";
            else
            {
                std::cout << "You WIN! ";
                std::cout << try_conter << " attempts were used.\n";
                done = true;
            }
            }
        } while(!done);
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
    void testPatientOutput()
    {
        Patient * _my_patient = new Patient("John", "bed1");
        TS_ASSERT_EQUALS("Patient 'John' is in 'bed1' and he is still alive", _my_patient->toString());
    }

    void testPatientInvalidLocation()
    {
        TS_ASSERT_THROWS(Patient mp("Erkki", "invalid place"), InvalidLocation);
    }

    void testPatientMock()
    {
        // TS_FAIL("Test not implemented\n");
    }

    void testPatientAlive()
    {
        Patient * _my_patient = new Patient("Alive", "bed9");
        TS_ASSERT(_my_patient->isAlive());
    }
    */


class PlaneTestSuite : public CxxTest::TestSuite
{
public:
    void testPlane()
    {
        // Airplane airplane;
        CropperPlane plane;
    }
};



class AirplaneTestSuite : public CxxTest::TestSuite
{
public:
    void TestAirplaneConstruction()
    {
        // 100 - number of seats; 500.0 fuel tank capacity
        Airplane airplane(201, 500.0);
        TS_ASSERT_EQUALS(airplane.getFuel(), 0);
        TS_ASSERT_EQUALS(airplane.getNumberOfPassengers(), 0);
        TS_ASSERT_EQUALS(airplane.getNumberOfSeats(), 100);
        TS_ASSERT_EQUALS(airplane.getNumberOfPilots(), 0);
        TS_ASSERT_EQUALS(airplane.getNumberOfStewardess(), 0);
        TS_ASSERT_EQUALS(airplane.getFuelTankCapacity(), 500.0);
        
        for (size_t seats = 0; seats <= 300; ++seats)
        {
            if ((seats >= 10) && (seats <= 200))
            {
                TS_ASSERT_THROWS_NOTHING(Airplane plane(seats, 500));
            }
            else
            {
                TS_ASSERT_THROWS(Airplane plane(seats, 500), std::invalid_argument);
            }
        }

        // 50 - number of seats
        Airplane airplane1(50, 100.0);
        TS_ASSERT_EQUALS(airplane1.getNumberOfSeats(), 50);
        TS_ASSERT_EQUALS(airplane1.getFuelTankCapacity(), 100.0);
        
    }

    void TestAirplaneRefuel()
    {
        // 100 - number of seats; 500.0 fuel tank capacity
        Airplane airplane(100, 500.0);        
        TS_ASSERT_EQUALS (airplane.getFuel(), 0);
        airplane.reFuel(100.0);
        TS_ASSERT_EQUALS (airplane.getFuel(), 100.0);
        airplane.reFuel(200.0);
        TS_ASSERT_EQUALS (airplane.getFuel(), 200.0 + 100.0);
        // test fuel overflow:
        airplane.reFuel(300.0);
        TS_ASSERT_EQUALS (airplane.getFuel(), airplane.getFuelTankCapacity() );    
    }
};
   
