#ifndef WateringControl_h
#define WateringControl_h

#include "Arduino.h"

#define BOMB_PORT 4

class WateringControl
{
public:
    WateringControl();
    void turnOn();
    void turnOff();
};
#endif