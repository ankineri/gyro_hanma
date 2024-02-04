#include "wheel.h"
#include <Arduino.h>

void Wheel::send(uint16_t angle)
{
    uint16_t accel = 0x58;
    ss.write9((uint16_t)0x100);

    ss.write9(angle & 0xFF);
    ss.write9(angle >> 8);

    ss.write9(angle & 0xFF);
    ss.write9(angle >> 8);
    bool enabled = millis() > 1500;
    ss.write9((uint16_t)(enabled ? 0x55 : 0xAA));
    // ss.write9(0x55);
    ss.write9(accel);
    ss.write9(accel);
}

Wheel::Wheel(int pin_output, int pin_input) : ss(pin_input, pin_output)
{
}

void Wheel::setSpeed(uint16_t speed)
{
    this->desired_speed = ((int32_t)speed) - 0x8000;
}

void Wheel::setAcceleration(uint16_t acceleration)
{
    this->acceleration = acceleration;
}

void Wheel::step()
{
    if (acceleration == 0) {
        send(0);
        return;
    }
    int16_t diff = (millis() - last_step) * 300 / 1000;
    if (diff > 2)
    {
        last_step = millis();
        if (speed < desired_speed)
        {
            speed += diff;
            if (speed > desired_speed)
            {
                speed = desired_speed;
            }
        }
        else if (speed > desired_speed)
        {
            speed -= diff;
            if (speed < desired_speed)
            {
                speed = desired_speed;
            }
        }
    }
    send(*(uint16_t*)(&speed));
}

void Wheel::init()
{
    ss.begin(25836);
}
