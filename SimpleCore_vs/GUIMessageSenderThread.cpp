#ifndef GUI_MESSAGE_SENDER_THREAD_CPP
#define GUI_MESSAGE_SENDER_THREAD_CPP

#include <boost/asio.hpp>
#include <iostream>
#include <boost/thread.hpp>
#include "WaveformsMessage.h"
#include "NumericsMessage.h"
#include "MonitorQueue.cpp"

using boost::asio::ip::tcp;

class GUIMessageSenderThread
{
public:

	bool running_;
	bool connected_;
	std::string host_;
	int port_;
	tcp::iostream stream_;
	boost::asio::io_service *io_service_;
	tcp::endpoint endpoint_;//(boost::asio::ip::address::from_string(host_), port_);
	tcp::acceptor *acceptor; //, endpoint);

    GUIMessageSenderThread() 
    {
        // the thread is not-a-thread until we call start()
		running_ = false;
		connected_ = false;
		
    }

    void start(std::string &host, int port, int sleepMillis, boost::asio::io_service *io_service)
    {
		host_ = host;
		port_ = port; //5050
		running_ = true;
		io_service_ = io_service;
        thread_ = boost::thread(&GUIMessageSenderThread::run, this, sleepMillis);
    }

	void stop() {
		running_ = false;
		join();
	}

    void join()
    {
        thread_.join();
    }
    
    void run(unsigned sleepMillis)
    {
		std::cout << "in GUIMessageSenderThread: run "
                  << sleepMillis << "ms"
                  << std::endl;

		while (running_) {
			if (!connected_) {
				std::cout << "In GUIMessageSenderThread trying to connect to: " << host_ << " " << port_ << std::endl;
				//tcp::endpoint endpoint_(boost::asio::ip::address::from_string(host_), port_);
				//tcp::endpoint endpoint_(boost::asio::ip::address::from_string(host_), port_);
				endpoint_.address(boost::asio::ip::address::from_string(host_));
				endpoint_.port(port_);
				tcp::acceptor acceptor(*io_service_, endpoint_);

				getClientConnection(acceptor);
				try {
				
					sendMessages(sleepMillis);

					acceptor.close();
					stream_.clear();
					stream_.close();
				}
				catch (std::exception& e)
				{
					std::cerr << "GUIMessageSenderThread Error in connection: " << e.what() << std::endl;
				}
				connected_ = false;
				//boost::asio::deadline_timer timer(*io_service_,boost::posix_time::milliseconds(1000));
				//timer.expires_from_now(boost::posix_time::milliseconds(1000));
				//timer.wait();
			}
		}
		std::cout << "done GUIMessageSenderThread: run "
                  << sleepMillis << "ms"
                  << std::endl;
	}

	bool isRunning() {
		return running_;
	}

	void sendWaveform(WaveformsMessage wm) {
		if (connected_) {
			waveQ_.push(wm);
		}
	}

	void sendNumerics(NumericsMessage nm) {
		if (connected_) {
			numericsQ_.push(nm);
		}
	}

	void sendMessages(unsigned sleepMillis) {
		std::cout << "In SimpleACoreDataServer sendMessages()" << std::endl;
		//WaveformSimulator wave_sim_;
		try
		{
			//wave_sim_.start(this);
			WaveformsMessage waveMessage;
			running_ = true;
			while (running_ && connected_)
			{
				if (stream_.good()) {
					//sending a waveform message
					waveMessage = waveQ_.popWait();
					std::cout << "GUIMessageSenderThread sending a waveform message" << std::endl;
					stream_ << waveMessage.toXML() << std::endl;

					while (!numericsQ_.isEmpty()) {
						std::cout << "GUIMessageSenderThread sending a numerics message!" << std::endl;
						stream_ << numericsQ_.popWait().toXML() << std::endl;
					}

				}
				else {
					connected_ = false;
				}
			  //now wait
			  //timer.expires_from_now(boost::posix_time::milliseconds(100));
			  //timer.wait();

			  //send a numerics message
			  //std::cout << "sending a numerics message!" << std::endl;
			  //stream << numerics_sim_.getNextNumericsMessage().toXML() << std::endl;
			  //now wait
			  //timer.expires_from_now(boost::posix_time::milliseconds(100));
			  //timer.wait();
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Error sending messages: " << e.what() << std::endl;
		}
		//wave_sim_.stop();
		stream_.clear();
		stream_.close();
		std::cout << "done SimpleACoreDataServer sendMessages()" << std::endl;
	}

	
	void getClientConnection (tcp::acceptor &acceptor) {
		std::cout << "In GUIMessageSenderThread getClientConnection()" << std::endl;
		try
		{
			std::cout << "waiting for gui client to connect..." << std::endl;
			acceptor.accept(*stream_.rdbuf());
			std::cout << "...gui client connected" << std::endl;
			connected_ = true;
		}
		catch (std::exception& e)
		{
			std::cerr << "Error in gui client connection: " << e.what() << std::endl;
		}
		std::cout << "done GUIMessageSenderThread getClientConnection()" << std::endl;
	}

private:
	MonitorQueue<WaveformsMessage> waveQ_;
	MonitorQueue<NumericsMessage> numericsQ_;
    boost::thread thread_;
};
#endif