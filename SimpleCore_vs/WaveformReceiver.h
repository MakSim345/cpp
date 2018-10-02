#ifndef WAVEFORM_RECEIVER_H
#define WAVEFORM_RECEIVER_H

#include "WaveformsMessage.h"

class WaveformReceiver {
public:
virtual ~WaveformReceiver() {}
virtual void receiveWaveforms(WaveformsMessage wm) = 0;

};
#endif;