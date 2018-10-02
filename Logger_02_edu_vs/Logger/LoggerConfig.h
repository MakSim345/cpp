#ifndef LOGGERCONFIG_H
#define LOGGERCONFIG_H

#include <Logger/LoggerExport.h>

#include <string>

/**
 * Reads Logger configuration.
 *
 * The configuration file follows the INI format.
 * Format:
 * <pre>
 * LoggingLevel = All
 * </pre>
 *
 * LoggingLevel can take the following values:
 * - All
 * - Off
 * - Debug
 * - Info
 * - Warning
 * - Critical
 *
 * Example: <pre>LoggingLevel = Info</pre>
 * This will limit the messages that are printed on the console to Logger::Info and above.
 *
 * @see http://en.wikipedia.org/wiki/INI_file
 * @author Tanguy Krotoff
 */
class LOGGER_API LoggerConfig {
public:

    /**
     * Reads the configuration file name and sets the Logger settings accordingly.
     *
     * @param file configuration file name (full path)
     * @return true if the config was read; false otherwise
     */
    static bool readConfig(const std::string & file);

    /** Reads the configuration from a stream. */
    static bool readConfig(std::stringstream & stream);

private:

    LoggerConfig();

    ~LoggerConfig();
};

#endif  //LOGGERCONFIG_H
