#include <Wire.h>

extern float currCost;
extern bool alarmMode;
extern int alarmValue;

void receiveMessage(int bytes);
void sendCurrValue();

void receiveMessage(int bytes) {

  //expecting 3 byte message, 2 bytes for cost float, one byte for the alarm mode bool
  if (bytes == 3) {

    byte highByte = Wire.read();
    byte lowByte = Wire.read();
    byte alarmByte = Wire.read();

    // Reconstruct the integer
    currCost = ((highByte << 8) | lowByte) / 100.0;

    alarmMode = (alarmByte == 1);

  }

}

void sendCurrValue() {

  for (int i = 0; i < sizeof(int); i++) {

    byte highByte = (alarmValue >> 8) & 0xFF;
    byte lowByte = alarmValue & 0xFF;

    Wire.write(highByte);
    Wire.write(lowByte);

  }

}