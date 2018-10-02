#include "Logger.h"

#include <iostream>

#include <cassert>

std::map<Logger::Level, bool> Logger::_outputList;

//Hack: call Logger::initOutputList() when loading this library
static bool LOGGER_INITOUTPUTLIST = Logger::initOutputList();

void Logger::enableLogLevel(Level level, bool enable) {
    initOutputList();

    //Fatal messages are always true, cannot be disabled
    if (level != Fatal) {
        _outputList[level] = enable;
    }
}

bool Logger::isLogLevelEnabled(Level level) {
    return _outputList[level];
}

Logger::Logger(Level level) {
    _level = level;

    //Should have been done when loading the library
    initOutputList();
}

bool Logger::initOutputList() {
    //Lazy initialization
    static bool already = false;

    if (already) {
        //Already initialized
        return true;
    }

#ifdef _DEBUG
    //Debug level output enabled only when compiling in DEBUG mode
    _outputList[Debug] = true;
#else
    _outputList[Debug] = false;
#endif  //_DEBUG

    _outputList[Info] = true;
    _outputList[Warning] = true;
    _outputList[Critical] = true;
    _outputList[Fatal] = true;  //Always true, cannot be disabled

    already = true;

    return true;
}

Logger::~Logger() {
    std::string tmp = _stream.str();

    //Remove the last character of the string: a space added by this class
    size_t lastChar = tmp.length() - 1;
    if (lastChar > 0) {
        tmp.erase(lastChar);
    }
    ///

    //Write to a log file
    //LogFile::instance().writeToLogFile(tmp);

    switch (_level) {

    case Debug:
    case Info:
        if (_outputList[_level]) {
            std::cout << tmp << std::endl;
        }
        break;

    case Warning:
    case Critical:
        if (_outputList[_level]) {
            std::cerr << tmp << std::endl;
        }
        break;

    case Fatal:
        std::cerr << tmp << std::endl;
        assert(NULL && "fatal error");
        break;

    default:
        std::cerr << __FUNCTION__ << " Unknown log level: " << _level << std::endl;
    }
}

Logger & Logger::space() {
    _stream << ' ';
    return *this;
}
