#include <Arduino.h>
#include "task.h"
class Led: public Task
{
private:
    int16_t speed;
    void set_color(bool r, bool g, bool b);
    void setup();
public:
    virtual void run();
    void update_speed(int16_t speed);
};