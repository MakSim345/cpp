#include "SimpleACoreDataServer.h"
#include "ACoreDLLAdapter.h"

using boost::asio::ip::tcp;

	SimpleACoreDataServer::SimpleACoreDataServer(const std::string &host, const int port, const int comPort)
	{
	  std::cout << "In SimpleACoreDataServer ctor()" << std::endl;
	  running_ = false;
	  connected_ = false;
	  host_ = host;
	  port_ = port;
	  comPort_ = comPort;
	  std::cout << "done SimpleACoreDataServer" << std::endl;
	}

	void SimpleACoreDataServer::start() {
		std::cout << "In SimpleACoreDataServer start()" << std::endl;
		running_ = true;

		guiSenderThread_.start(host_,port_,100,&io_service_);
		guiReceiverThread_.start(this,host_,port_+1,100,&io_service_);

		if (comPort_ != -1) {
			std::cout << "In SimpleACoreDataServer starting VCB DLL" << std::endl;
			aCoreAdapter_.init(comPort_);
			aCoreAdapter_.start(this, 500);
		}
		else {
			std::cout << "In SimpleACoreDataServer starting ACore simulator" << std::endl;
			aCoreSim_;
			aCoreSim_.start(this,200); //200 is the waveform update speed, 5Hz
		}

		WaveformsMessage waveformsMessage;
		NumericsMessage numericsMessage;
		SettingsMessage settingsMessage;

		while (running_) {
			//std::cout << "In SimpleACoreDataServer start()" << std::endl;

			//
			//  TODO, could add some sanity check here, for now it just sleeps
			//
			boost::asio::deadline_timer timer(io_service_,boost::posix_time::milliseconds(1000));
			timer.expires_from_now(boost::posix_time::milliseconds(1000));
			timer.wait();
			
		}
		aCoreAdapter_.stop();
		guiSenderThread_.stop();
		guiReceiverThread_.stop();
	    std::cout << "done SimpleACoreDataServer start()" << std::endl;
	}

	void SimpleACoreDataServer::stop() {
		std::cout << "In SimpleACoreDataServer stop()" << std::endl;
		running_ = false;
		std::cout << "done SimpleACoreDataServer stop()" << std::endl;
	}

	void SimpleACoreDataServer::receiveWaveforms(WaveformsMessage message) {
		//waveQ_.push(message);
		std::cout << "In SimpleACoreDataServer receiveWaveforms()" << std::endl;
		if (running_ && guiSenderThread_.isRunning()) {
			guiSenderThread_.sendWaveform(message);
		}
	}

	void SimpleACoreDataServer::receiveNumerics(NumericsMessage message) {
		std::cout << "In SimpleACoreDataServer receiveNumerics()" << std::endl;
		if (running_ && guiSenderThread_.isRunning()) {
			guiSenderThread_.sendNumerics(message);
		}
	}

	void SimpleACoreDataServer::receiveSettings(SettingsMessage message) {
		std::cout << "In SimpleACoreDataServer receiveSettings()" << std::endl;
		if (running_) {
			if (comPort_ == -1) {
				aCoreSim_.sendSettings(message);
			}
			else {
				aCoreAdapter_.sendSettings(message);
			}
		}
	}

