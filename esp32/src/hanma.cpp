#include <Wire.h>

#include "hanma.h"
#include "pinout.h"

#define Wire ERROR

#define BATTERY_MULTIPLIER (5.0 / 1024.0 * 10000 / 1200 * 39.8 / 32.3)
#define CHARGER_MULTIPLIER (5.0 / 1024.0 * 10000 / 1200)
// #define Wire1 TheWire
// SoftWire Wire1(PIN_SDA, PIN_SCL);

void Hanma::send(int16_t speed)
{
    int32_t speed32 = speed;
    uint16_t speed16 = speed32 + 0x8000;
    Wire1.beginTransmission(0x08);
    Wire1.write(speed16 & 0xFF);
    Wire1.write(speed16 >> 8);

    // Wire1.write(speed16 &0xFF);
    // Wire1.write(speed16 >> 8);

    uint16_t neg_speed = (-speed32) + 0x8000;

    Wire1.write(speed16 & 0xFF);
    Wire1.write(speed16 >> 8);
    // neg_speed = 0x8000;
    // Wire1.write(neg_speed &0xFF);
    // Wire1.write(neg_speed >> 8);

    Wire1.write(acceleration & 0xFF);
    Wire1.write(acceleration >> 8);
    Wire1.endTransmission();
    // Serial.print("Sent ");
    // Serial.print(speed);
    // Serial.print(", ");
    // Serial.print(neg_speed);
    // Serial.print(", ");
    // Serial.println(acceleration);
}

void Hanma::run()
{
    send(speed);
    read_voltages();
    this->sleep(100);
}

void Hanma::read_voltages()
{
    if (Wire1.available() > 4)
    {
        while (Wire1.available())
        {
            Wire1.read();
        }
    }
    if (Wire1.available() == 4)
    {
        uint16_t ints[2];
        Wire1.readBytes((uint8_t *)ints, 4);
        charger_voltage = ints[0];
        battery_voltage = ints[1];

        last_voltage_read = millis();
    }
    Wire1.requestFrom(0x08, 4);
}

int16_t Hanma::get_speed()
{
    return speed;
}

int16_t Hanma::get_acceleration()
{
    return acceleration;
}

void Hanma::set_speed(int16_t speed)
{
    this->speed = speed;
}

void Hanma::set_acceleration(int16_t acceleration)
{
    this->acceleration = acceleration;
}

void Hanma::setup()
{
    Wire1.begin(PIN_SDA, PIN_SCL, 1000UL);
    Wire1.setTimeOut(100);
    // Wire1.enablePullups();
    // Wire1.setClock(1000UL);
}

unsigned long Hanma::get_voltages_age()
{
    return millis() - last_voltage_read;
}

float Hanma::get_battery_voltage()
{
    return battery_voltage * BATTERY_MULTIPLIER;
}

float Hanma::get_charger_voltage()
{
    return charger_voltage * CHARGER_MULTIPLIER;
}