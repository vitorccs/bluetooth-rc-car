# Bluetooth RC Car
Bluetooth Remote Controlled Car using Arduino Nano board v3. 

<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/d4cf7d09-89ce-4f19-b74a-7290a47bce9b" width="400">

<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/032b06c2-c130-4dad-81ca-7079a3e00abb" width="400">

## Description
This is a [Platform IO IDE](https://platformio.org/platformio-ide) project coded in C++. 

The car is controlled by a [free Android App](https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en) (Bluettoh connection will appear as "HC-05"):

![BluetoohRcCar_bb](https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/a932c96f-a2e9-4fb0-92e2-317c30f7adb8)
Note: the Electrolytic Capacitor is used to prevent Arduino Nano from rebooting when DC Motors consume more current and causes a voltage drop.

## Components
* 01 - 4WD Car Chassis with steering (see section below)
* 04 - DC Motors (3v - 6v)
* 04 - Wheels
* 01 - Arduino Nano v3
* 01 - [Arduino Nano shield](https://www.aliexpress.us/item/2251801857885983.html) (recomended, not required)
* 01 - L298N Dual H-Bridge
* 01 - Bluetooth HC-05
* 02 - Red Leds
* 02 - White Leds
* 01 - Passive Buzzer
* 04 - 150 Ω Resistors
* 01 - 1.0 KΩ Resistor
* 01 - 3.3 Ω Resistor
* 01 - 220 Ω Resistor
* 02 - 18650 batteries
* 01 - Battery support
* 01 - SG90 Servo Motor
* 01 - Electrolytic Capacitor 1000 μF (6.3v - 25v)

## About PlatformIO IDE
Platform IO is a plugin for Microsoft Virtual Studio Code. It is a more robust IDE compared to official Arduino IDE. It also allows us to easily create our own private libraries and use a more object oriented code.

## About Car Chassis
This project was designed to have a servo motor steeting the front wheels:

## About the code
The PINs can be customized in the `main.cpp` 
```c++
#include <Arduino.h>
#include <DigitalLed.h>
#include <PassiveBuzzer.h>
#include <DCMotor.h>
#include <Car.h>
#include <BluetoothJoyHandler.h>
#include <SoftwareSerial.h>
#include <ServoMotor.h>
#include <Servo.h>

#define PIN_FLED A5 // converted to a Digital Port
#define PIN_RLED A4 // converted to a Digital Port
#define PIN_HORN 10
#define PIN_M1_EN 5
#define PIN_M1_IN1 4
#define PIN_M1_IN2 6
#define PIN_M2_EN 9
#define PIN_M2_IN1 7
#define PIN_M2_IN2 8
#define PIN_BLUETOOTH_TX 12
#define PIN_BLUETOOTH_RX 13
#define PIN_SERVO 11
#define MIN_MOTOR_SPEED 80 // (between 0 to 255)

DigitalLed fLed(PIN_FLED);
DigitalLed rLed(PIN_RLED);
PassiveBuzzer horn(PIN_HORN);
DCMotor motor1(PIN_M1_EN, PIN_M1_IN1, PIN_M1_IN2);
DCMotor motor2(PIN_M2_EN, PIN_M2_IN1, PIN_M2_IN2);
Servo servo;
ServoMotor servoMotor(servo, PIN_SERVO);
Car car(motor1, motor2, fLed, rLed, servoMotor, horn);
SoftwareSerial bluetooth(PIN_BLUETOOTH_TX, PIN_BLUETOOTH_RX);
BluetoothJoyHandler joyHandler(car);

void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);

    servo.attach(PIN_SERVO);

    car.stop();
}

void loop()
{
    if (bluetooth.available() > 0)
    {
        joyHandler.handle(bluetooth.read());
    }
}
```

Fine tuned customizations can be done in the individual files like `ServoMotor.h`
```c++
#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H
#include <Arduino.h>
#include <Servo.h>

class ServoMotor
{
public:
  ServoMotor(Servo &servo, uint8_t pin);
 // void attach();
  void turn(uint16_t angle);
  void turnLeft();
  void turnHalfLeft();
  void turnRight();
  void turnHalfRight();
  void reset();

private:
  uint8_t pin;
  Servo _servo;
  uint8_t angleReset = 90;
  uint8_t angleFull = 25;
  uint8_t angleHalf = 15;
};

#endif
```

### Reference 1 (International):
<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/5a65ca40-7e99-4db5-8cd8-4550874b3d62" width="300">

https://www.aliexpress.us/item/2251832846243463.html?channel=facebook

### Reference 2 (Brazil):
<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/d42e3eee-127e-4b12-b4ab-0122fffeed5c" width="300">

https://www.usinainfo.com.br/kit-robotica/chassi-carrinho-arduino-mdf-com-eixo-movel-v2-manual-de-montagem-5532.html



## Fritzing file
[BluetoohRcCar.zip](https://github.com/vitorccs/bluetooth-rc-car/files/12842007/BluetoohRcCar.zip)

