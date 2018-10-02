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
#include "tdd_start.h"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "tdd_start.h", 5, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testAddition() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 8, "testAddition" ) {}
 void runTest() { suite_MyTestSuite.testAddition(); }
} testDescription_MyTestSuite_testAddition;

static class TestDescription_MyTestSuite_testMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testMultiplication() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 14, "testMultiplication" ) {}
 void runTest() { suite_MyTestSuite.testMultiplication(); }
} testDescription_MyTestSuite_testMultiplication;

static class TestDescription_MyTestSuite_TestMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_TestMultiplication() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 19, "TestMultiplication" ) {}
 void runTest() { suite_MyTestSuite.TestMultiplication(); }
} testDescription_MyTestSuite_TestMultiplication;

static class TestDescription_MyTestSuite_testComparison : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testComparison() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 26, "testComparison" ) {}
 void runTest() { suite_MyTestSuite.testComparison(); }
} testDescription_MyTestSuite_testComparison;

static class TestDescription_MyTestSuite_testEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testEquality() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 32, "testEquality" ) {}
 void runTest() { suite_MyTestSuite.testEquality(); }
} testDescription_MyTestSuite_testEquality;

#include <cxxtest/Root.cpp>
