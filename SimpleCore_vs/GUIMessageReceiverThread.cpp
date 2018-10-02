#ifndef GUI_MESSAGE_RECEIVER_THREAD_CPP
#define GUI_MESSAGE_RECEIVER_THREAD_CPP

#include <boost/asio.hpp>
#include <iostream>
#include <boost/thread.hpp>
#include "SettingsMessage.h"
#include "GUIReceiver.h"

using boost::asio::ip::tcp;

class GUIMessageReceiverThread
{
public:
	GUIReceiver *receiver_;
	bool running_;
	bool connected_;
	std::string host_;
	int port_;
	tcp::iostream stream_;
	boost::asio::io_service *io_service_;
	tcp::endpoint endpoint_;//(boost::asio::ip::address::from_string(host_), port_);
	tcp::acceptor *acceptor; //, endpoint);

    GUIMessageReceiverThread() 
    {
        // the thread is not-a-thread until we call start()
		running_ = false;
		connected_ = false;
    }

    void start(GUIReceiver *receiver, std::string host, int port, int sleepMillis, boost::asio::io_service *io_service)
    {
		receiver_ = receiver;
		host_ = host;
		port_ = port; //5051
		running_ = true;
		io_service_ = io_service;
        thread_ = boost::thread(&GUIMessageReceiverThread::run, this, sleepMillis);
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
		std::cout << "in GUIMessageReceiverThread: run "
                  << sleepMillis << "ms"
                  << std::endl;

		while (running_) {
			if (!connected_) {
				std::cout << "In GUIMessageReceiverThread trying to connect to: " << host_ << " " << port_ << std::endl;
				//tcp::endpoint endpoint_(boost::asio::ip::address::from_string(host_), port_);
				//tcp::endpoint endpoint_(boost::asio::ip::address::from_string(host_), port_);
				endpoint_.address(boost::asio::ip::address::from_string(host_));
				endpoint_.port(port_);
				tcp::acceptor acceptor(*io_service_, endpoint_);

				getClientConnection(acceptor);
				try {
				
					readMessages(sleepMillis);

					acceptor.close();
					stream_.clear();
					stream_.close();
				}
				catch (std::exception& e)
				{
					std::cerr << "GUIMessageReceiverThread Error in connection: " << e.what() << std::endl;
				}
				connected_ = false;
				//boost::asio::deadline_timer timer(*io_service_,boost::posix_time::milliseconds(1000));
				//timer.expires_from_now(boost::posix_time::milliseconds(1000));
				//timer.wait();
			}
		}
		std::cout << "done GUIMessageReceiverThread: run "
                  << sleepMillis << "ms"
                  << std::endl;
	}

	void readMessages(unsigned sleepMillis) {
		std::cout << "in GUIMessageReceiverThread: readMessages" << std::endl;
		while (running_ && connected_) {
			if (stream_.good()) {
				boost::posix_time::milliseconds workTime(sleepMillis);
				std::string line;
				std::getline(stream_, line);
				
				if (line != "") {
					SettingsMessage message;
					message = message.fromXML(line);
					std::cout << "GUIMessageReceiverThread received a settings message id: " << message.seq_id<< std::endl;
                    std::cout << "GUIMessageReceiverThread received a settings message setting data: " << message.theSetting.data<< std::endl;
                    std::cout << "GUIMessageReceiverThread received a settings message setting name: " << message.theSetting.name<< std::endl;
					receiver_->receiveSettings(message);
				}
				// We're busy, honest!
				boost::this_thread::sleep(workTime);
			}
			else {
				connected_ = false;
			}
		}
        std::cout << "done GUIMessageReceiverThread: readMessages" << std::endl;
    }

	
	void getClientConnection (tcp::acceptor &acceptor) {
		std::cout << "In GUIMessageReceiverThread getClientConnection()" << std::endl;
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
		std::cout << "done GUIMessageReceiverThread getClientConnection()" << std::endl;
	}

private:

    boost::thread thread_;
};
#endif