#pragma once
#include <Arduino.h>
#include "task.h"

extern int16_t speed;

class Hanma: public Task {
    private:
        int16_t acceleration = 100;
        int16_t speed = 0;

        uint16_t battery_voltage = 0;
        uint16_t charger_voltage = 0;

        unsigned long last_voltage_read = 0;

        void send(int16_t speed);
        void run();
        void read_voltages();
    public:
        int16_t get_speed();
        int16_t get_acceleration();
        void set_speed(int16_t speed);
        void set_acceleration(int16_t acceleration);
        unsigned long get_voltages_age();
        float get_battery_voltage();
        float get_charger_voltage();
        void setup();
};