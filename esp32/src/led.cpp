#include "led.h"
#include "pinout.h"



void Led::set_color(bool r, bool g, bool b)
{
    digitalWrite(PIN_RED, !r);
    digitalWrite(PIN_GREEN, !g);
    digitalWrite(PIN_BLUE, !b);
}

void Led::setup()
{
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
}

void Led::run()
{
    if (speed > 0)
    {
        set_color(false, true, false);
    }
    else if (speed < 0)
    {
        set_color(true, true, false);
    }
    else
    {
        set_color(false, false, true);
    }
}

void Led::error()
{
    set_color(true, false, false);
}

void Led::update_speed(int16_t speed)
{
    this->speed = speed;
    step();
}
