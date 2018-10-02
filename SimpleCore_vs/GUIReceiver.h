#ifndef GUI_RECEIVER_H
#define GUI_RECEIVER_H

#include "SettingsMessage.h"

class GUIReceiver {
public:
virtual ~GUIReceiver() {}
//virtual void setPeep(int peep) = 0;
virtual void receiveSettings(SettingsMessage message) = 0;

};
#endif;