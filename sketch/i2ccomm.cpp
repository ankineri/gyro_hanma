#include "i2ccomm.h"
#include <Arduino.h>
I2CComm *_i2ccomm;

int16_t readInt16()
{
    uint16_t value = 0;
    value = Wire.read();
    value |= Wire.read() << 8;
    return (int16_t)value;
}

void I2CComm::requestEvent()
{
    Wire.write((uint8_t*)&this->battery_voltage, sizeof(uint16_t));
    Wire.write((uint8_t*)&this->charger_voltage, sizeof(uint16_t));
}

void I2CComm::receiveEvent(int howMany)
{
    if (howMany != 2*sizeof(int16_t))
    {
        return;
    }
    this->left_speed = readInt16();
    this->right_speed = readInt16();
    this->last_received_at = millis();
}

bool I2CComm::areSpeedsValid()
{
    return millis() - last_received_at < I2C_MAX_STALENESS;
}

void I2CComm::init()
{
    _i2ccomm = this;
    Wire.begin(I2C_ADDRESS);
    Wire.onRequest(::requestEvent);
    Wire.onReceive(::receiveEvent);
}

void I2CComm::setVoltages(uint16_t battery_voltage, uint16_t charger_voltage)
{
    this->battery_voltage = battery_voltage;
    this->charger_voltage = charger_voltage;
}

int16_t I2CComm::getLeftSpeed()
{
    return areSpeedsValid() ? left_speed : 0;
}

int16_t I2CComm::getRightSpeed()
{
    return areSpeedsValid() ? right_speed : 0;
}

void requestEvent()
{
    _i2ccomm->requestEvent();
}
void receiveEvent(int howMany)
{
    _i2ccomm->receiveEvent(howMany);
}
