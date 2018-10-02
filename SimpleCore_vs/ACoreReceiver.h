#ifndef ACORE_RECEIVER_H
#define ACORE_RECEIVER_H

#include "WaveformsMessage.h"
#include "NumericsMessage.h"

class ACoreReceiver {
public:
virtual ~ACoreReceiver() {}
virtual void receiveWaveforms(WaveformsMessage wm) = 0;
virtual void receiveNumerics(NumericsMessage nm) = 0;

};
#endif;