#include <Logger/Logger.h>
#include <Logger/LoggerConfig.h>

#define BOOST_TEST_MODULE LoggerTests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestConfigFile) {
    LoggerConfig::readConfig(std::stringstream(""));
    LoggerConfig::readConfig(std::stringstream("No logging level"));
    LoggerConfig::readConfig(std::stringstream("Hello=world"));
#ifdef _DEBUG
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == true);
#else
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == false);
#endif  //_DEBUG
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Info) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Warning) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Critical) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Fatal) == true);
#ifdef _DEBUG
    logDebug() << "Should print";
#else
    logDebug() << "Should not print";
#endif  //_DEBUG
    logInfo() << "Should print";

    LoggerConfig::readConfig(std::stringstream("LoggingLevel = All"));
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Info) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Warning) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Critical) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Fatal) == true);
    logDebug() << "Should print";
    logInfo() << "Should print";

    LoggerConfig::readConfig(std::stringstream("LoggingLevel = Off"));
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Info) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Warning) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Critical) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Fatal) == true);
    logDebug() << "Should not print";
    logInfo() << "Should not print";

    LoggerConfig::readConfig(std::stringstream("LoggingLevel = Debug"));
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Info) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Warning) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Critical) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Fatal) == true);
    logDebug() << "Should print";
    logInfo() << "Should print";

    LoggerConfig::readConfig(std::stringstream("LoggingLevel = Info"));
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Info) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Warning) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Critical) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Fatal) == true);
    logDebug() << "Should not print";
    logInfo() << "Should print";

    LoggerConfig::readConfig(std::stringstream("LoggingLevel = Warning"));
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Info) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Warning) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Critical) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Fatal) == true);
    logDebug() << "Should not print";
    logInfo() << "Should not print";

    LoggerConfig::readConfig(std::stringstream("LoggingLevel = Critical"));
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Debug) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Info) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Warning) == false);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Critical) == true);
    BOOST_CHECK(Logger::isLogLevelEnabled(Logger::Fatal) == true);
    logDebug() << "Should not print";
    logInfo() << "Should not print";
}
