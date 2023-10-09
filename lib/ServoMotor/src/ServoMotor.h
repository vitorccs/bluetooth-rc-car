#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H
#include <Arduino.h>
#include <Servo.h>

class ServoMotor
{
public:
  ServoMotor(Servo &servo, uint8_t pin);
  void attach();
  void turn(uint16_t angle);
  void turnLeft();
  void turnHalfLeft();
  void turnRight();
  void turnHalfRight();
  void reset();

private:
  uint8_t pin;
  Servo _servo;
  uint8_t angleReset = 90;
  uint8_t angleFull = 25;
  uint8_t angleHalf = 15;
};

#endif