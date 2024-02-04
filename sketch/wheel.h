#pragma once

#include "ss.h"
class Wheel
{
    uint16_t acceleration = 0;
    int16_t speed = 0;
    int16_t desired_speed = 0;
    unsigned long last_step = 0;
    SoftwareSerial ss;
    void send(uint16_t angle);
public:
    Wheel(int pin_output, int pin_input = 0);

    void setSpeed(uint16_t speed);
    void setAcceleration(uint16_t acceleration);
    virtual void step();
    virtual void init();
};