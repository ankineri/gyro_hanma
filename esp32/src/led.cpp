#include "led.h"

void Led::set_color(bool r, bool g, bool b)
{
    digitalWrite(LED_R_GPIO, r);
    digitalWrite(LED_G_GPIO, g);
    digitalWrite(LED_B_GPIO, b);
}

void Led::setup()
{
    pinMode(LED_R_GPIO, OUTPUT);
    pinMode(LED_G_GPIO, OUTPUT);
    pinMode(LED_B_GPIO, OUTPUT);
}

void Led::run()
{
    if (speed > 0)
    {
        set_color(true, false, false);
    }
    else if (speed < 0)
    {
        set_color(false, true, false);
    }
    else
    {
        set_color(false, false, true);
    }
}

void Led::update_speed(int16_t speed)
{
    this->speed = speed;
    step();
}
