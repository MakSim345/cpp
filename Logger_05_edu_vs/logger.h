#ifndef _LOGGER_H_
#define _LOGGER_H_
//============================================================
//
// Copyright (c) 2011 
//
//============================================================
//
// File:           logger.h
// Project:        
//
// Author:         <author> / 
//
//============================================================
// Description:
// <purpose of this file>
//============================================================
#include "gen.h"

#include <string>
#include <fstream>
#include <sstream>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem/path.hpp>

namespace smart_log
{
    typedef void (*ErrorHandler)(const std::string&);
    typedef const std::string (*Obfuscater)(const std::string&);
    //This type provides constant which set the writing log mode. 
    //If a current mode is bigger then methods mode the writing will be ignored.
    //It needs for log flood control
    enum LogLevel{eNormal, eExtended, eDebug};

    struct LogParameters
    {
        std::string m_strLogFileName;
        //Pointer to a function which does appropriate manipulations in case of a log corruption. Set to 0 if it doesn't need.
        ErrorHandler m_pErrorHandler;    
        //Pointer to a function which obfuscates each string writing to a log file. Set to 0 if it doesn't need.
        Obfuscater m_pObfuscater;
        size_t m_uiLogMaxSize;
        unsigned short m_siMaxSavedLogs;
        //Is the thread synchronization needed?
        bool m_bIsMultiThreaded;
        //Indicates whether log will be saved or not. If this flag is set then log will be saved when its size exceed m_uiLogMaxSize.
        //Use m_siMaxSavedLogs to control how many log files will be saved. If the current number of log files has reached the m_siMaxSavedLogs then
        //new saved log would replace the oldest one.
        bool m_bIsSaveLog;
        LogLevel m_xLogLevel;
        //Path to the log location. It will be created if no exists.
        boost::filesystem::path m_xLogSavedPath;
    };

    class Logger
    {
        //---------------------------------------Data
        size_t m_uiCurrentLogSize;
        short int m_siCurrentSavedLogs;
        LogParameters m_xParameters;
        std::ofstream m_xOfstream;
        boost::interprocess::named_mutex m_xMutex;
        //File name with full path in which it will be create
        boost::filesystem::path m_xFullFileName;
        //--------------------------------------Internal methods
    private:
        //Common method for message writing
        void WriteLog(LogLevel xLevel, const std::string& strMessage);
        void HandleLogSizeExcess();
        std::string Timestamp();
        void CreatePath(boost::filesystem::path xPath);
        //--------------------------------------Interface
    public:
        Logger(const LogParameters& xParameters);

        //Set of methods which concretize the common WriteLog method to log levels.
        void WriteNormalLog(const std::ostringstream& strMessage)
        {
            WriteLog( eNormal, strMessage.str() );
        }
        void WriteExtendedLog(const std::ostringstream& strMessage)
        {
            WriteLog( eExtended, strMessage.str() );
        }
        void WriteDebugLog(const std::ostringstream& strMessage)
        {
            WriteLog( eDebug, strMessage.str() );
        }
        //-----------------------------------Setters
        void SetErrorHandler(ErrorHandler pErrorHandler)
        {
            m_xParameters.m_pErrorHandler = pErrorHandler;
        }
        void SetLogMode(LogLevel xLevel)
        {
            m_xParameters.m_xLogLevel = xLevel;
        }
    };
}
#endif//  _LOGGER_

