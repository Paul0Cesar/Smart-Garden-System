#ifndef Config_h
#define Config_h

#include <Preferences.h>

struct ConfigData
{
    String wateringType;
    unsigned int interval;
};

class Config
{
public:
    Config();
    void initialize();
    void update(String wateringType, int interval);
    void setManualStatus(int status);
    int getManualStatus();
    ConfigData get();

private:
    Preferences preferences;
    void open();
    void close();
};
#endif