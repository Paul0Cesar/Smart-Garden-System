#include "Arduino.h"
#include "Config.h"

Config::Config()
{
}

void Config::open()
{
    preferences.begin("smartGarden", false);
}

void Config::close()
{
    preferences.end();
}

void Config::update(String wateringType, int interval)
{
    open();
    preferences.putString("wateringType", wateringType);
    preferences.putUInt("interval", interval);
    close();
}
void Config::setManualStatus(int status)
{
    open();
    preferences.putUInt("manualStatus", status);
    close();
}

int Config::getManualStatus()
{
    open();
    int manual = preferences.getUInt("manualStatus", 0);
    close();
    return manual;
}

ConfigData Config::get()
{
    ConfigData config;
    open();
    config.interval = preferences.getUInt("interval", 600000);
    config.wateringType = preferences.getString("wateringType", "AUTO");
    close();
    return config;
}
