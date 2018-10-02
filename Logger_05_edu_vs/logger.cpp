//============================================================
//
// 
//
//============================================================
//
// File:           logger.cpp
// Project:        
//
// Author:         <author> / 
//
//============================================================
// Description:
// <purpose of this file>
//============================================================
#include "logger.h"
#include <ctime>
#include <boost/filesystem/operations.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <set>
#include <algorithm>
#include <windows.h>

namespace fs = boost::filesystem;
namespace multiprocess = boost::interprocess;
using namespace smart_log;

Logger::Logger(const LogParameters& xParameters): 
                m_xParameters(xParameters),
                m_xMutex(multiprocess::open_or_create,
                         (xParameters.m_strLogFileName + std::string("smart_logger_mutex") ).c_str() ),
                m_uiCurrentLogSize(0)
{
    m_xMutex.unlock();
    m_xOfstream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    m_xFullFileName = m_xParameters.m_xLogSavedPath;
    m_xFullFileName /= xParameters.m_strLogFileName;
}

void Logger::WriteLog(LogLevel xLevel, const std::string& strMessage)
try
{
    multiprocess::scoped_lock<boost::interprocess::named_mutex> xLock;
    if(m_xParameters.m_bIsMultiThreaded)
    {
        xLock = multiprocess::scoped_lock<multiprocess::named_mutex>(m_xMutex, multiprocess::defer_lock_type());
        xLock.lock();
    }
    CreatePath(m_xParameters.m_xLogSavedPath);
    
    //Don't do anything if the current log level less then the message demands
    if(xLevel > m_xParameters.m_xLogLevel)
        return;
    if(m_uiCurrentLogSize + strMessage.length() > m_xParameters.m_uiLogMaxSize)
        HandleLogSizeExcess();
    if( !m_xOfstream.is_open() )
        m_xOfstream.open( (m_xFullFileName file_string() + "-" + Timestamp() + ".log").c_str() );
    //Make an output string
    std::ostringstream xStream;
    xStream << "[" << Timestamp() << "]: " << strMessage;
    const std::string& xFinalString = xStream.str();
    if(m_xParameters.m_pObfuscater)
        m_xOfstream << m_xParameters.m_pObfuscater(xFinalString) << std::endl;
    else
        m_xOfstream << xFinalString << std::endl;
    m_uiCurrentLogSize += strMessage.length();
}
catch (std::ofstream::failure xFail)
{
    if(m_xParameters.m_pErrorHandler)
        m_xParameters.m_pErrorHandler("Problem with a file creation or writing to the already existing file.");
    else
        throw;
}

void Logger::HandleLogSizeExcess()
{
    if(m_xOfstream.is_open())
        m_xOfstream.close();
    //Goes through the log directory and finds files which looks like "m_strLogFileName-*Timestamp*"
    fs::directory_iterator xEndIterator;
    std::set<std::string> xFileList;
    for( fs::directory_iterator it(m_xParameters.m_xLogSavedPath); it != xEndIterator; ++it )
    {
        std::string xCurrentFile = it->path().filename();
        if( fs::is_regular_file(it->status()) )
            if(xCurrentFile.find(m_xParameters.m_strLogFileName) != std::string::npos) 
                xFileList.insert(xCurrentFile);
    }
    //If the log files number exceeds the m_siMaxSavedLogs then keep on removing 
    //files until current files number won't be less then threshold
    if(m_xParameters.m_siMaxSavedLogs)
    {
        if(xFileList.size() >= m_xParameters.m_siMaxSavedLogs)
        {
            for(std::set<std::string>::iterator it = xFileList.begin(); it != xFileList.end() 
                && xFileList.size() >= m_xParameters.m_siMaxSavedLogs;)
            {

                fs::remove(fs::path(m_xParameters.m_xLogSavedPath) /= *it);
                xFileList.erase(it++);
            }
        }
    }
    else//Save files property is turned off hence remove all existing log files
    {
        for(std::set<std::string>::iterator it = xFileList.begin(); it != xFileList.end();)
        {
            fs::remove(fs::path(m_xParameters.m_xLogSavedPath) /= *it);
            xFileList.erase(it++);
        }
    }
    m_uiCurrentLogSize = 0;
    //Create a new file
    m_xOfstream.open( (m_xFullFileName.file_string() + "-" + Timestamp() + ".log").c_str() );
}

void Logger::CreatePath(fs::path xPath)
try
{
    //If a directory doesn't exist then try to create full path up to the required directory
    if( !fs::exists(m_xParameters.m_xLogSavedPath) )
    {
        fs::path xTmpPath;
        for(fs::path::iterator xIt = m_xParameters.m_xLogSavedPath.begin(); 
            xIt != m_xParameters.m_xLogSavedPath.end();
            ++xIt)

        {
            xTmpPath /= *xIt;
            if( !fs::exists(xTmpPath) )
                fs::create_directory(xTmpPath);
        }
    }
 
}
catch (fs::basic_filesystem_error<fs::path>)
{ 
    if(m_xParameters.m_pErrorHandler)
        m_xParameters.m_pErrorHandler("Problem with a directory creation");
    else
        throw;
}

std::string Logger::Timestamp()
{
    SYSTEMTIME xTime;
    ::GetSystemTime(&xTime);
    std::ostringstream xStream;
    xStream << xTime.wDay << "." 
            << xTime.wMonth << "."
            << xTime.wYear << "-"
            << xTime.wHour << "."
            << xTime.wMinute << "."
            << xTime.wSecond << "."
            << xTime.wMilliseconds;

    return xStream.str();
}

