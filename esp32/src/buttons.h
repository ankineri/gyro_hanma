#pragma once
#include <Arduino.h>
#include "task.h"
#include "pinout.h"
#include "gear_state.h"


class Buttons: public Task {
    private:
        bool pedal_pressed = false;
        GearState gear_state = GearState::FORWARD;

        void run();
        void setup();
    public:
        bool is_pedal_pressed();
        GearState get_gear_state();
};