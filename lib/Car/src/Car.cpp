#ifndef CAR_H
#define CAR_H
#include <Arduino.h>
#include <DCMotor.h>
#include <DigitalLed.h>
#include <DigitalLed.h>
#include <Car.h>
#include <PassiveBuzzer.h>

Car::Car(DCMotor &m1,
         DCMotor &m2,
         DigitalLed &fLed,
         DigitalLed &rLed,
         ServoMotor &servoM,
         PassiveBuzzer &fHorn) : motor1(m1),
                                 motor2(m2),
                                 frontLed(fLed),
                                 rearLed(rLed),
                                 servoMotor(servoM),
                                 frontHorn(fHorn)
{
    this->motor1 = m1;
    this->motor2 = m2;
    this->frontLed = fLed;
    this->rearLed = rLed;
    this->servoMotor = servoM;
    this->frontHorn = fHorn;
}

void Car::backward()
{
    this->servoMotor.reset();
    this->motorBackward();
}

void Car::backwardLeft()
{
    this->servoMotor.turnHalfLeft();
    this->motorBackward();
}

void Car::backwardRight()
{
    this->servoMotor.turnHalfRight();
    this->motorBackward();
}

void Car::forward()
{
    this->servoMotor.reset();
    this->motorForward();
}

void Car::forwardLeft()
{
    this->servoMotor.turnHalfLeft();
    this->motorForward();
}

void Car::forwardRight()
{
    this->servoMotor.turnHalfRight();
    this->motorForward();
}

void Car::setSpeed(uint8_t speed)
{
    this->speed = speed;
}

void Car::setMaxSpeed()
{
    this->speed = 100;
}

void Car::frontLightsOn()
{
    this->frontLed.turnOn();
}

void Car::frontLightsOff()
{
    this->frontLed.turnOff();
}

void Car::frontLightsToggle()
{
    this->frontLed.toggle();
}

void Car::motorBackward()
{
    this->motor1.backward(this->speed);
    this->motor2.backward(this->speed);
}

void Car::motorForward()
{
    this->motor1.forward(this->speed);
    this->motor2.forward(this->speed);
}

void Car::rearLightsOn()
{
    this->rearLed.turnOn();
}

void Car::rearLightsOff()
{
    this->rearLed.turnOff();
}

void Car::rearLightsToggle()
{
    this->rearLed.toggle();
}

void Car::playHorn()
{
    this->frontHorn.play(this->frontHornFreq);
}

void Car::playHornOnce()
{
    this->frontHorn.playOnce(this->frontHornDur, this->frontHornFreq);
}

void Car::stopHorn()
{
    this->frontHorn.stop();
}

void Car::setMinAbsSpeed(uint8_t absSpeed)
{
    this->motor1.setMinAbsSpeed(absSpeed);
    this->motor2.setMinAbsSpeed(absSpeed);
}

void Car::turnLeft()
{
    this->servoMotor.turnLeft();
    this->motorForward();
}

void Car::turnRight()
{
    this->servoMotor.turnRight();
    this->motorForward();
}

void Car::stop()
{
    this->motor1.stop();
    this->motor2.stop();
}

#endif