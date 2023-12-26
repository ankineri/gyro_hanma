#pragma once

class ITask {
    unsigned long next_time = 0;
public:
    virtual void step() = 0;
    virtual void init();
    bool shouldStep();
protected:
    void sleep(unsigned long ms);
};
