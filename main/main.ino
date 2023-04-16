#include "BluetoothApi.h"
#include "Config.h"
#include "WateringControl.h"
#include "LightSensor.h"
#include "HumiditySensor.h"
#include <Wire.h>

BluetoothApi api;
LightSensor lightSensor;
Config config;
WateringControl wateringControl;
HumiditySensor humiditySensor;

String wateringType = "AUTO";
int interval = 30;
int intervalCount = 0;

void sendWateringStatus(bool status)
{
  StaticJsonDocument<200> payload;
  payload["wateringStatus"] = status;
  api.send(payload);
}

void wateringProcess()
{
  sendWateringStatus(true);
  delay(10000);
  wateringControl.turnOn();
  delay(15000);
  wateringControl.turnOff();
  sendWateringStatus(false);
  delay(10000);
}

void setup()
{
  Serial.begin(115200);

  config = Config();
  lightSensor = LightSensor();
  wateringControl = WateringControl();
  humiditySensor = HumiditySensor();
  api = BluetoothApi();

  Wire.begin();
  api.initialize();
  lightSensor.initialize();
  wateringControl.turnOff();
}

void loop()
{
  api.verify();

  ConfigData data = config.get();
  interval = data.interval;
  wateringType = data.wateringType;
  int manualWatering = config.getManualStatus();

  intervalCount++;

  StaticJsonDocument<200> humidity = humiditySensor.read();
  api.send(humidity);
  delay(500);
  StaticJsonDocument<200> light = lightSensor.read();
  api.send(light);
  delay(500);

  if (manualWatering == 1)
  {
    intervalCount = 0;
    manualWatering = 0;
    config.setManualStatus(0);
    wateringProcess();
  }
  if (intervalCount >= interval)
  {
    intervalCount = 0;
    if (wateringType != "AUTO")
    {
      wateringProcess();
    }
  }
  else
  {
    int percent = humidity["percent"];
    if (percent < 40 && wateringType == "AUTO")
    {
      wateringProcess();
    }
  }
}
