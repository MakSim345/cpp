#ifndef ACORE_DLL_ADAPTER_H
#define ACORE_DLL_ADAPTER_H

#include "ACoreReceiver.h"
#include "windows.h"
#include <iostream>
#include <boost/thread.hpp>
#include "MonitorQueue.cpp"
#include "ACoreReceiver.h"
#include "SettingsMessage.h"
#include "VentUserSettings.h"
#include "VCB_Enums.h"
#include "Constants.cpp"

class ACoreDLLAdapter {

public:
	ACoreDLLAdapter();
	virtual ~ACoreDLLAdapter();

	void start( ACoreReceiver* receiver, long sleepMillis);
	void stop();
	void join();
	void init(int comPort);
	void run(long sleepMillis);
	void sendSettings(SettingsMessage message);

private:
	Constants constants_;
	boost::thread thread_;
	int comPort_;
	MonitorQueue<SettingsMessage> settingsQ_;
	ACoreReceiver *receiver_;
    bool connected_;
	bool running_;
	bool initialised_;
	VentUserSettings userSettings_;
    HMODULE dllHandle;
};
#endif