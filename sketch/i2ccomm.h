#pragma once
#include <Wire.h>
#include "sensors.h"
#include "wheel.h"
#define I2C_ADDRESS 8
#define I2C_MAX_STALENESS 1000

class I2CComm
{
    Wheel* left_wheel;
    Wheel* right_wheel;
    unsigned long last_received_at = 0;
    void requestEvent();

    void receiveEvent(int howMany);
    bool areSpeedsValid();
    friend void requestEvent();
    friend void receiveEvent(int howMany);

public:
    void init();
    void step();
    I2CComm(Wheel* left_wheel, Wheel* right_wheel);
};
void requestEvent();
void receiveEvent(int howMany);
