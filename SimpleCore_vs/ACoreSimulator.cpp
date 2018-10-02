#include "ACoreSimulator.h"
#include "SimpleACoreDataServer.h"

  ACoreSimulator::ACoreSimulator()
  {
    std::cout << "In ACoreSimulator ctor" << std::endl;
	//this->waveQ = waveQueue;
	
	simPawWaveforms[0].name = "Paw";
	simPawWaveforms[1].name = "Paw";
	simPawWaveforms[2].name = "Paw";
	simPawWaveforms[3].name = "Paw";
	simPawWaveforms[4].name = "Paw";
	simPawWaveforms[5].name = "Paw";
	simPawWaveforms[6].name = "Paw";
	simPawWaveforms[7].name = "Paw";
	simPawWaveforms[8].name = "Paw";
	simPawWaveforms[9].name = "Paw";

	simFlowWaveforms[0].name = "Flow";
	simFlowWaveforms[1].name = "Flow";
	simFlowWaveforms[2].name = "Flow";
	simFlowWaveforms[3].name = "Flow";
	simFlowWaveforms[4].name = "Flow";
	simFlowWaveforms[5].name = "Flow";
	simFlowWaveforms[6].name = "Flow";
	simFlowWaveforms[7].name = "Flow";
	simFlowWaveforms[8].name = "Flow";
	simFlowWaveforms[9].name = "Flow";

	simVolWaveforms[0].name = "Vol";
	simVolWaveforms[1].name = "Vol";
	simVolWaveforms[2].name = "Vol";
	simVolWaveforms[3].name = "Vol";
	simVolWaveforms[4].name = "Vol";
	simVolWaveforms[5].name = "Vol";
	simVolWaveforms[6].name = "Vol";
	simVolWaveforms[7].name = "Vol";
	simVolWaveforms[8].name = "Vol";
	simVolWaveforms[9].name = "Vol";
	

	int pawData[] = {400,490,580,670,760,850,940,1030,1120,1210,2200,2290,2380,2470,2560,2650,2740,2830,2920,3010,3100,3190,3280,3370,3460,3550,3640,3730,3820,3910,2229,2096,1969,1849,1734,1625,1521,1423,1329,1240,1155,1074,997,924,855,789,726,666,609,555,109,79,51,24,-1,-25,-48,-70,-91,-111,-130,-148,-165,-182,-197,-212,-226,-239,-252,-264,-364,-370,-377,-383,-388,-394,-399,-404,-408,-413,-417,-421,-425,-429,-432,-435,-438,-441,-444,-447,-500,-410,-320,-230,-140,-50,40,130,220,310};
	int flowData[] = {70000,66586,63338,60249,57311,54516,51857,49328,46922,44633,42457,40386,38416,36543,34760,33065,31453,29919,28459,27071,15619,14857,14132,13443,12787,12164,11570,11006,10469,9959,9473,9011,8571,8153,7756,7377,7018,6675,6350,6040,3485,3315,3153,2999,2853,2714,2581,2455,2336,2222,2113,2010,1912,1819,1730,1646,1565,1489,1416,1347,777,739,703,669,636,605,576,547,521,495,0,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000,-70000};
	int volData[] = {0,0,0,0,0,0,0,0,0,0,5000,10000,15000,20000,25000,30000,35000,40000,45000,50000,160000,170000,180000,195000,210000,225000,240000,255000,270000,285000,300000,310000,320000,330000,340000,350000,360000,370000,380000,390000,475000,480000,485000,490000,495000,500000,500000,500000,500000,500000,500000,500000,500000,500000,500000,500000,500000,500000,500000,500000,470000,465000,460000,455000,450000,440000,430000,420000,410000,400000,390000,380000,370000,360000,350000,340000,330000,320000,310000,300000,150000,140000,130000,120000,110000,100000,90000,80000,70000,60000,50000,45000,40000,35000,30000,25000,20000,15000,10000,5000};

	for (int i=0; i < 10; i++) {
		simPawWaveforms[0].data[i] = pawData[i];
		simPawWaveforms[1].data[i] = pawData[i+10];
		simPawWaveforms[2].data[i] = pawData[i+20];
		simPawWaveforms[3].data[i] = pawData[i+30];
		simPawWaveforms[4].data[i] = pawData[i+40];
		simPawWaveforms[5].data[i] = pawData[i+50];
		simPawWaveforms[6].data[i] = pawData[i+60];
		simPawWaveforms[7].data[i] = pawData[i+70];
		simPawWaveforms[8].data[i] = pawData[i+80];
		simPawWaveforms[9].data[i] = pawData[i+90];
		simFlowWaveforms[0].data[i] = flowData[i];
		simFlowWaveforms[1].data[i] = flowData[i+10];
		simFlowWaveforms[2].data[i] = flowData[i+20];
		simFlowWaveforms[3].data[i] = flowData[i+30];
		simFlowWaveforms[4].data[i] = flowData[i+40];
		simFlowWaveforms[5].data[i] = flowData[i+50];
		simFlowWaveforms[6].data[i] = flowData[i+60];
		simFlowWaveforms[7].data[i] = flowData[i+70];
		simFlowWaveforms[8].data[i] = flowData[i+80];
		simFlowWaveforms[9].data[i] = flowData[i+90];
		simVolWaveforms[0].data[i] = volData[i];
		simVolWaveforms[1].data[i] = volData[i+10];
		simVolWaveforms[2].data[i] = volData[i+20];
		simVolWaveforms[3].data[i] = volData[i+30];
		simVolWaveforms[4].data[i] = volData[i+40];
		simVolWaveforms[5].data[i] = volData[i+50];
		simVolWaveforms[6].data[i] = volData[i+60];
		simVolWaveforms[7].data[i] = volData[i+70];
		simVolWaveforms[8].data[i] = volData[i+80];
		simVolWaveforms[9].data[i] = volData[i+90];
	}

	simWaveformsMessage.flow = simFlowWaveforms[0];
	simWaveformsMessage.paw = simPawWaveforms[0];
	simWaveformsMessage.vol = simVolWaveforms[0];
	simWaveformsMessage.seq_id = 0;
	waveCounter = 0;

	numericsCounter = 0;

	lastSetRR_ = 10;
	lastRR_ = lastSetRR_;
	lastSetPeep_ = 5;
	lastPeep_ = lastSetPeep_;
	lastSetTV_ = 100;
	lastTV_ = lastSetTV_;

	running_ = false;
  }

  ACoreSimulator::~ACoreSimulator() {};


  WaveformsMessage ACoreSimulator::getNextWaveformMessage() 
  {
    waveCounter++;
	if (waveCounter > 999) {
		//reset the seq number
		waveCounter = 0;
	}
	
	simWaveformsMessage.seq_id = waveCounter;
	simWaveformsMessage.flow = simFlowWaveforms[waveCounter%10];
	simWaveformsMessage.flow.name = "Flow";
	simWaveformsMessage.paw = simPawWaveforms[waveCounter%10];
	simWaveformsMessage.paw.name = "Paw";
	simWaveformsMessage.vol = simVolWaveforms[waveCounter%10];
	simWaveformsMessage.vol.name = "Vol";
	//std::cout << "In ACoreSimulator getNextMessage() " << seq_count << " msg is: " << simWaveformsMessage.toXML() << std::endl;
	return simWaveformsMessage;
  }

  NumericsMessage ACoreSimulator::getNextNumericsMessage() 
  {
    numericsCounter++;
	if (numericsCounter > 999) {
		//reset the seq number
		numericsCounter = 0;
	}
	
	simNumericsMessage.seq_id = numericsCounter;

	simNumericsMessage.peep.name = "Peep"; //constants_.PEEP_NUMERIC;

	//simulate approaching the correct setting
	if (lastPeep_ < lastSetPeep_) {
		lastPeep_++;
	}
	else if (lastPeep_ > lastSetPeep_){
		lastPeep_--;
	}
	simNumericsMessage.peep.data = lastPeep_;

	simNumericsMessage.rr.name = "BreathRate"; //constants_.BREATH_RATE_NUMERIC;
	if (lastRR_ < lastSetRR_) {
		lastRR_++;
	}
	else if (lastRR_ > lastSetRR_){
		lastRR_--;
	}
	simNumericsMessage.rr.data = lastRR_;

	simNumericsMessage.tv.name = "TidalVolume"; //constants_.TIDAL_VOLUME_NUMERIC;
	if (lastTV_ < lastSetTV_) {
		lastTV_++;
	}
	else if (lastTV_ > lastSetTV_) {
		lastTV_--;
	}

	simNumericsMessage.tv.data = lastTV_;
	simNumericsMessage.pMax.name = "Pmax"; //constants_.PMAX_NUMERIC;
	simNumericsMessage.pMax.data = numericsCounter%10 * 10;

	//std::cout << "In ACoreSimulator getNextNumericsMessage() " << numericsCounter << " msg is: " << simNumericsMessage.toXML() << std::endl;
	return simNumericsMessage;
  }

  void ACoreSimulator::start(ACoreReceiver* receiver, unsigned sleepMillis)
  {
    running_ = true;
	this->receiver = receiver;
	m_Thread = boost::thread(&ACoreSimulator::simulate, this, sleepMillis);
  }

  void ACoreSimulator::join()
  {
	m_Thread.join();
  }

  void ACoreSimulator::stop()
  {
    running_ = false;
	m_Thread.join();
  }

  void ACoreSimulator::sendSettings(SettingsMessage message) {
	if (running_) {
		settingsQ_.push(message);
	}
  }

  void ACoreSimulator::simulate(unsigned int sleepMillis) {
	boost::posix_time::milliseconds sleepTime(sleepMillis);
	//WaveformsMessage wm = getNextWaveformMessage();
	while (running_) {
		//waveQ.push(&wm);
		if (!settingsQ_.isEmpty()) {
			
			SettingsMessage settings = settingsQ_.popWait();
			std::cout << "In ACoreSimulator received setting: " << settings.toXML() << std::endl;
			if (settings.theSetting.name == "SetBreathRate") {
				lastSetRR_ = settings.theSetting.data;
			}
			else if (settings.theSetting.name == "SetTidalVolume") {
				lastSetTV_ = settings.theSetting.data;
			}
			else if (settings.theSetting.name == "SetPeep") {
				lastSetPeep_ = settings.theSetting.data;
			}
			/*else if (settings.theSetting.name == "SetPMax") {
				lastRR = settings.theSetting.data;
			}*/
			
		}
		this->receiver->receiveWaveforms(getNextWaveformMessage());

		if (waveCounter % 3 == 0) {
			this->receiver->receiveNumerics(getNextNumericsMessage());
		}
		boost::this_thread::sleep(sleepTime);
	}
  }
