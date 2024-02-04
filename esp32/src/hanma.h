#pragma once
#include <Arduino.h>
#include "task.h"

extern int16_t speed;

class Hanma: public Task {
    private:
        int16_t acceleration = 100;
        int16_t speed = 0;
        void send(int16_t speed);
        void run();
    public:
        int16_t get_speed();
        int16_t get_acceleration();
        void set_speed(int16_t speed);
        void set_acceleration(int16_t acceleration);
        void setup();
};