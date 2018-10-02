/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "unit_test.h"

static PatientTestSuite suite_PatientTestSuite;

static CxxTest::List Tests_PatientTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PatientTestSuite( "unit_test.h", 6, "PatientTestSuite", suite_PatientTestSuite, Tests_PatientTestSuite );

static class TestDescription_PatientTestSuite_testPatientConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_PatientTestSuite_testPatientConstructor() : CxxTest::RealTestDescription( Tests_PatientTestSuite, suiteDescription_PatientTestSuite, 9, "testPatientConstructor" ) {}
 void runTest() { suite_PatientTestSuite.testPatientConstructor(); }
} testDescription_PatientTestSuite_testPatientConstructor;

static class TestDescription_PatientTestSuite_testPatientOutput : public CxxTest::RealTestDescription {
public:
 TestDescription_PatientTestSuite_testPatientOutput() : CxxTest::RealTestDescription( Tests_PatientTestSuite, suiteDescription_PatientTestSuite, 16, "testPatientOutput" ) {}
 void runTest() { suite_PatientTestSuite.testPatientOutput(); }
} testDescription_PatientTestSuite_testPatientOutput;

static class TestDescription_PatientTestSuite_testPatientInvalidLocation : public CxxTest::RealTestDescription {
public:
 TestDescription_PatientTestSuite_testPatientInvalidLocation() : CxxTest::RealTestDescription( Tests_PatientTestSuite, suiteDescription_PatientTestSuite, 22, "testPatientInvalidLocation" ) {}
 void runTest() { suite_PatientTestSuite.testPatientInvalidLocation(); }
} testDescription_PatientTestSuite_testPatientInvalidLocation;

static class TestDescription_PatientTestSuite_testPatientMock : public CxxTest::RealTestDescription {
public:
 TestDescription_PatientTestSuite_testPatientMock() : CxxTest::RealTestDescription( Tests_PatientTestSuite, suiteDescription_PatientTestSuite, 27, "testPatientMock" ) {}
 void runTest() { suite_PatientTestSuite.testPatientMock(); }
} testDescription_PatientTestSuite_testPatientMock;

static class TestDescription_PatientTestSuite_testPatientAlive : public CxxTest::RealTestDescription {
public:
 TestDescription_PatientTestSuite_testPatientAlive() : CxxTest::RealTestDescription( Tests_PatientTestSuite, suiteDescription_PatientTestSuite, 32, "testPatientAlive" ) {}
 void runTest() { suite_PatientTestSuite.testPatientAlive(); }
} testDescription_PatientTestSuite_testPatientAlive;

#include <cxxtest/Root.cpp>
