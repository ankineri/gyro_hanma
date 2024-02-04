#include <Arduino.h>

#include "task.h"

void Task::sleep(unsigned long ms)
{
    next_run_ms = millis() + ms;
}

void Task::step()
{
    if (millis() >= next_run_ms)
    {
        run();
    }
}

void Task::setup()
{
}
