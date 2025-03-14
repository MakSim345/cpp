#ifndef _TRACE_LOGGER_H_
#define _TRACE_LOGGER_H_

#include "gen.h"

class TraceLogger
{
public:
    TraceLogger (const char* fileName, const char* funcName, int lineNumber);
    ~TraceLogger();

private:
    static std::string Indent;
    const char* _fileName;
    const char* _funcName;
};

#ifdef DEBUG
    #define LOG_TRACE TraceLogger traceLogger(__FILE__, __FUNCTION__, __LINE__);
#else
    #define LOG_TRACE
#endif

#endif
