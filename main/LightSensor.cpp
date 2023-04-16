#include "Arduino.h"
#include "LightSensor.h"

BH1750 lightMeter;

LightSensor::LightSensor()
{
   
}

void LightSensor::initialize()
{
    if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        Serial.println(F("Error initialising BH1750"));
    }
}

StaticJsonDocument<200> LightSensor::read()
{
    StaticJsonDocument<200> payload;
    float lux = lightMeter.readLightLevel();
    payload["lux"] = lux;
    return payload;
}