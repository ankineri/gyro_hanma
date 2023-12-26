#pragma once
#include "task.h"
#include "pinout.h"
#include <Arduino.h>

#define BATTERY_MULTIPLIER (5.0 / 1024.0 * 10000 / 1200)
#define CHARGER_MULTIPLIER (5.0 / 1024.0 * 10000 / 1200)

class Sensors : public ITask
{
    uint16_t battery_value = 0;
    uint16_t charger_value = 0;

public:
    void step();
    void init();
    uint16_t getBatteryVoltage();
    uint16_t getChargerVoltage();
};