#include <Wire.h>

#include "hanma.h"
#include "pinout.h"

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
    this->sleep(100);
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
    Wire1.begin(PIN_SDA, PIN_SCL);
}
