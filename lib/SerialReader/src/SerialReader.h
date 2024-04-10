#ifndef SERIALREADER_H
#define SERIALREADER_H
#include <SoftwareSerial.h>

class SerialReader
{
public:
    String read(SoftwareSerial &bluetooth);

private:
    char terminator = '\n';
};

#endif