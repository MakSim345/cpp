#include "LoggerConfig.h"

#include "Logger.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

boost::property_tree::ptree getPropertyTree(std::stringstream & stream) {
    boost::property_tree::ptree ptree;
    try {
        read_ini(stream, ptree);
    } catch (boost::property_tree::ini_parser::ini_parser_error & e) {
        logCritical() << "Parsing failed:" << e.what();
    }
    return ptree;
}

boost::property_tree::ptree getPropertyTree(const std::string & file) {
    boost::property_tree::ptree ptree;
    try {
        read_ini(file, ptree);
    } catch (std::exception & e) {
        logCritical() << "Parsing failed:" << e.what();
    }
    return ptree;
}

void changeLogLevels(Logger::Level limit) {
    for (int i = 0; i < Logger::Fatal; i++) {
        if (i < limit) {
            Logger::enableLogLevel(static_cast<Logger::Level>(i), false);
        } else {
            Logger::enableLogLevel(static_cast<Logger::Level>(i), true);
        }
    }
}

bool parseLevel(const boost::property_tree::ptree & ptree) {
    bool ok = true;

    if (ptree.empty()) {
        ok = false;
    } else {
        std::string level = ptree.get<std::string>("LoggingLevel", "");
        boost::algorithm::to_lower(level);
        if (level.empty()) {
            //No LoggingLevel node
        } else if (level == "off") {
            //Enables all log levels
            changeLogLevels(Logger::Fatal);
        } else if (level == "all") {
            //Disables all log levels (except Fatal)
            changeLogLevels(Logger::Debug);
        }

        else if (level == "debug") {
            changeLogLevels(Logger::Debug);
        } else if (level == "info") {
            changeLogLevels(Logger::Info);
        } else if (level == "warning") {
            changeLogLevels(Logger::Warning);
        } else if (level == "critical") {
            changeLogLevels(Logger::Critical);
        } else if (level == "fatal") {
            logCritical() << "Fatal is an invalid level";
            ok = false;
        }

        else {
            logCritical() << "Unknown level:" << level;
            ok = false;
        }
    }

    return ok;
}

bool LoggerConfig::readConfig(std::stringstream & stream) {
    boost::property_tree::ptree ptree = getPropertyTree(stream);
    return parseLevel(ptree);
}

bool LoggerConfig::readConfig(const std::string & file) {
    boost::property_tree::ptree ptree = getPropertyTree(file);
    return parseLevel(ptree);
}
