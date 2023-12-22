#include "ss.h"
SoftwareSerial ss(2, 3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(27027);
  Serial.begin(115200);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
}
uint16_t buf[16];
uint8_t len = 0;

void send(uint16_t angle, uint16_t accel, bool blocked) {
  ss.write9((uint16_t)0x100);

  ss.write9(angle & 0xFF);
  ss.write9(angle >> 8);

  ss.write9(angle & 0xFF);
  ss.write9(angle >> 8);

  ss.write9((uint16_t)(blocked ? 0x55 : 0xAA));
  ss.write9(accel);
  ss.write9(accel);
}
uint16_t angle = 0;
void loop() {
  // put your main code here, to run repeatedly:
  bool blocked = digitalRead(7);
  if (digitalRead(8) == LOW) {
    auto val = analogRead(A0) / 1024.0 - 0.5;
    // Serial.println(val);
    angle = ((double)0xA00) * 2*val;
    //angle -= 1;
  }else {
    angle = 0;
  }
  Serial.println(angle, HEX);
  //uint16_t angle = digitalRead(8) ? 0 : 0x1111;
  // accel 0x58
  send(angle, 0x40, blocked);
  delayMicroseconds(1000);
  return;
  if (ss.available()) {
    auto value = ss.read();
    // Serial.println(len);
    if (value == 0x100 && len == 7) {
      buf[len++] = value;
      Serial.print(len);
      Serial.print(": ");
      for (int i = 0; i < len; ++i) {
        Serial.print(buf[i], HEX);
        Serial.print(' ');
      }
      Serial.println();
      len = 0;
    }
    else if (value == 0x100 || len > 14) {
      len = 0;
    } else {
      buf[len++] = value;
    }
  }
}
