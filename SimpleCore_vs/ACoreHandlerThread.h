#ifndef ACORE_HANDLER_THREAD_H
#define ACORE_HANDLER_THREAD_H

#include <iostream>
#include <boost/thread.hpp>
#include <string>
#include "WaveformsMessage.h"
#include "MonitorQueue.cpp"
#include "ACoreReceiver.h"

class ACoreHandlerThread
{

public:
  int seq_count;
  std::string message_;

  ACoreHandlerThread();
  ~ACoreHandlerThread();
  int getPeep();
  void setPeep(int peep);
  void start(ACoreReceiver* receiver);
  void stop();
  void join();
  void run(unsigned int sleepMillis);

private:
  boost::thread m_Thread;
  ACoreReceiver* receiver_;
  bool running_;
};
#endif