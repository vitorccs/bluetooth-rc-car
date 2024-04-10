#ifndef DIGITALLED_H
#define DIGITALLED_H
#include <Arduino.h>

class DigitalLed
{
public:
  uint8_t state = LOW;
  DigitalLed(uint8_t pin);
  void turnOn();
  void turnOff();
  bool toggle();
  bool isTurnedOn();

private:
  uint8_t pin;
  void setState(uint8_t state);
};

#endif