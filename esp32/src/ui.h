#pragma once
#include "gear_state.h"
#include "web.h"
#include <string>
class Ui {
private:
    const ConfigurableParams& params;
  public:
    Ui(const ConfigurableParams &params);
    void update();
    void set_gear_state(GearState gear_state);
    void set_pedal_state(bool pedal_state);
    void error(std::string message);
    void set_battery_voltage(float voltage);
};