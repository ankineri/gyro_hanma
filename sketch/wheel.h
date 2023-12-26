#pragma once

#include "task.h"
#include "ss.h"
#define ACCELERATION 300
class Wheel
{
    int16_t speed = 0;
    int16_t desired_speed = 0;
    unsigned long last_step = 0;
    SoftwareSerial ss;
    void send(uint16_t angle);
public:
    Wheel(int pin_output, int pin_input = 0);

    void setSpeed(int16_t speed);
    virtual void step();
    virtual void init();
};