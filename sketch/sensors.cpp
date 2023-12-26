#include "sensors.h"
#include <Arduino.h>

void Sensors::step()
{
    battery_value = analogRead(PIN_BATTERY_VOLTAGE);
    charger_value = analogRead(PIN_CHARGER_VOLTAGE);
    sleep(100);
}

void Sensors::init()
{
    pinMode(PIN_BATTERY_VOLTAGE, INPUT);
    pinMode(PIN_CHARGER_VOLTAGE, INPUT);
    analogReference(DEFAULT);
}

uint16_t Sensors::getBatteryVoltage()
{
    return battery_value;
}

uint16_t Sensors::getChargerVoltage()
{
    return charger_value;
}
