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

static ParserTestSuite suite_ParserTestSuite;

static CxxTest::List Tests_ParserTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ParserTestSuite( "unit_test.h", 5, "ParserTestSuite", suite_ParserTestSuite, Tests_ParserTestSuite );

static class TestDescription_ParserTestSuite_testStart : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testStart() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 18, "testStart" ) {}
 void runTest() { suite_ParserTestSuite.testStart(); }
} testDescription_ParserTestSuite_testStart;

static class TestDescription_ParserTestSuite_testPass1stExample : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testPass1stExample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 23, "testPass1stExample" ) {}
 void runTest() { suite_ParserTestSuite.testPass1stExample(); }
} testDescription_ParserTestSuite_testPass1stExample;

static class TestDescription_ParserTestSuite_testPass2ndExample : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testPass2ndExample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 30, "testPass2ndExample" ) {}
 void runTest() { suite_ParserTestSuite.testPass2ndExample(); }
} testDescription_ParserTestSuite_testPass2ndExample;

static class TestDescription_ParserTestSuite_testPass3dExample : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testPass3dExample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 37, "testPass3dExample" ) {}
 void runTest() { suite_ParserTestSuite.testPass3dExample(); }
} testDescription_ParserTestSuite_testPass3dExample;

static class TestDescription_ParserTestSuite_testPass4thExample : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testPass4thExample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 44, "testPass4thExample" ) {}
 void runTest() { suite_ParserTestSuite.testPass4thExample(); }
} testDescription_ParserTestSuite_testPass4thExample;

static class TestDescription_ParserTestSuite_testPass5thExample : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testPass5thExample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 51, "testPass5thExample" ) {}
 void runTest() { suite_ParserTestSuite.testPass5thExample(); }
} testDescription_ParserTestSuite_testPass5thExample;

static class TestDescription_ParserTestSuite_testPass6thExample : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testPass6thExample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 58, "testPass6thExample" ) {}
 void runTest() { suite_ParserTestSuite.testPass6thExample(); }
} testDescription_ParserTestSuite_testPass6thExample;

static class TestDescription_ParserTestSuite_testPass7thExample : public CxxTest::RealTestDescription {
public:
 TestDescription_ParserTestSuite_testPass7thExample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 65, "testPass7thExample" ) {}
 void runTest() { suite_ParserTestSuite.testPass7thExample(); }
} testDescription_ParserTestSuite_testPass7thExample;

#include <cxxtest/Root.cpp>
