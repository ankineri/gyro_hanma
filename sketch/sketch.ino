#include "ss.h"
#include "wheel.h"
#include "i2ccomm.h"
#include "sensors.h"

Wheel left_wheel(PIN_PD5);
Wheel right_wheel(PIN_PD7);
I2CComm i2ccomm;
Sensors sensors;

void setup()
{
  left_wheel.init();
  right_wheel.init();
  sensors.init();
  i2ccomm.init();
  pinMode(PIN_PWR, OUTPUT);

  digitalWrite(PIN_PWR, HIGH);
}
void loop()
{
  if (millis() > 1000) {
    digitalWrite(PIN_PWR, LOW);
  }
  right_wheel.step();
  left_wheel.step();
  if (sensors.shouldStep())
  {
    sensors.step();
  }
  {
    uint16_t battery_voltage = sensors.getBatteryVoltage();
    uint16_t charger_voltage = sensors.getChargerVoltage();
    i2ccomm.setVoltages(battery_voltage, charger_voltage);
  }
  left_wheel.setSpeed(i2ccomm.getLeftSpeed());
  right_wheel.setSpeed(i2ccomm.getRightSpeed());
}
