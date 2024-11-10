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

const int MOTOR3_APLUS_PIN = 31;
const int MOTOR3_AMINUS_PIN = 33;
const int MOTOR3_BPLUS_PIN = 35;
const int MOTOR3_BMINUS_PIN = 37;

const int MOTOR4_APLUS_PIN = 30;
const int MOTOR4_AMINUS_PIN = 32;
const int MOTOR4_BPLUS_PIN = 34;
const int MOTOR4_BMINUS_PIN = 36;

const int MOTOR5_APLUS_PIN = 38;
const int MOTOR5_AMINUS_PIN = 40;
const int MOTOR5_BPLUS_PIN = 42;
const int MOTOR5_BMINUS_PIN = 44;

//since for our motors, each step is 1.8 degrees, this means stepping 20 times to rotate to the next digit
const int STEPS_PER_DIGIT = 20;

void initMotors();
void step(int motor, int stepPhase);
void rotateToNextDigit(int motor, int stepDelay);

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

void step(int motor, int stepPhase) {

  //get pins for specified motor
  int aplus_pin = 0;
  int aminus_pin = 0;
  int bplus_pin = 0;
  int bminus_pin = 0;

  switch(motor) {

    case 1:
      aplus_pin = MOTOR1_APLUS_PIN;
      aminus_pin = MOTOR1_AMINUS_PIN;
      bplus_pin = MOTOR1_BPLUS_PIN;
      bminus_pin = MOTOR1_BMINUS_PIN;
      break;
    case 2:
      aplus_pin = MOTOR2_APLUS_PIN;
      aminus_pin = MOTOR2_AMINUS_PIN;
      bplus_pin = MOTOR2_BPLUS_PIN;
      bminus_pin = MOTOR2_BMINUS_PIN;
      break;
    case 3:
      aplus_pin = MOTOR3_APLUS_PIN;
      aminus_pin = MOTOR3_AMINUS_PIN;
      bplus_pin = MOTOR3_BPLUS_PIN;
      bminus_pin = MOTOR3_BMINUS_PIN;
      break;
    case 4:
      aplus_pin = MOTOR4_APLUS_PIN;
      aminus_pin = MOTOR4_AMINUS_PIN;
      bplus_pin = MOTOR4_BPLUS_PIN;
      bminus_pin = MOTOR4_BMINUS_PIN;
      break;
    case 5:
      aplus_pin = MOTOR4_APLUS_PIN;
      aminus_pin = MOTOR4_AMINUS_PIN;
      bplus_pin = MOTOR4_BPLUS_PIN;
      bminus_pin = MOTOR4_BMINUS_PIN;
      break;
    default:
      return;

  }

  switch (stepPhase) {
    case 1:
      digitalWrite(aplus_pin, HIGH); 
      digitalWrite(aminus_pin, LOW);
      digitalWrite(bplus_pin, HIGH); 
      digitalWrite(bminus_pin, LOW);
      break;
    case 2:
      digitalWrite(aplus_pin, LOW); 
      digitalWrite(aminus_pin, HIGH);
      digitalWrite(bplus_pin, HIGH); 
      digitalWrite(bminus_pin, LOW);
      break;
    case 3:
      digitalWrite(aplus_pin, LOW); 
      digitalWrite(aminus_pin, HIGH);
      digitalWrite(bplus_pin, LOW); 
      digitalWrite(bminus_pin, HIGH);
      break;
    case 4:
      digitalWrite(aplus_pin, HIGH); 
      digitalWrite(aminus_pin, LOW);
      digitalWrite(bplus_pin, LOW); 
      digitalWrite(bminus_pin, HIGH);
      break;
  }

}

void rotateToNextDigit(int motor, int stepDelay);

  //rotating to next digit means rotating 36 degrees
  

  int stepPhase = 1;

  for (int i = 0; i < STEPS_PER_DIGIT; i++) {

    step(motor, stepPhase);
    stepPhase = (stepPhase + 1) % 4;
    delay(stepDelay);

  }