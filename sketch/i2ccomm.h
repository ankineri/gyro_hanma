#pragma once
#include <Wire.h>
#include "sensors.h"
#define I2C_ADDRESS 8
#define I2C_MAX_STALENESS 1000

class I2CComm
{
    uint16_t battery_voltage = 0;
    uint16_t charger_voltage = 0;
    int16_t left_speed = 0;
    int16_t right_speed = 0;
    unsigned long last_received_at = 0;
    void requestEvent();

    void receiveEvent(int howMany);
    bool areSpeedsValid();
    friend void requestEvent();
    friend void receiveEvent(int howMany);

public:
    void init();
    void setVoltages(uint16_t battery_voltage, uint16_t charger_voltage);
    int16_t getLeftSpeed();
    int16_t getRightSpeed();
};
void requestEvent();
void receiveEvent(int howMany);
