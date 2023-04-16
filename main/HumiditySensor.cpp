#include "Arduino.h"
#include "HumiditySensor.h"

HumiditySensor::HumiditySensor()
{
}

StaticJsonDocument<200> HumiditySensor::read()
{
    StaticJsonDocument<200> payload;
    int humidity = analogRead(SENSOR_PORT);
    int percent = ( 100 - ( (humidity/4095.00) * 100 ) );
    payload["humidity"] = humidity;
    payload["percent"] = percent;
    return payload;
}