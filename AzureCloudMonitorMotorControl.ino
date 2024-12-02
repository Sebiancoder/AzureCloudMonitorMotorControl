#include <Wire.h>
#include <Stepper.h>
#include "MotorControlReceiver.h"
#include "MotorController.h"

const int MOTOR_CONTROLLER_I2C_ADDRESS = 8;

//currently set value on display
float currCost = 0.0;

//whether alarm mode is on or off
bool alarmMode = false;

//alarm value set
int alarmValue = 0;

void setup() {
  
  Serial.begin(9600);

  //begin I2C communication with ESP32
  Wire.begin(MOTOR_CONTROLLER_I2C_ADDRESS);
  Wire.onReceive(receiveMessage);
  Wire.onRequest(sendCurrValue);

  //init motor pins
  initMotors();

  //set motor speeds
  for (const Stepper& motor : STEPPER_MOTORS) {

    motor.setSpeed(10);

  }

}

void loop() {
  
  // Serial.print(currCost);
  // Serial.print("----");
  // Serial.print(alarmMode);
  // Serial.println(" ");

  Serial.println("--------------------");
  Serial.println(currCost);

  if (alarmMode) {

    loosenSteppers();

    // for left three rotors, update position based on encoder
    for (int i = 0; i < 3; i++) {

      rotorPositions[i] = readAngle(i);

    }

    setCurrCostToEncoderValues();

    Serial.print("Alarm Value: ");
    Serial.println(alarmValue);

  } else {
    
    calcTargetPositions(currCost);
    setTargetPositions();

    // for left three rotors, update position based on encoder
    for (int i = 0; i < 3; i++) {

      rotorPositions[i] = readAngle(i);

    }

    for (int i = 0; i < 5; i++) {

      Serial.print(targetPositions[i]);
      Serial.print(" ");

    }

    Serial.println();
    
    for (int i = 0; i < 5; i++) {

      Serial.print(rotorPositions[i]);
      Serial.print(" ");

    }

    Serial.println();

  }

  delay(500);

}
