#ifndef GenieUsabilityLogger_H
#define GenieUsabilityLogger_H

//#include <QString>
//#include <QTime>
#include <fstream>
#include <iostream>
#include <istream>
//#include <GEng.h>

class GenieUsabilityLogger
{
public:
    GenieUsabilityLogger(void);
    ~GenieUsabilityLogger(void);

    bool OpenLogFile(std::string  name);
    void CloseLogFile();
    void Log(std::string  name, std::string  value, std::string  status);
    //void LogPanicStarted(int seconds);
    //void LogPanicAdjusted(int seconds);
    //void LogTimeOut();

private:

    bool FileExists(std::string  filename);
    void OpenLog(std::string  filename);
    //QString mfilename;
    // QTime * mLogTime;
    std::ofstream mOut;
};

#endif // GenieUsabilityLogger_H
