#ifndef PASSIVEBUZZER_H
#define PASSIVEBUZZER_H
#include <Arduino.h>

class PassiveBuzzer
{
public:
    PassiveBuzzer(uint8_t pin);
    void play(uint16_t frequency);
    void playOnce(unsigned long duration, uint16_t frequency);
    void stop();

private:
    uint8_t pin;
};

#endif