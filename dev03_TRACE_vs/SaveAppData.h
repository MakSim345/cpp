#ifndef _SAVE_APP_DATA_H_
#define _SAVE_APP_DATA_H_

//#ifdef YS_26JUN2008_TEST_RM

// #include "LogMaintenanceBase.h"

struct STime
{
	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned long hour;
	unsigned long minute;
	unsigned long second;
};

class DOSaveAppData
{
public:
	DOSaveAppData();
	virtual ~DOSaveAppData();

    //bool SaveLogData(const CComBSTR& targetPath, LOG_TYPE logToSave);
    //bool SaveAllLogData(const CComBSTR& targetPath);
    //bool SaveWhiteboardSettingsData(const CComBSTR& sourcePath, const CComBSTR& targetPath);
    void GetDateTime(CComBSTR& dateTime);

protected:
	// Copy construtor - NO IMPLEMENTATION
	DOSaveAppData (const DOSaveAppData&);
	// Operator = - NO IMPLEMENTATION
	DOSaveAppData & operator = (const DOSaveAppData&);

private:
    void SetDateTime();
    //bool SaveLog(const CComBSTR& targetPath, LOG_TYPE logToSave);
    bool SaveWhiteboardSettings(const CComBSTR& sourcePath, const CComBSTR& sourceFileName, const CComBSTR& targetPath);

    CComBSTR            m_dateTime;
};

//#endif YS_26JUN2008_TEST_RM

#endif // !defined(_SAVE_APP_DATA_H_)
