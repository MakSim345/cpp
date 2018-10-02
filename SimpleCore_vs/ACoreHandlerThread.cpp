/*
#include "ACoreHandlerThread.h"
#include "SimpleACoreDataServer.h"

#include <iostream>

  ACoreHandlerThread::ACoreHandlerThread()
  {
    std::cout << "In ACoreHandlerThread ctor" << std::endl;
	seq_count = 0;
	running_ = false;
  }

  ACoreHandlerThread::~ACoreHandlerThread() {};


  int ACoreHandlerThread::getPeep() 
  {
	return 1; //peepFromDLL;
  }

  void ACoreHandlerThread::setPeep(int peep) 
  {
	//set peepFromDLL;
  }

  void ACoreHandlerThread::start(ACoreReceiver* receiver)
  {
	std::cout << "in ACoreHandlerThread start() " << std::endl;
    running_ = true;
	this->receiver_ = receiver;
	m_Thread = boost::thread(&ACoreHandlerThread::run, this, 1000);
	std::cout << "done ACoreHandlerThread start() " << std::endl;
  }

  void ACoreHandlerThread::join()
  {
	m_Thread.join();
  }

  void ACoreHandlerThread::stop()
  {
    running_ = false;
	m_Thread.join();
  }

  void ACoreHandlerThread::run(unsigned int sleepMillis) {
	boost::posix_time::milliseconds sleepTime(sleepMillis);
	//WaveformsMessage wm = getNextWaveformMessage();
	std::cout << "in ACoreHandlerThread run() " << sleepMillis << std::endl;
	while (running_) {
		//waveQ.push(&wm);
		receiver_->pushPeep(getPeep());
		boost::this_thread::sleep(sleepTime);
	}
	std::cout << "done ACoreHandlerThread run() " << sleepMillis << std::endl;
  }*/