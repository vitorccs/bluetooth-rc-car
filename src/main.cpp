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