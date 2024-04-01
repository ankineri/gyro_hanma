#include "buttons.h"

void Buttons::run()
{
    pedal_pressed = digitalRead(PIN_PEDAL) == LOW;
    // gear state is bit-encoded, with lower bit being the forward pin value and higher bit being the reverse pin value.
    // if both are pressed, it's an error state.
    byte state = (digitalRead(PIN_GEAR_FAST) ? 0 : 1) | ((digitalRead(PIN_GEAR_REVERSE) ? 0 : 1) << 1);
    gear_state = (GearState)state;
}

void Buttons::setup()
{
    pinMode(PIN_PEDAL, INPUT_PULLUP);
    pinMode(PIN_GEAR_FAST, INPUT_PULLUP);
    pinMode(PIN_GEAR_REVERSE, INPUT_PULLUP);
}

bool Buttons::is_pedal_pressed()
{
    return pedal_pressed;
}

GearState Buttons::get_gear_state()
{
    return gear_state;
}
