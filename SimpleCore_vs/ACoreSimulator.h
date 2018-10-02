#ifndef ACORE_SIMULATOR_H
#define ACORE_SIMULATOR_H

#include <iostream>
#include <boost/thread.hpp>
#include <string>
#include "WaveformsMessage.h"
#include "NumericsMessage.h"
#include "SettingsMessage.h"
#include "MonitorQueue.cpp"
#include "ACoreReceiver.h"
#include "Constants.cpp"

class ACoreSimulator
{

public:
  int lastRR_;
  int lastPeep_;
  int lastTV_;
  int lastSetRR_;
  int lastSetPeep_;
  int lastSetTV_;
  int waveCounter;
  int numericsCounter;
  WaveformsMessage simWaveformsMessage;
  NumericsMessage simNumericsMessage;
  Waveform simFlowWaveforms[10];
  Waveform simPawWaveforms[10];
  Waveform simVolWaveforms[10];
  std::string message_;

  ACoreSimulator();
  ~ACoreSimulator();
  
  void start(ACoreReceiver* receiver, unsigned int sleepMillis);
  void stop();
  void join();
  void simulate(unsigned int sleepMillis);
  void sendSettings(SettingsMessage message);

private:
  Constants constants_;
  boost::thread m_Thread;
  ACoreReceiver* receiver;
  bool running_;
  MonitorQueue<SettingsMessage> settingsQ_;

  WaveformsMessage getNextWaveformMessage();
  NumericsMessage getNextNumericsMessage();
};
#endif