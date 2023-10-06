#ifndef THECAR_H
#define THECAR_H
#include <Arduino.h>
#include <DCMotor.h>
#include <DigitalLed.h>
#include <PassiveBuzzer.h>
#include <ServoMotor.h>

class Car
{
public:
    Car(DCMotor &m1,
        DCMotor &m2,
        DigitalLed &fLed,
        DigitalLed &rLed,
        ServoMotor &servoM,
        PassiveBuzzer &fHorn);

    void backward();
    void backwardLeft();
    void backwardRight();
    void forward();
    void forwardLeft();
    void forwardRight();
    void frontLightsOn();
    void frontLightsOff();
    void rearLightsOn();
    void rearLightsOff();
    void playHorn();
    void setMinAbsSpeed(uint8_t absSpeed);
    void setSpeed(uint8_t speed);
    void stop();
    void stopHorn();
    void turnLeft();
    void turnRight();

private:
    uint8_t speed = 0;
    DCMotor motor1;
    DCMotor motor2;
    DigitalLed frontLed;
    DigitalLed rearLed;
    ServoMotor servoMotor;
    PassiveBuzzer frontHorn;
    uint16_t frontHornFreq = 500;

    void motorBackward();
    void motorForward();
};
#endif