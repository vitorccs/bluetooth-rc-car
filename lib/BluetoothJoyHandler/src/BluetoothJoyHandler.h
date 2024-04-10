#ifndef BLUETOOTHJOYHANDLER_H
#define BLUETOOTHJOYHANDLER_H
#include <Arduino.h>
#include <Car.h>

class BluetoothJoyHandler {
public:
    BluetoothJoyHandler(Car &car);
    void handle(String command);
    void setDebug(bool enable);
private:
    Car &_car;
    bool debug = false;
    void debugMovement(String command);
};

#endif