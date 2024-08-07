# Bluetooth RC Car
Bluetooth Remote Controlled Car using Arduino Nano v3 board. 

<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/c28659e8-4a21-4e9c-bf2e-5e1d1da0a0b4" width="400">

<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/e116b1a2-e75f-4761-9fa6-8965506df705" width="400">


## Recording
Note: enable the sound by clicking on the speaker icon from the video toolbar


https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/5b10d8bd-b947-42eb-8aeb-4d8697c9ae02

## Schematics
This is a [Platform IO IDE](https://platformio.org/platformio-ide) project coded in C++. 

![BluetoothRcCar_v3_bb](https://github.com/user-attachments/assets/a84d260e-dfef-4970-a6aa-2d521dc71ecb)


## Bluetooth controller
The car is controlled by a [free Android App](https://play.google.com/store/apps/details?id=com.electro_tex.bluetoothcar&pcampaignid=web_share) (Bluetooth connection is displayed as "HC-05"):
<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/93d25180-f532-4717-aa7c-2c25e38c2414" width="500">

Once installed the app, map the buttons code as shown below:

<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/4e0d08ae-a4e4-4613-90cf-5a586280fb27" width="500">

## Components
* 01 - 4WD Car Chassis with steering (see section below)
* 04 - DC Motors (3v - 6v)
* 04 - Wheels
* 01 - Arduino Nano v3
* 01 - [Arduino Nano shield](https://www.aliexpress.us/item/2251801857885983.html) (recomended, not required)
* 01 - L298N Dual H-Bridge board
* 01 - HC-05 Bluetooth module
* 02 - Red Leds
* 02 - White Leds
* 01 - Passive Buzzer
* 04 - 150 Ω Resistors
* 01 - 1.0K Ω Resistor
* 01 - 3.3K Ω Resistor
* 01 - 220 Ω Resistor
* 02 - 18650 batteries (3.7v - 4.2v)
* 02 - Battery support
* 01 - SG90 Servo Motor
* 02 - Electrolytic Capacitor 6800 μF (9v - 50v)

NOTES:
* You can also use TB6612FNG as H-Bridge, a modern MOSFET driver with about 90% energy efficiency versus 40-70% for the L298N
* You can increase car speed by adding an extra 18650 battery

## About PlatformIO IDE
Platform IO is a plugin for Microsoft Virtual Studio Code. It is a more robust IDE compared to official Arduino IDE. It also allows us to easily create our own private libraries and use a more object oriented code.

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
#include <SerialReader.h>

#define PIN_FLED 2
#define PIN_RLED 3
#define PIN_HORN 10
#define PIN_M1_EN 5
#define PIN_M1_IN1 4
#define PIN_M1_IN2 6
#define PIN_M2_EN 11
#define PIN_M2_IN1 7
#define PIN_M2_IN2 8
#define PIN_BLUETOOTH_TX 12
#define PIN_BLUETOOTH_RX 13
#define PIN_SERVO 9
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
SerialReader serialReader;

void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);

    servoMotor.attach();
    
    joyHandler.setDebug(false);

    car.stop();
    car.setMaxSpeed();
}

void loop()
{
    String command = serialReader.read(bluetooth);
    if (command != "") {
        joyHandler.handle(command);
    }
}
```

Fine-tuning customizations can be done in the individual files like `ServoMotor.h` for servo motor angle
```c++
#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H
#include <Arduino.h>
#include <Servo.h>

class ServoMotor
{
public:
  ServoMotor(Servo &servo, uint8_t pin);
  void attach();
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

or in the `DCMotor.h` for changing speed parameters
```c++
#ifndef DCMOTOR_H
#define DCMOTOR_H
#include <Arduino.h>

class DCMotor
{
public:
    DCMotor(uint8_t pinEn, uint8_t pinIn1, uint8_t pinIn2);
    void backward(uint8_t speed = 100);
    void forward(uint8_t speed = 100);
    void setMinAbsSpeed(uint8_t absSpeed);
    void stop();

private:
    uint8_t pinEn;
    uint8_t pinIn1;
    uint8_t pinIn2;
    uint8_t absSpeed = 0;
    uint8_t maxAbsSpeed = 255;
    uint8_t minAbsSpeed = 50;
    uint8_t ignoreAbsSpeed = 30;

    void setSpeed(uint8_t speed);
};

#endif
```

## About Car Chassis
This project was designed to have a servo motor steering the front wheels:

### Reference 1 (International):
<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/fc44181b-09c9-459d-bb90-3e725720ff7c" width="300">

https://www.aliexpress.us/item/2251832846243463.html?channel=facebook

### Reference 2 (Brazil):
<img src="https://github.com/vitorccs/bluetooth-rc-car/assets/9891961/6d2626ba-d2ef-4a6d-9c85-598381214e7b" width="300">

https://www.usinainfo.com.br/kit-robotica/chassi-carrinho-arduino-mdf-com-eixo-movel-v2-manual-de-montagem-5532.html

## About the Power Supply
I recommend to use high quality 18650 batteries (3.7v - 4.2v, 2200mAh, at least 2C of discharge rate).

Most people prefer to use different power sources for Arduino (5v) and Bridge driver (6 - 35v). 

I preferred to have a single power source and thus a single power switch. However, it was required to use huge Electrolytic Capacitors (around 12,000µF) to prevent Arduino Nano from rebooting when the bridge drains too much power and also to filter the electric noise.

It is up to you!

## About the Servo Motor
Be careful if you need to change PINs of PWM motors (`PIN_M1_EN` and `PIN_M2_EN`) and Servo (`PIN_SERVO`) since they cannot use the same Arduino timers.
* [Discussion in Arduino forum](https://forum.arduino.cc/t/problem-using-both-a-dc-motor-and-servo/1172917/13)
* [Arduino timers](https://devboards.info/boards/arduino-nano)


## Fritzing file
The eletronic schematic was created in the [Fritzing](https://fritzing.org/) software and can be downloaded at

[BluetoothRcCar_v3.zip](https://github.com/user-attachments/files/16517847/BluetoothRcCar_v3.zip)
