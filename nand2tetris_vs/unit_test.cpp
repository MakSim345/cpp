/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "unit_test.h"

static NOTTestSuite suite_NOTTestSuite;

static CxxTest::List Tests_NOTTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NOTTestSuite( "unit_test.h", 6, "NOTTestSuite", suite_NOTTestSuite, Tests_NOTTestSuite );

static class TestDescription_NOTTestSuite_testNOTConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_NOTTestSuite_testNOTConstructor() : CxxTest::RealTestDescription( Tests_NOTTestSuite, suiteDescription_NOTTestSuite, 10, "testNOTConstructor" ) {}
 void runTest() { suite_NOTTestSuite.testNOTConstructor(); }
} testDescription_NOTTestSuite_testNOTConstructor;

static class TestDescription_NOTTestSuite_testNOTOutput : public CxxTest::RealTestDescription {
public:
 TestDescription_NOTTestSuite_testNOTOutput() : CxxTest::RealTestDescription( Tests_NOTTestSuite, suiteDescription_NOTTestSuite, 17, "testNOTOutput" ) {}
 void runTest() { suite_NOTTestSuite.testNOTOutput(); }
} testDescription_NOTTestSuite_testNOTOutput;

static NANDTestSuite suite_NANDTestSuite;

static CxxTest::List Tests_NANDTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_NANDTestSuite( "unit_test.h", 35, "NANDTestSuite", suite_NANDTestSuite, Tests_NANDTestSuite );

static class TestDescription_NANDTestSuite_testNANDConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_NANDTestSuite_testNANDConstructor() : CxxTest::RealTestDescription( Tests_NANDTestSuite, suiteDescription_NANDTestSuite, 39, "testNANDConstructor" ) {}
 void runTest() { suite_NANDTestSuite.testNANDConstructor(); }
} testDescription_NANDTestSuite_testNANDConstructor;

static class TestDescription_NANDTestSuite_testNANDOutput : public CxxTest::RealTestDescription {
public:
 TestDescription_NANDTestSuite_testNANDOutput() : CxxTest::RealTestDescription( Tests_NANDTestSuite, suiteDescription_NANDTestSuite, 47, "testNANDOutput" ) {}
 void runTest() { suite_NANDTestSuite.testNANDOutput(); }
} testDescription_NANDTestSuite_testNANDOutput;

#include <cxxtest/Root.cpp>
