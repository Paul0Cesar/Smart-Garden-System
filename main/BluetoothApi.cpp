#include "BluetoothApi.h"

BluetoothApi::BluetoothApi()
{
    config = Config();
}

void BluetoothApi::initialize()
{
    serialBT.begin("SmartGarden");
    serialBT.println(F("Bluetooth Api Started! Ready to pair..."));
}

void BluetoothApi::verify()
{
    if (serialBT.available())
    {
        request(serialBT.readString());
    }
    delay(20);
}

void BluetoothApi::send(StaticJsonDocument<200> body)
{
    String a;
    serializeJson(body, a);
    uint8_t buf[a.length()];
    memcpy(buf, a.c_str(), a.length());
    serialBT.write(buf, a.length());
    serialBT.println();
}

void BluetoothApi::request(String json)
{
    try
    {
        Serial.println(F("[BluetoothApi][request] New Request Receive:"));
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, json);
        if (error)
        {
            throw 1;
        }
        const char *route = doc["route"];
        String body = doc["body"];
        router(String(route), String(body));
    }
    catch (...)
    {
        Serial.println(F("[BluetoothApi][request] Request Deserialization Fail!"));
    }
}

void BluetoothApi::router(String route, String body)
{
    Serial.println(F("[BluetoothApi][router] Routing New Request..."));
    if (route == "getConfig")
    {
        StaticJsonDocument<200> payload;
        ConfigData data = config.get();
        payload["wateringType"] = data.wateringType;
        payload["interval"] = data.interval;
        send(payload);
    }
    else if (route == "setConfig")
    {
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, body);
        if (error)
        {
            return;
        }
        config.update(doc["wateringType"], doc["interval"]);
    }
    else if (route == "forceWatering")
    {
        config.setManualStatus(1);
    }
    else
    {
        Serial.println(F("[BluetoothApi][router] Request not valid"));
    }
}