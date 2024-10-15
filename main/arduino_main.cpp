// Bare minimum code for spinning motors triggered by controller input

// Assumes servo is connected to pin 15

// Assumes motor controller IN1 and IN2 are connected to pins 14 and 12

#include "sdkconfig.h"
#ifndef CONFIG_BLUEPAD32_PLATFORM_ARDUINO
#error "Must only be compiled when using Bluepad32 Arduino platform"
#endif  !CONFIG_BLUEPAD32_PLATFORM_ARDUINO
#include <Arduino.h>
#include <Bluepad32.h>
#include <ESP32Servo.h>
#include <bits/stdc++.h>
#include <ESP32SharpIR.h>
#include <QTRSensors.h>
#include <Arduino_APDS9960.h>
#include <Wire.h>


#define IN1 4
#define IN2 16
#define ENA 17
#define IN3 5
#define IN4 18
#define ENB 19
#define APDS9960_INT 2
#define I2C_SDA 21
#define I2C_SCL 22
#define I2C_FREQ 100000

TwoWire I2C_0 = TwoWire(0);
APDS9960 apds = APDS9960(I2C_0, APDS9960_INT);

int joyX;
int joyY;
int mode = 1;
Servo servo;

GamepadPtr myGamepads[BP32_MAX_GAMEPADS];

// This callback gets called any time a new gamepad is connected.
void onConnectedGamepad(GamepadPtr gp) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myGamepads[i] == nullptr) {
            myGamepads[i] = gp;
            foundEmptySlot = true;
            break;
        }
    }
}

void onDisconnectedGamepad(GamepadPtr gp) {
    bool foundGamepad = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myGamepads[i] == gp) {
            myGamepads[i] = nullptr;
            foundGamepad = true;
            break;
        }
    }
}
//ENA
void rightMotor(int speed){
    if(speed >= 0){
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else if(speed < 0){
    speed = speed*(-1);
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    analogWrite(ENA, speed);
    //Serial.print("Right Motor :: ");
    //Serial.println(speed);
}
//ENB
void leftMotor(int speed){
    
    if(speed >= 0){
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    else if(speed < 0){
        speed = speed*(-1);
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }
    analogWrite(ENB, speed);
    //Serial.print("Left Motor :: ");
    //Serial.println(speed);
}

void colordetect() {
    int r, g, b, a;
    // Wait until color is read from the sensor 
    while (!apds.colorAvailable()) { delay(5); }
    apds.readColor(r, g, b, a);
    // Read color from sensor apds.readColor(r, g, b, a);
    // Print color in decimal 
    Serial.print("RED: ");
    Serial.print(r);
    Serial.print(" GREEN: ");
    Serial.print(g);
    Serial.print(" BLUE: ");
    Serial.print(b);
    Serial.print(" AMBIENT: ");
    Serial.println(a);
    delay(100);
}

void setup() {
    BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
    BP32.forgetBluetoothKeys();
 
    //servo.attach(15);

    // motor controller outputs
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);

    //sets up I2C protocol; no need to worry about how it works, just used to pull info from the color sensor
    I2C_0.begin(I2C_SDA, I2C_SCL, I2C_FREQ);

    //sets up color sensor
    apds.setInterruptPin(APDS9960_INT);
    apds.begin();
   
    Serial.begin(115200);
    joyX = 0;
    joyY = 0;
}

void loop() {
    BP32.update();
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        GamepadPtr controller = myGamepads[i];
        if (controller && controller->isConnected()) {
            if (controller->b()) {
                Serial.println("button A pressed");
                mode = 1;
            }

            if (controller->a()) {
                Serial.println("button B pressed");
                mode = 2;
            }

            if (mode == 1) { //manual control 
            joyX = controller->axisX() / 4;
            joyY = controller->axisY() / 4;
            rightMotor(joyY+joyX);
            leftMotor(joyY-joyX);
            }

            if (mode == 2) { //colordetect mode as placeholder to autonomous stage 1
                colordetect();
            }


           if (controller->l1() == 1) {
                Serial.print("Servo move");
                servo.write(1000);
            }
            if (controller->l1() == 0) {
                Serial.print("Servo stop");
                servo.write(1500);
            }

           /* if(controller->axisRY() > 0) { // negative y is upward on stick
                Serial.println(" DC motor move");
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
            }
            if(controller->axisRY() == 0) { // stop motor 1
                Serial.println(" DC motor stop");
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
            }*/

        }
        vTaskDelay(1);
    }
}            
