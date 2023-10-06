#include <Arduino.h>
#include <ServoMotor.h>
#include <Servo.h>

ServoMotor::ServoMotor(Servo &servo, uint8_t pin): _servo(servo)
{
    this->pin = pin;
    this->_servo = servo;
}

void ServoMotor::turn(uint16_t angle)
{
    this->_servo.write(angle);
}

void ServoMotor::turnLeft()
{
    this->_servo.write(this->angleReset + this->angleFull);
}

void ServoMotor::turnHalfLeft()
{
    this->_servo.write(this->angleReset + this->angleHalf);
}

void ServoMotor::turnRight()
{
    this->_servo.write(this->angleReset - this->angleFull);
}

void ServoMotor::turnHalfRight()
{
   this->_servo.write(this->angleReset - this->angleHalf);
}

void ServoMotor::reset()
{
    this->_servo.write(this->angleReset);
}
