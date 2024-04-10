#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SerialReader.h>

String SerialReader::read(SoftwareSerial &bluetooth)
{
    char buffer[5];
    size_t numRead = 0;

    while (bluetooth.available() > 0)
    {
        numRead = bluetooth.readBytesUntil(
            this->terminator, 
            buffer, 
            sizeof(buffer) - 1
        );

        buffer[numRead] = '\0';
    }

    if (numRead == 0) {
        return "";
    }

    return String(buffer);
}