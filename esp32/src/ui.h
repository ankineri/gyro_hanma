#pragma once
#include "gear_state.h"
#include <string>
class Ui {
    public:
    void set_gear_state(GearState gear_state);
    void set_pedal_state(bool pedal_state);
    void error(std::string message);
    void set_battery_voltage(float voltage);
};