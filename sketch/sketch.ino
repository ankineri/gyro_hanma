#include "ss.h"
#include "wheel.h"
#include "i2ccomm.h"
#include "sensors.h"

Wheel left_wheel(PIN_PD5);
Wheel right_wheel(PIN_PD7);
I2CComm i2ccomm(&left_wheel, &right_wheel);

void setup()
{
  left_wheel.init();
  right_wheel.init();
  i2ccomm.init();
  pinMode(PIN_PWR, OUTPUT);

  digitalWrite(PIN_PWR, HIGH);
}
void loop()
{
  if (millis() > 1000) {
    digitalWrite(PIN_PWR, LOW);
  }
  i2ccomm.step();
  right_wheel.step();
  left_wheel.step();
}
