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
#include "plane_test.h"

static PlaneTestSuite suite_PlaneTestSuite;

static CxxTest::List Tests_PlaneTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PlaneTestSuite( "plane_test.h", 7, "PlaneTestSuite", suite_PlaneTestSuite, Tests_PlaneTestSuite );

static class TestDescription_PlaneTestSuite_testPlane : public CxxTest::RealTestDescription {
public:
 TestDescription_PlaneTestSuite_testPlane() : CxxTest::RealTestDescription( Tests_PlaneTestSuite, suiteDescription_PlaneTestSuite, 10, "testPlane" ) {}
 void runTest() { suite_PlaneTestSuite.testPlane(); }
} testDescription_PlaneTestSuite_testPlane;

static AirplaneTestSuite suite_AirplaneTestSuite;

static CxxTest::List Tests_AirplaneTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AirplaneTestSuite( "plane_test.h", 17, "AirplaneTestSuite", suite_AirplaneTestSuite, Tests_AirplaneTestSuite );

static class TestDescription_AirplaneTestSuite_TestAirplaneConstruction : public CxxTest::RealTestDescription {
public:
 TestDescription_AirplaneTestSuite_TestAirplaneConstruction() : CxxTest::RealTestDescription( Tests_AirplaneTestSuite, suiteDescription_AirplaneTestSuite, 20, "TestAirplaneConstruction" ) {}
 void runTest() { suite_AirplaneTestSuite.TestAirplaneConstruction(); }
} testDescription_AirplaneTestSuite_TestAirplaneConstruction;

static class TestDescription_AirplaneTestSuite_TestAirplaneSeats : public CxxTest::RealTestDescription {
public:
 TestDescription_AirplaneTestSuite_TestAirplaneSeats() : CxxTest::RealTestDescription( Tests_AirplaneTestSuite, suiteDescription_AirplaneTestSuite, 44, "TestAirplaneSeats" ) {}
 void runTest() { suite_AirplaneTestSuite.TestAirplaneSeats(); }
} testDescription_AirplaneTestSuite_TestAirplaneSeats;

static class TestDescription_AirplaneTestSuite_TestAirplaneRefuel : public CxxTest::RealTestDescription {
public:
 TestDescription_AirplaneTestSuite_TestAirplaneRefuel() : CxxTest::RealTestDescription( Tests_AirplaneTestSuite, suiteDescription_AirplaneTestSuite, 53, "TestAirplaneRefuel" ) {}
 void runTest() { suite_AirplaneTestSuite.TestAirplaneRefuel(); }
} testDescription_AirplaneTestSuite_TestAirplaneRefuel;

#include <cxxtest/Root.cpp>
