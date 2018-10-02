#ifndef SIMPLE_ACORE_DATA_SERVER_CPP
#define SIMPLE_ACORE_DATA_SERVER_CPP

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "WaveformReceiver.h"
#include "ACoreSimulator.h"
#include "MonitorQueue.cpp"
#include "ACoreReceiver.h"
#include "GUIReceiver.h"
#include "GUIMessageReceiverThread.cpp"
#include "GUIMessageSenderThread.cpp"
#include "ACoreDLLAdapter.h"

using boost::asio::ip::tcp;
class SimpleACoreDataServer : public ACoreReceiver, GUIReceiver
{
public:

	SimpleACoreDataServer(const std::string &host, const int port, const int comPort);
	virtual void start();
	virtual void stop();
	//virtual void pushWaveform(WaveformsMessage wm);
	virtual void receiveWaveforms(WaveformsMessage wm);
	virtual void receiveNumerics(NumericsMessage nm);
	virtual void receiveSettings(SettingsMessage sm);
	//virtual void receivePeep(int peep);

private:
	GUIMessageSenderThread guiSenderThread_;
	GUIMessageReceiverThread guiReceiverThread_;
	ACoreDLLAdapter aCoreAdapter_;
	ACoreSimulator aCoreSim_;
	
	//MonitorQueue<WaveformsMessage> waveQ_;
	//MonitorQueue<NumericsMessage> numericsQ_;
	//MonitorQueue<SettingsMessage> settingsQ_;
	//ACoreSimulator wave_sim_;
	//NumericsSimulator numerics_sim_;
	bool running_;
	bool connected_;
	std::string host_;
	int port_;
	int comPort_;
	tcp::iostream stream_;
	boost::asio::io_service io_service_;
	tcp::endpoint endpoint_;//(boost::asio::ip::address::from_string(host_), port_);
	//tcp::acceptor *acceptor; //, endpoint);

	void getClientConnection(tcp::acceptor &acceptor);
	void sendMessages();
};
#endif