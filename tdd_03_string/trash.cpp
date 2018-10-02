/*
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
   
