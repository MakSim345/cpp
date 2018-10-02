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
#include "my_test.h"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "my_test.h", 10, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testAddition() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 13, "testAddition" ) {}
 void runTest() { suite_MyTestSuite.testAddition(); }
} testDescription_MyTestSuite_testAddition;

static class TestDescription_MyTestSuite_testMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testMultiplication() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 20, "testMultiplication" ) {}
 void runTest() { suite_MyTestSuite.testMultiplication(); }
} testDescription_MyTestSuite_testMultiplication;

static class TestDescription_MyTestSuite_test_a_winner : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_winner() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 26, "test_a_winner" ) {}
 void runTest() { suite_MyTestSuite.test_a_winner(); }
} testDescription_MyTestSuite_test_a_winner;

static class TestDescription_MyTestSuite_test_rabbit_pos : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_rabbit_pos() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 33, "test_rabbit_pos" ) {}
 void runTest() { suite_MyTestSuite.test_rabbit_pos(); }
} testDescription_MyTestSuite_test_rabbit_pos;

static class TestDescription_MyTestSuite_test_super_rabbit_pos : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_super_rabbit_pos() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 53, "test_super_rabbit_pos" ) {}
 void runTest() { suite_MyTestSuite.test_super_rabbit_pos(); }
} testDescription_MyTestSuite_test_super_rabbit_pos;

static class TestDescription_MyTestSuite_test_super_turtle_pos : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_super_turtle_pos() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 73, "test_super_turtle_pos" ) {}
 void runTest() { suite_MyTestSuite.test_super_turtle_pos(); }
} testDescription_MyTestSuite_test_super_turtle_pos;

#include <cxxtest/Root.cpp>
