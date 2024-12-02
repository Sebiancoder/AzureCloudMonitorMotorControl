#include <Stepper.h>
#include <Encoder.h>

//motor pins
//motors are designated 1 to 5 from left-most (most significant digit) to right-most (least significant digit)
const int MOTOR1_APLUS_PIN = 23;
const int MOTOR1_AMINUS_PIN = 25;
const int MOTOR1_BPLUS_PIN = 27;
const int MOTOR1_BMINUS_PIN = 29;

const int MOTOR2_APLUS_PIN = 28;
const int MOTOR2_AMINUS_PIN = 26;
const int MOTOR2_BPLUS_PIN = 24;
const int MOTOR2_BMINUS_PIN = 22;

const int MOTOR3_APLUS_PIN = 33;
const int MOTOR3_AMINUS_PIN = 35;
const int MOTOR3_BPLUS_PIN = 37;
const int MOTOR3_BMINUS_PIN = 39;

const int MOTOR4_APLUS_PIN = 32;
const int MOTOR4_AMINUS_PIN = 34;
const int MOTOR4_BPLUS_PIN = 36;
const int MOTOR4_BMINUS_PIN = 38;

const int MOTOR5_APLUS_PIN = 43;
const int MOTOR5_AMINUS_PIN = 45;
const int MOTOR5_BPLUS_PIN = 47;
const int MOTOR5_BMINUS_PIN = 49;

//since for our motors, each step is 1.8 degrees, this means stepping 20 times to rotate to the next digit
const int STEPS_PER_DIGIT = 20;

//number of rotors
const int NUM_ROTORS = 5;

//stepper instances
const Stepper STEPPER_MOTORS[5] = {
  Stepper(STEPS_PER_DIGIT * 10, MOTOR1_APLUS_PIN, MOTOR1_AMINUS_PIN, MOTOR1_BPLUS_PIN, MOTOR1_BMINUS_PIN),
  Stepper(STEPS_PER_DIGIT * 10, MOTOR2_APLUS_PIN, MOTOR2_AMINUS_PIN, MOTOR2_BPLUS_PIN, MOTOR2_BMINUS_PIN),
  Stepper(STEPS_PER_DIGIT * 10, MOTOR3_APLUS_PIN, MOTOR3_AMINUS_PIN, MOTOR3_BPLUS_PIN, MOTOR3_BMINUS_PIN),
  Stepper(STEPS_PER_DIGIT * 10, MOTOR4_APLUS_PIN, MOTOR4_AMINUS_PIN, MOTOR4_BPLUS_PIN, MOTOR4_BMINUS_PIN),
  Stepper(STEPS_PER_DIGIT * 10, MOTOR5_APLUS_PIN, MOTOR5_AMINUS_PIN, MOTOR5_BPLUS_PIN, MOTOR5_BMINUS_PIN)
};

//encoder pins
const int MOTOR1_EA = 2;
const int MOTOR1_EB = 4;
const int MOTOR2_EA = 3;
const int MOTOR2_EB = 5;
const int MOTOR3_EA = 18;
const int MOTOR3_EB = 19;
const int MOTOR4_EA = 9;
const int MOTOR4_EB = 10;
const int MOTOR5_EA = 11;
const int MOTOR5_EB = 12;

const Encoder ENCODERS[5] = {
  Encoder(MOTOR1_EA, MOTOR1_EB),
  Encoder(MOTOR2_EA, MOTOR2_EB),
  Encoder(MOTOR3_EA, MOTOR3_EB),
  Encoder(MOTOR4_EA, MOTOR4_EB),
  Encoder(MOTOR5_EA, MOTOR5_EB),
};

//actual (more or less) rotor positions
int rotorPositions[5] = {0, 0, 0, 0, 0};

//target rotor positions
int targetPositions[5] = {0, 0, 0, 0, 0};

//currCostValue
extern int alarmValue;

void initMotors();
void step(int motor, int steps);
void rotateToNextDigit(int motor);
int readAngle(int motor);
void calcTargetPositions(float currCost);
void sendCurrValue();
void loosenSteppers(); //drive all motor pins low to allow for hand-turning the motors
void setCurrCostToEncoderValues(); //set the currCost variable to the value being read off the encoder

void initMotors() {

  pinMode(MOTOR1_APLUS_PIN, OUTPUT);
  pinMode(MOTOR1_AMINUS_PIN, OUTPUT);
  pinMode(MOTOR1_BPLUS_PIN, OUTPUT);
  pinMode(MOTOR1_BMINUS_PIN, OUTPUT);

  pinMode(MOTOR2_APLUS_PIN, OUTPUT);
  pinMode(MOTOR2_AMINUS_PIN, OUTPUT);
  pinMode(MOTOR2_BPLUS_PIN, OUTPUT);
  pinMode(MOTOR2_BMINUS_PIN, OUTPUT);

  pinMode(MOTOR3_APLUS_PIN, OUTPUT);
  pinMode(MOTOR3_AMINUS_PIN, OUTPUT);
  pinMode(MOTOR3_BPLUS_PIN, OUTPUT);
  pinMode(MOTOR3_BMINUS_PIN, OUTPUT);

  pinMode(MOTOR4_APLUS_PIN, OUTPUT);
  pinMode(MOTOR4_AMINUS_PIN, OUTPUT);
  pinMode(MOTOR4_BPLUS_PIN, OUTPUT);
  pinMode(MOTOR4_BMINUS_PIN, OUTPUT);

  pinMode(MOTOR5_APLUS_PIN, OUTPUT);
  pinMode(MOTOR5_AMINUS_PIN, OUTPUT);
  pinMode(MOTOR5_BPLUS_PIN, OUTPUT);
  pinMode(MOTOR5_BMINUS_PIN, OUTPUT);

}

void step(int motor, int steps) {

  STEPPER_MOTORS[motor - 1].step(steps);

}

void rotateToNextDigit(int motor) {

  step(motor, STEPS_PER_DIGIT);

  //naive guess at what the rotor position should be; for rotors 4 and 5, the only way to determine position, since I broke the encoders :(
  rotorPositions[motor] += 20;

}

int readAngle(int motor) {

  long encoderReading = ENCODERS[motor].read();

  int angle = (encoderReading % 4000);

  if (angle < 0) {

    angle = 4000 + angle;

  }

  angle = (((float) angle) / 4000.0) * 360;

  return angle;

}

void calcTargetPositions(float currCost) {

  int integerized = (int) (currCost * 100);

  for (int i = 0; i < NUM_ROTORS; i++) {

    targetPositions[NUM_ROTORS - 1 - i] = ((integerized / ((int) pow(10, i))) % 10) * 36;

  }

}

void setTargetPositions() {

  for (int i = 0; i < NUM_ROTORS; i++) {

    int degRotate = targetPositions[i] - rotorPositions[i];

    if (degRotate < 0) {

      degRotate = degRotate + 360;

    }

    if (degRotate < 5) {

      degRotate = 0;

    }

    step(i + 1, ((int) (((float) degRotate) / 1.8)));

    rotorPositions[i] = (rotorPositions[i] + degRotate) % 360;

  }

}

void loosenSteppers() {

  digitalWrite(MOTOR1_APLUS_PIN, LOW);
  digitalWrite(MOTOR1_AMINUS_PIN, LOW);
  digitalWrite(MOTOR1_BPLUS_PIN, LOW);
  digitalWrite(MOTOR1_BMINUS_PIN, LOW);

  digitalWrite(MOTOR2_APLUS_PIN, LOW);
  digitalWrite(MOTOR2_AMINUS_PIN, LOW);
  digitalWrite(MOTOR2_BPLUS_PIN, LOW);
  digitalWrite(MOTOR2_BMINUS_PIN, LOW);

  digitalWrite(MOTOR3_APLUS_PIN, LOW);
  digitalWrite(MOTOR3_AMINUS_PIN, LOW);
  digitalWrite(MOTOR3_BPLUS_PIN, LOW);
  digitalWrite(MOTOR3_BMINUS_PIN, LOW);

  digitalWrite(MOTOR4_APLUS_PIN, LOW);
  digitalWrite(MOTOR4_AMINUS_PIN, LOW);
  digitalWrite(MOTOR4_BPLUS_PIN, LOW);
  digitalWrite(MOTOR4_BMINUS_PIN, LOW);

  digitalWrite(MOTOR5_APLUS_PIN, LOW);
  digitalWrite(MOTOR5_AMINUS_PIN, LOW);
  digitalWrite(MOTOR5_BPLUS_PIN, LOW);
  digitalWrite(MOTOR5_BMINUS_PIN, LOW);

}

void setCurrCostToEncoderValues() {

  int value = 0;

  int multiplier = 100;

  for (int i = 0; i < 3; i++) {

    value = value + ((rotorPositions[i] / 36) * multiplier);
    multiplier /= 10;

  }

  alarmValue = value;

}