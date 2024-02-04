#include "i2ccomm.h"
#include <Arduino.h>
I2CComm *_i2ccomm;

uint16_t readUint16()
{
    uint16_t value = 0;
    value = Wire.read();
    value |= Wire.read() << 8;
    return value;
}

void I2CComm::requestEvent()
{
    uint16_t battery_value = analogRead(PIN_BATTERY_VOLTAGE);
    uint16_t charger_value = analogRead(PIN_CHARGER_VOLTAGE);
    Wire.write((uint8_t*)&battery_value, sizeof(uint16_t));
    Wire.write((uint8_t*)&charger_value, sizeof(uint16_t));
}

void I2CComm::receiveEvent(int howMany)
{
    if (howMany != 3*sizeof(uint16_t))
    {
        return;
    }
    this->left_wheel->setSpeed(readUint16());
    this->right_wheel->setSpeed(readUint16());
    uint16_t acceleration = readUint16();
    this->left_wheel->setAcceleration(acceleration);
    this->right_wheel->setAcceleration(acceleration);
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

void I2CComm::step()
{
    if (!areSpeedsValid())
    {
        this->left_wheel->setSpeed(0x8000);
        this->right_wheel->setSpeed(0x8000);
    }
}

I2CComm::I2CComm(Wheel *left_wheel, Wheel *right_wheel): left_wheel(left_wheel), right_wheel(right_wheel)
{
}

void requestEvent()
{
    _i2ccomm->requestEvent();
}
void receiveEvent(int howMany)
{
    _i2ccomm->receiveEvent(howMany);
}
