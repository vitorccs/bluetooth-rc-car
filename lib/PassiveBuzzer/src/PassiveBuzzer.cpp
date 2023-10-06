#include <Arduino.h>
#include <PassiveBuzzer.h>

PassiveBuzzer::PassiveBuzzer(uint8_t pin)
{
    this->pin = pin;    
    pinMode(this->pin, OUTPUT);
}

void PassiveBuzzer::play(uint16_t frequency) {
    tone(this->pin, frequency);
}

void PassiveBuzzer::playOnce(unsigned long duration, uint16_t frequency) {
    tone(this->pin, frequency, duration);
}

void PassiveBuzzer::stop() {
    noTone(this->pin);
}