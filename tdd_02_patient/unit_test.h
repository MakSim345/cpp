// MyTestSuite1.h
#include <cxxtest/TestSuite.h>

#include "patient.h"

class PatientTestSuite : public CxxTest::TestSuite
{
public:
    void testPatientConstructor()
    {
        Patient * _my_patient = new Patient("John", "bed25");
        TS_ASSERT_EQUALS("John", _my_patient->getName());
        TS_ASSERT_EQUALS("bed25", _my_patient->getLocation());
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
};
 
