#include "stdafx.h"

// Start - ATL include headers
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlwin.h>
// End - ATL include headers

#include "SaveAppData.h"
#ifdef YS_26JUN2008_TEST_RM

#include "Opsyslib.h"
#include "Localization.h"
#include "SaveAppData.h"

// Values less than this value will have front append _T("0")
const unsigned long APPEND_ZERO_CHECK_VALUE = 10;
// Whiteboard settings file type to search
const TCHAR* WHITEBOARD_SETTINGS_WILDCARD_SEARCH = _T("*.txt");

/****************************************
** Author:      Joe Li
** Purpose:     Constructor
** Comments:  
****************************************/
DOSaveAppData::DOSaveAppData()
{
    m_dateTime = _T("");
}

/****************************************
** Author:      Joe Li
** Purpose:     Destructor
** Comments:  
****************************************/
DOSaveAppData::~DOSaveAppData()
{
}

////////////////////////////////////////
////// ***** PUBLIC METHODS ***** //////
////////////////////////////////////////

/****************************************
** Author:      Joe Li
** Purpose:     Save log data
** Comments:  
****************************************/
bool DOSaveAppData::SaveLogData(const CComBSTR& targetPath, LOG_TYPE logToSave)
{
    if (targetPath.Length() != 0)
        return SaveLog(targetPath, logToSave);

    return false;
}

/****************************************
** Author:      Joe Li
** Purpose:     Save log data
** Comments:  
****************************************/
bool DOSaveAppData::SaveAllLogData(const CComBSTR& targetPath)
{
    if (targetPath.Length() != 0)
    {
        bool allLogsSaved = true;

        // Did not use loop to avoid casting loop index into LOG_TYPE
        allLogsSaved = SaveLog(targetPath, ALARM_LOG) && allLogsSaved;
        allLogsSaved = SaveLog(targetPath, ERROR_LOG) && allLogsSaved;
        allLogsSaved = SaveLog(targetPath, RND_LOG) && allLogsSaved;
        allLogsSaved = SaveLog(targetPath, KEYPRESS_LOG) && allLogsSaved;
        allLogsSaved = SaveLog(targetPath, EVENT_LOG) && allLogsSaved;

        return allLogsSaved;
    }

    return false;
}

/****************************************
** Author:      Joe Li
** Purpose:     Save whiteboard settings data
** Comments:  
****************************************/ 
bool DOSaveAppData::SaveWhiteboardSettingsData(const CComBSTR& sourcePath, const CComBSTR& targetPath)
{
    if (sourcePath.Length() != 0 && targetPath.Length() != 0)
    {
        const unsigned long bufferSize = 256;
        TCHAR buffer[bufferSize];

        DOPersistentFile sourceFile;

        // Search for first source file
        if (sourceFile.FindFirstFile(sourcePath, WHITEBOARD_SETTINGS_WILDCARD_SEARCH, buffer, bufferSize) == true)
        {
            CComBSTR sourceFileName = buffer;
            bool allWhiteboardSettingsSaved = SaveWhiteboardSettings(sourcePath, sourceFileName, targetPath);

            // Search of remaining source file(s)
            while (sourceFile.FindNextFile(buffer, bufferSize) == true)
            {
                sourceFileName = buffer;
                allWhiteboardSettingsSaved = SaveWhiteboardSettings(sourcePath, sourceFileName, targetPath) && allWhiteboardSettingsSaved;
            }

            return allWhiteboardSettingsSaved;
        }
    }

    return false;
}

/****************************************
** Author:      Joe Li
** Purpose:     Get date and time used for saving app data
** Comments:  
****************************************/ 
void DOSaveAppData::GetDateTime(CComBSTR& dateTime)
{
    SetDateTime();
    dateTime = m_dateTime;
}

///////////////////////////////////////////
////// ***** PROTECTED METHODS ***** //////
///////////////////////////////////////////

/////////////////////////////////////////
////// ***** PRIVATE METHODS ***** //////
/////////////////////////////////////////

/****************************************
** Author:    Joe Li
** Purpose:   Set date and time string
** Comments:  
****************************************/
void DOSaveAppData::SetDateTime()
{
    if (m_dateTime.Length() != 0)
        return;

    STime localTime;
    CComBSTR stringValue = _T("");
    unsigned long value = 0;

    DOTime::GetLocalTime(localTime);

    value = localTime.year;
    DODataConversion::LongToString(value, stringValue);
    m_dateTime.Append(stringValue);
    stringValue.Empty();

    value = localTime.month;
    if (value < APPEND_ZERO_CHECK_VALUE)
        m_dateTime.Append(_T("0"));
    DODataConversion::LongToString(value, stringValue);
    m_dateTime.Append(stringValue);
    stringValue.Empty();

    value = localTime.day;
    if (value < APPEND_ZERO_CHECK_VALUE)
        m_dateTime.Append(_T("0"));
    DODataConversion::LongToString(value, stringValue);
    m_dateTime.Append(stringValue);
    stringValue.Empty();

    m_dateTime.Append(_T("_"));

    value = localTime.hour;
    if (value < APPEND_ZERO_CHECK_VALUE)
        m_dateTime.Append(_T("0"));
    DODataConversion::LongToString(value, stringValue);
    m_dateTime.Append(stringValue);
    stringValue.Empty();

    value = localTime.minute;
    if (value < APPEND_ZERO_CHECK_VALUE)
        m_dateTime.Append(_T("0"));
    DODataConversion::LongToString(value, stringValue);
    m_dateTime.Append(stringValue);
    stringValue.Empty();

    value = localTime.second;
    if (value < APPEND_ZERO_CHECK_VALUE)
        m_dateTime.Append(_T("0"));
    DODataConversion::LongToString(value, stringValue);
    m_dateTime.Append(stringValue);
    stringValue.Empty();

    m_dateTime.Append(_T("_"));
}

/****************************************
** Author:    Joe Li
** Purpose:   Save log file
** Comments:  
****************************************/
bool DOSaveAppData::SaveLog(const CComBSTR& targetPath, LOG_TYPE logToSave)
{
    HRESULT hr = E_FAIL;
    DOLogMaintenanceBase logMaintenance(hr);

    if (SUCCEEDED(hr))
    {
        SetDateTime();
        CComBSTR targetLogFileName = m_dateTime;

        switch(logToSave)
        {
        case ALARM_LOG:
            targetLogFileName.Append(_T("AlarmLog.txt"));
            break;
        case ERROR_LOG:
            targetLogFileName.Append(_T("ErrorLog.txt"));
            break;
        case RND_LOG:
            targetLogFileName.Append(_T("RnDLog.txt"));
            break;
        case KEYPRESS_LOG:
            targetLogFileName.Append(_T("KeyPressLog.txt"));
            break;
        case EVENT_LOG:
            targetLogFileName.Append(_T("EventLog.txt"));
            break;
        default:
            return false;
        }

        return logMaintenance.WriteLogEntriesToRemovableStorage(logToSave, targetPath, targetLogFileName);
    }

    return false;
}

/****************************************
** Author:      Joe Li
** Purpose:     Save whiteboard settings data
** Comments:  
****************************************/ 
bool DOSaveAppData::SaveWhiteboardSettings(const CComBSTR& sourcePath, const CComBSTR& sourceFileName, const CComBSTR& targetPath)
{
    DOPersistentFile sourceFile;

    // Open source file for reading
    if (sourceFile.OpenFile(sourcePath, sourceFileName, DOFile::DO_FILE_OPEN_EXISTING, DOFile::DO_FILE_READ) == true)
    {
        SetDateTime();

        CComBSTR targetFileName = m_dateTime;
        targetFileName.Append(sourceFileName);

        DORemovableStorageFile targetFile;
        bool targetFileOpen = true;

        // Open existing target file
        if (targetFile.OpenFile(targetPath, targetFileName, DOFile::DO_FILE_TRUNCATE_EXISTING) == false)
            // Create target file if open existing file failed
            if (targetFile.OpenFile(targetPath, targetFileName) == false)
                targetFileOpen = false;

        if (targetFileOpen == true)
        {
            DOFileUtility fileUtility;
            return fileUtility.CopyFileContents(&sourceFile, &targetFile);
        }
    }

    return false;
}


#endif//  YS_26JUN2008_TEST_RM
