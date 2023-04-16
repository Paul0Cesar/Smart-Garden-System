#ifndef BluetoothApi_h
#define BluetoothApi_h

#include "Arduino.h"
#include <inttypes.h>
#include "BluetoothSerial.h"
#include <ArduinoJson.h>
#include "Config.h"

class BluetoothApi
{
public:
  BluetoothApi();
  void initialize();
  void verify();
  void send(StaticJsonDocument<200> body);

private:
  BluetoothSerial serialBT;
  Config config;
  std::function<void(String)> readSensor;
  void request(String json);
  void router(String route, String body);
};
#endif