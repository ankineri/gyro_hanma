#pragma once
class Task
{
private:
    unsigned long next_run_ms = 0;

protected:
    void sleep(unsigned long ms);
    virtual void run() = 0;

public:
    virtual void step();
    virtual void setup();
};