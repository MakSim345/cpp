#ifndef LOGGER_H
#define LOGGER_H

#include <Logger/LoggerExport.h>

#include <string>
#include <sstream>
#include <map>

/*
Reminder
See http://msdn.microsoft.com/en-us/library/b0084kay.aspx
__FILE__ : file source name
__LINE__ : line number inside the source file
__DATE__ : compilation date
__TIME__ : compilation time
__FUNCTION__ : function name
__PRETTY_FUNCTION__ : function name
*/

#ifdef __GNUC__
    #define __FUNCTION__ __PRETTY_FUNCTION__
#endif

/** Macros for the Logger class. */
#define addBrackets(text) "[" + std::ostringstream(text).str() + "]"
#define logDebug() Logger(Logger::Debug) << "[DEBUG]" << addBrackets(__FUNCTION__)
#define logInfo() Logger(Logger::Info) << "[INFO]" << addBrackets(__FUNCTION__)
#define logWarning() Logger(Logger::Warning) << "[WARNING]" << addBrackets(__FUNCTION__)
#define logCritical() Logger(Logger::Critical) << "[CRITICAL]" << addBrackets(__FUNCTION__)
#define logFatal() Logger(Logger::Fatal) << "[FATAL]" << addBrackets(__FUNCTION__) << addBrackets(__FILE__)

/**
 * Logs a given message.
 *
 * 1 message = 1 instance of class Logger.
 *
 * Warning: this class is not thread-safe, does not use mutex.
 *
 * You should use the macros defined above, example:
 * @code
 * logDebug() << "Hello" << "world!";
 * logFatal() << "Fatal error" << "will do an assert";
 * @endcode
 *
 * @see http://developer.qt.nokia.com/doc/qt-4.8/qdebug.html
 * @author Tanguy Krotoff
 */
class Logger {
public:

    /**
     * Level of the log message.
     */
    enum Level {
        Debug,
        Info,
        Warning,
        Critical,
        Fatal
    };

    /**
     * Enables/disables the output for each log level.
     *
     * By default:
     * Debug messages go to std::cout if compiled in DEBUG mode; no output if compiled in RELEASE mode.
     * Info messages go to std::cout
     * Warning and Critical messages go to std::cerr
     * Fatal messages always assert after a std::cerr, they cannot be disabled
     *
     * @param level log level to configure
     * @param enable if true will output all log messages of the given level; if false the given log level outputs nothing
     */
    LOGGER_API static void enableLogLevel(Level level, bool enable);

    /** Checks if a given log level is enabled or not. */
    LOGGER_API static bool isLogLevelEnabled(Level level);

    LOGGER_API Logger(Level level);

    LOGGER_API ~Logger();

    /**
     * Adds a "value" (string, int, whatever...) to the log message.
     *
     * Accepts just about anything: based on std::ostringstream.
     * Adds a space after every "value" added like does QDebug from Qt.
     *
     * @param t whatever value
     */
    template<typename T> Logger & operator<<(const T & t) {
        _stream << t;
        return space();
    }

    /**
     * Internal function, do not use.
     *
     * @see enableLogLevel()
     * @return the boolean is just a hack for the initialization,
     *         see LOGGER_INITOUTPUTLIST inside Logger.cpp
     */
    static bool initOutputList();

private:

    LOGGER_API Logger & space();

    /** @see enableLogLevel() */
    static std::map<Level, bool> _outputList;

    Level _level;

    std::ostringstream _stream;
};

#endif  //LOGGER_H
