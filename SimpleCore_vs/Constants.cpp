#ifndef CONSTANTS_CPP
#define CONSTANTS_CPP

#include <string>

class Constants {

public:
	std::string SET_VENTILATION_MODE;
	std::string SET_PEEP;
	std::string SET_BREATH_RATE;
	std::string SET_PMAX;
	std::string SET_TIDAL_VOLUME;

	std::string PEEP_NUMERIC;
	std::string BREATH_RATE_NUMERIC;
	std::string PMAX_NUMERIC;
	std::string TIDAL_VOLUME_NUMERIC;

	std::string FLOW_WAVEFORM;
	std::string VOLUME_WAVEFORM;
	std::string PAW_WAVEFORM;

	Constants() {
		SET_VENTILATION_MODE = "SetVentilationMode";
		SET_PEEP = "SetPeep";
		SET_BREATH_RATE = "SetBreathRate";
		SET_PMAX = "SetPmax";
		SET_TIDAL_VOLUME = "SetTidalVolume";

		PEEP_NUMERIC = "Peep";
		BREATH_RATE_NUMERIC = "BreathRate";
		PMAX_NUMERIC = "Pmax";
		TIDAL_VOLUME_NUMERIC = "TidalVolume";

		FLOW_WAVEFORM = "Flow";
		VOLUME_WAVEFORM = "Vol";
		PAW_WAVEFORM = "Paw";
	}

	~Constants() {}

};
#endif