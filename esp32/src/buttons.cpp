#include "buttons.h"

void Buttons::run()
{
    pedal_pressed = digitalRead(PIN_PEDAL) == LOW;
    gear_state = digitalRead(PIN_GEAR) == LOW ? GearState::NEUTRAL : GearState::FORWARD;
}

void Buttons::setup()
{
    pinMode(PIN_PEDAL, INPUT_PULLUP);
    pinMode(PIN_GEAR, INPUT_PULLUP);
}

bool Buttons::is_pedal_pressed()
{
    return pedal_pressed;
}

GearState Buttons::get_gear_state()
{
    return gear_state;
}
