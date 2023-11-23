#include <Arduino.h>
#include <DCMotor.h>

DCMotor::DCMotor(uint8_t pinEn,
                 uint8_t pinIn1,
                 uint8_t pinIn2)
{
    this->pinEn = pinEn;
    this->pinIn1 = pinIn1;
    this->pinIn2 = pinIn2;

    pinMode(this->pinEn, OUTPUT);
    pinMode(this->pinIn1, OUTPUT);
    pinMode(this->pinIn2, OUTPUT);
}

/** Speed must be between 0 and 100 */
void DCMotor::backward(uint8_t speed)
{
    setSpeed(speed);
    digitalWrite(this->pinIn1, HIGH);
    digitalWrite(this->pinIn2, LOW);
}

/** Speed must be between 0 and 100 */
void DCMotor::forward(uint8_t speed)
{
    setSpeed(speed);
    digitalWrite(this->pinIn1, LOW);
    digitalWrite(this->pinIn2, HIGH);
}

void DCMotor::setSpeed(uint8_t speed)
{
    this->absSpeed = map(speed, 0, 100, 0, this->maxAbsSpeed);

    if (this->absSpeed <= this->ignoreAbsSpeed)
    {
        this->absSpeed = 0;
    }

    if (this->absSpeed > 0 && this->absSpeed <= this->minAbsSpeed)
    {
        this->absSpeed = minAbsSpeed;
    }

    analogWrite(this->pinEn, this->absSpeed);
}

void DCMotor::setMinAbsSpeed(uint8_t absSpeed)
{
    this->minAbsSpeed = absSpeed;
}

void DCMotor::stop()
{
    setSpeed(0);
    digitalWrite(this->pinIn1, LOW);
    digitalWrite(this->pinIn2, LOW);
}