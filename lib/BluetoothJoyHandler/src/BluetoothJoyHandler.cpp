#include <Arduino.h>
#include <BluetoothJoyHandler.h>
#include <SoftwareSerial.h>

BluetoothJoyHandler::BluetoothJoyHandler(Car &car) : _car(car)
{
    _car = car;
}

void BluetoothJoyHandler::handle(int incomingByte)
{
    _car.stop();

    debugMovement(incomingByte);

    switch (incomingByte)
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
    case 'U':
        _car.rearLightsOn();
        break;
    case 'u':
        _car.rearLightsOff();
        break;
    case 'V':
        _car.playHorn();
        break;
    case 'v':
        _car.stopHorn();
        break;
    case 'W':
        _car.frontLightsOn();
        break;
    case 'w':
        _car.frontLightsOff();
        break;
    case '0':
        _car.setSpeed(0);
        break;
    case '1':
        _car.setSpeed(10);
        break;
    case '2':
        _car.setSpeed(20);
        break;
    case '3':
        _car.setSpeed(30);
        break;
    case '4':
        _car.setSpeed(40);
        break;
    case '5':
        _car.setSpeed(50);
        break;
    case '6':
        _car.setSpeed(60);
        break;
    case '7':
        _car.setSpeed(70);
        break;
    case '8':
        _car.setSpeed(80);
        break;
    case '9':
        _car.setSpeed(90);
        break;
    case 'q':
        _car.setSpeed(100);
        break;
    }
}

void BluetoothJoyHandler::setDebug(bool enable)
{
    this->debug = enable;
}

void BluetoothJoyHandler::debugMovement(int incomingByte)
{
    if (!this->debug)
    {
        return;
    }

    Serial.print("Received: ");
    Serial.println(incomingByte);
}