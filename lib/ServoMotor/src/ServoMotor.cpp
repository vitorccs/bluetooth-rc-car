#include <Arduino.h>
#include <ServoMotor.h>
#include <Servo.h>

ServoMotor::ServoMotor(Servo &servo, uint8_t pin): _servo(servo)
{
    this->pin = pin;
    this->_servo = servo;
}

void ServoMotor::attach()
{
    this->_servo.attach(this->pin);
}

void ServoMotor::turn(uint16_t angle)
{
    this->_servo.write(angle);
}

void ServoMotor::turnLeft()
{
    this->_servo.write(this->angleReset + this->angleFull + this->leftOffset);
}

void ServoMotor::turnHalfLeft()
{
    this->_servo.write(this->angleReset + this->angleHalf + this->leftOffset);
}

void ServoMotor::turnRight()
{
    this->_servo.write(this->angleReset - this->angleFull - this->rightOffset);
}

void ServoMotor::turnHalfRight()
{
   this->_servo.write(this->angleReset - this->angleHalf - this->rightOffset);
}

void ServoMotor::reset()
{
    this->_servo.write(this->angleReset);
}
