#include <Arduino.h>
#include <BluetoothJoyHandler.h>
#include <SoftwareSerial.h>

BluetoothJoyHandler::BluetoothJoyHandler(Car &car) : _car(car)
{
    _car = car;
}

void BluetoothJoyHandler::handle(String command)
{
    _car.stop();

    debugMovement(command);

    char keyCode = command[0];
    String keyValue = command.substring(1);
    
    switch (keyCode)
    {
    case 'F':
        _car.forward();
        break;
    case 'B':
        _car.backward();
        break;
    case 'L':
        _car.turnLeft();
        break;
    case 'R':
        _car.turnRight();
        break;
    case 'G':
        _car.forwardLeft();
        break;
    case 'I':
        _car.forwardRight();
        break;
    case 'H':
        _car.backwardLeft();
        break;
    case 'J':
        _car.backwardRight();
        break;
    case 'S':
        _car.stop();
        break;
    case 'W':
        _car.frontLightsToggle();
        break;
    case 'U':
        _car.rearLightsToggle();
        break;
    case 'X':
        _car.playHornOnce();
        break;
    case 'M':
        _car.setSpeed(keyValue.toInt());
        break;
    }
}

void BluetoothJoyHandler::setDebug(bool enable)
{
    this->debug = enable;
}

void BluetoothJoyHandler::debugMovement(String command)
{
    if (!this->debug)
    {
        return;
    }

    Serial.print("Received: ");
    Serial.println(command);
}