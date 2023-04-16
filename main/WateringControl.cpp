#include "Arduino.h"
#include "WateringControl.h"

WateringControl::WateringControl()
{
    pinMode(BOMB_PORT, OUTPUT);
}

void WateringControl::turnOn()
{
    digitalWrite(BOMB_PORT, LOW);
}

void WateringControl::turnOff()
{
    digitalWrite(BOMB_PORT, HIGH);
}