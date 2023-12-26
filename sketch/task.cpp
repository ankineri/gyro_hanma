#include "task.h"
#include <Arduino.h>

void ITask::init()
{
}

bool ITask::shouldStep()
{
    return millis() >= next_time;
}

void ITask::sleep(unsigned long ms)
{
    next_time = millis() + ms;
}
