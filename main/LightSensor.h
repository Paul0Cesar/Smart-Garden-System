#ifndef LightSensor_h
#define LightSensor_h

#include "Arduino.h"
#include <BH1750.h>
#include <ArduinoJson.h>

class LightSensor
{
public:
    LightSensor();
    void initialize();
    StaticJsonDocument<200> read();

private:
    
};
#endif