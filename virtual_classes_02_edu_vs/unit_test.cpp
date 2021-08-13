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

static baseTestSuite suite_baseTestSuite;

static CxxTest::List Tests_baseTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_baseTestSuite( "unit_test.h", 6, "baseTestSuite", suite_baseTestSuite, Tests_baseTestSuite );

static class TestDescription_baseTestSuite_testCreateBase : public CxxTest::RealTestDescription {
public:
 TestDescription_baseTestSuite_testCreateBase() : CxxTest::RealTestDescription( Tests_baseTestSuite, suiteDescription_baseTestSuite, 9, "testCreateBase" ) {}
 void runTest() { suite_baseTestSuite.testCreateBase(); }
} testDescription_baseTestSuite_testCreateBase;

static class TestDescription_baseTestSuite_testCreateDerived : public CxxTest::RealTestDescription {
public:
 TestDescription_baseTestSuite_testCreateDerived() : CxxTest::RealTestDescription( Tests_baseTestSuite, suiteDescription_baseTestSuite, 16, "testCreateDerived" ) {}
 void runTest() { suite_baseTestSuite.testCreateDerived(); }
} testDescription_baseTestSuite_testCreateDerived;

#include <cxxtest/Root.cpp>
