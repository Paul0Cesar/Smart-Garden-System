#ifndef HumiditySensor_h
#define HumiditySensor_h

#include "Arduino.h"
#include <ArduinoJson.h>

#define SENSOR_PORT 32

class HumiditySensor
{
public:
    HumiditySensor();
    StaticJsonDocument<200> read();
};
#endif