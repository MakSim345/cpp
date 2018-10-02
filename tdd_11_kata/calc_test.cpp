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
#include "calc_test.h"

static CalcTestSuite suite_CalcTestSuite;

static CxxTest::List Tests_CalcTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CalcTestSuite( "calc_test.h", 26, "CalcTestSuite", suite_CalcTestSuite, Tests_CalcTestSuite );

static class TestDescription_CalcTestSuite_test_add_emptyString_returns0 : public CxxTest::RealTestDescription {
public:
 TestDescription_CalcTestSuite_test_add_emptyString_returns0() : CxxTest::RealTestDescription( Tests_CalcTestSuite, suiteDescription_CalcTestSuite, 30, "test_add_emptyString_returns0" ) {}
 void runTest() { suite_CalcTestSuite.test_add_emptyString_returns0(); }
} testDescription_CalcTestSuite_test_add_emptyString_returns0;

static class TestDescription_CalcTestSuite_test_add_oneNumberString_returns1 : public CxxTest::RealTestDescription {
public:
 TestDescription_CalcTestSuite_test_add_oneNumberString_returns1() : CxxTest::RealTestDescription( Tests_CalcTestSuite, suiteDescription_CalcTestSuite, 36, "test_add_oneNumberString_returns1" ) {}
 void runTest() { suite_CalcTestSuite.test_add_oneNumberString_returns1(); }
} testDescription_CalcTestSuite_test_add_oneNumberString_returns1;

static class TestDescription_CalcTestSuite_test_add_twoNumberString_returns2 : public CxxTest::RealTestDescription {
public:
 TestDescription_CalcTestSuite_test_add_twoNumberString_returns2() : CxxTest::RealTestDescription( Tests_CalcTestSuite, suiteDescription_CalcTestSuite, 42, "test_add_twoNumberString_returns2" ) {}
 void runTest() { suite_CalcTestSuite.test_add_twoNumberString_returns2(); }
} testDescription_CalcTestSuite_test_add_twoNumberString_returns2;

static class TestDescription_CalcTestSuite_test_add_threeNumberString_returns3 : public CxxTest::RealTestDescription {
public:
 TestDescription_CalcTestSuite_test_add_threeNumberString_returns3() : CxxTest::RealTestDescription( Tests_CalcTestSuite, suiteDescription_CalcTestSuite, 48, "test_add_threeNumberString_returns3" ) {}
 void runTest() { suite_CalcTestSuite.test_add_threeNumberString_returns3(); }
} testDescription_CalcTestSuite_test_add_threeNumberString_returns3;

static class TestDescription_CalcTestSuite_test_add_fiveNumberString_returns5 : public CxxTest::RealTestDescription {
public:
 TestDescription_CalcTestSuite_test_add_fiveNumberString_returns5() : CxxTest::RealTestDescription( Tests_CalcTestSuite, suiteDescription_CalcTestSuite, 53, "test_add_fiveNumberString_returns5" ) {}
 void runTest() { suite_CalcTestSuite.test_add_fiveNumberString_returns5(); }
} testDescription_CalcTestSuite_test_add_fiveNumberString_returns5;

static class TestDescription_CalcTestSuite_test_add_newLineDelimTwoNumberString_returns2 : public CxxTest::RealTestDescription {
public:
 TestDescription_CalcTestSuite_test_add_newLineDelimTwoNumberString_returns2() : CxxTest::RealTestDescription( Tests_CalcTestSuite, suiteDescription_CalcTestSuite, 59, "test_add_newLineDelimTwoNumberString_returns2" ) {}
 void runTest() { suite_CalcTestSuite.test_add_newLineDelimTwoNumberString_returns2(); }
} testDescription_CalcTestSuite_test_add_newLineDelimTwoNumberString_returns2;

#include <cxxtest/Root.cpp>
