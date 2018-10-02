#include "ACoreDLLAdapter.h"
#include "VcbTestInterfaceDll.h"
#include "VentUserSettings.h"
#include "VentilatorWaveforms.h"

ACoreDLLAdapter::ACoreDLLAdapter() {
	initialised_ = false;
}

ACoreDLLAdapter::~ACoreDLLAdapter() {}

void ACoreDLLAdapter::init(int comPort) {
	std::cout<<"in ACoreDLLAdapter init() serial com port:" << comPort<< std::endl;
	comPort_ = comPort;
    connected_ = false;
	running_ = false;
	// Load the DLL code
	dllHandle = LoadLibrary("VcbTestInterfaceDll.dll");
	if (dllHandle != 0)
	{
        std::cout<<"VcbTestInterfaceDll library loaded!\n";
		initialised_ = true;
	}
	else
	{
        std::cout<<"VcbTestInterfaceDll library failed to load!\n";
		initialised_ = false;
	}
	
	userSettings_.bySettingType = 1;
	userSettings_.VentilationMode = VENTILATION_MODE_PT_VCV;
	userSettings_.bBackupSetting = 0;
	userSettings_.bySetBreathRate = 12;
	userSettings_.nSetPeep = 0;
	userSettings_.dwSetTidalVolume = 5000;
	userSettings_.nSetPinspired = 1000;
	userSettings_.nSetPhigh = 1000; 
	userSettings_.nSetPLimit = 10000;
	userSettings_.nSetPmax = 10000;
	userSettings_.dwApneaDelayTime = 30;
	userSettings_.byLeakLimit = 50;
	userSettings_.nAltitude = 300;
	userSettings_.byVolumeCalcCondition = 0;
	userSettings_.byLeakCompensation = 0;
	userSettings_.bNfsState = 1;
	userSettings_.nSetTinsp = 1700;
	userSettings_.nSetTlow = 4250;
	userSettings_.bTriggerCompensation = 0;
	userSettings_.bManualVentModeOn = 0;

	std::cout<<"done ACoreDLLAdapter init()" << std::endl;
}

void ACoreDLLAdapter::start(ACoreReceiver* receiver, long sleepMillis) {
	std::cout<<"in ACoreDLLAdapter start()" << std::endl;
	receiver_ = receiver;
	if (!initialised_) {
		std::cout<<"can not start ACoreDLLAdapter, VcbTestInterfaceDll library failed to load!" << std::endl;
		return;
	}
	running_ = true;
	thread_ = boost::thread(&ACoreDLLAdapter::run, this, sleepMillis);
	std::cout<<"done ACoreDLLAdapter start()" << std::endl;
}

void ACoreDLLAdapter::stop() {
	std::cout<<"in ACoreDLLAdapter stop()" << std::endl;
	running_ = false;
	join();
	std::cout<<"done ACoreDLLAdapter stop()" << std::endl;
}

void ACoreDLLAdapter::join()
{
	thread_.join();
}

void ACoreDLLAdapter::sendSettings(SettingsMessage message) {
	if (initialised_) {
		settingsQ_.push(message);
	}
}

void ACoreDLLAdapter::run(long sleepMillis) {
	std::cout<<"In ACoreDLLAdapter run()" << std::endl;
    //VentilationParameters params;
    //VentUserSettings settings;
	
    int count = 0;
    while (initialised_ && running_ && !connected_)
    {
		std::cout<<"Trying to connect to VCB; attempt# " << count++ << std::endl;
		connected_ = startConnection( comPort_, 50 );
		Sleep(sleepMillis);
    }
    
    //setVentParameters(&params);
    //setVentUserSettings(&settings);
	
	int numericsSeq = 0;
	NumericsMessage numerics;
	SettingsMessage settings;
	WaveformsMessage waveformsMessage;
	waveformsMessage.flow.name = "Flow";
	waveformsMessage.paw.name = "Paw";
	waveformsMessage.vol.name = "Vol";
	VentilatorWaveforms* waveforms;
	while(running_)
	{   
		int peep = getPeep();
		//int breathRate = getBreathRate();
		int pMax = getPmax();
		//int tv = getTidalVolume();

		std::cout<<"Current Peep=" << peep << std::endl;

		numerics.seq_id = numericsSeq++;
		numerics.peep.name = constants_.PEEP_NUMERIC;
		numerics.peep.data = peep; // / 100;
		numerics.pMax.name = constants_.PMAX_NUMERIC;
		numerics.pMax.data = pMax;

		// when waveforms are ready try this...
		/*getVentilatorWaveforms(waveforms);

		waveformsMessage.seq_id = waveforms->SequenceNumber;

		for (int i=0; i < 10; i++) {
			waveformsMessage.paw.data[i] = waveforms->PawWaveform[i];
			waveformsMessage.vol.data[i] = waveforms->VolumeWaveform[i];
			waveformsMessage.flow.data[i] = waveforms->FlowWaveform[i];
		}
		receiver_->receiveWaveforms(waveformsMessage);
		*/

		receiver_->receiveNumerics(numerics);

		if (!settingsQ_.isEmpty()) {
			SettingsMessage settingsMessage = settingsQ_.popWait();
			
			std::cout<<"ACoreDLLAdapter setting is " << settingsMessage.theSetting.name << std::endl;
			if (settingsMessage.theSetting.name == constants_.SET_PEEP) {
				int peepSetting = settingsMessage.theSetting.data;
				
				if (peepSetting >= 0 && peepSetting <= 50) {
					userSettings_.nSetPeep = peepSetting * 100;
					std::cout<<"ACoreDLLAdapter setting peep to " << peepSetting << std::endl;
					setPeep(peepSetting * 100);
					//setVentUserSettings();
				}
				else {
					std::cout<<"ACoreDLLAdapter setPeep out of range " << peepSetting << std::endl;
				}
			}
			else if (settingsMessage.theSetting.name == constants_.SET_BREATH_RATE) {
				int breathRateSetting = settingsMessage.theSetting.data;
				
				if (breathRateSetting >= 3 && breathRateSetting <= 120) {
					userSettings_.bySetBreathRate = breathRateSetting;
					std::cout<<"ACoreDLLAdapter setting breathRate to " << breathRateSetting << std::endl;
					setBreathRate(breathRateSetting);
					//setVentUserSettings();
				}
				else {
					std::cout<<"ACoreDLLAdapter setBreathRate out of range " << breathRateSetting << std::endl;
				}
			}
			else if (settingsMessage.theSetting.name == constants_.SET_PMAX) {
				int pMaxSetting = settingsMessage.theSetting.data;
				
				if (pMaxSetting >= 3 && pMaxSetting <= 120) {
					userSettings_.nSetPmax = pMaxSetting;
					std::cout<<"ACoreDLLAdapter setting PMax to " << pMaxSetting << std::endl;
					setPmax(pMaxSetting);
					//setVentUserSettings();
				}
				else {
					std::cout<<"ACoreDLLAdapter setPmax out of range " << pMaxSetting << std::endl;
				}
			}
		}
        
        Sleep(sleepMillis);
        //std::cout<<"setting Peep to 6\n";
        //setPeep(600);

        //Sleep(60000);
        //std::cout<<"setting Peep to 1\n";
        //setPeep(100);

		//
		//receiver->pushWaveform(wm);
	}
    std::cout << "Vent Parameters are controlled from DU now\n";
    restoreVentParameters();
	FreeLibrary(dllHandle);
	std::cout<<"done ACoreDLLAdapter run()" << std::endl;
}