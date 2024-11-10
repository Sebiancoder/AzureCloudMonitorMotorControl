#include <Wire.h>
#include "MotorControlReceiver.h"
#include "MotorController.h"

const int MOTOR_CONTROLLER_I2C_ADDRESS = 8;

//currently set value on display
float currCost = 0.0;

//whether alarm mode is on or off
bool alarmMode = false;

void setup() {
  
  Serial.begin(9600);

  //begin I2C communication with ESP32
  Wire.begin(MOTOR_CONTROLLER_I2C_ADDRESS);
  Wire.onReceive(receiveMessage);

  //init motor pins
  initMotors();

}

void loop() {
  
  Serial.print(currCost);
  Serial.print("----");
  Serial.print(alarmMode);
  Serial.println(" ");

  rotateToNextDigit(1, 10);

  delay(1000);

}
