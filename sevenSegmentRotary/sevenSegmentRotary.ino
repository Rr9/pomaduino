#include <SevSeg.h>

#include "SevSeg.h"
SevSeg sevseg;

int timer = 0;
int timeNow = 0;
int timerState = 0; //0-NotStarted, 1-Work, 2-ShrtBreak, 3-LongBreak
#define eA 2
#define eB 3
volatile int ePos = 0;


void setup() {
  pinMode(eA, INPUT_PULLUP);
  //digitalWrite(eA, HIGH);       // turn on pull-up resistor
  pinMode(eB, INPUT_PULLUP);
  //digitalWrite(eB, HIGH);       // turn on pull-up resistor
  attachInterrupt(0, encoderISR, CHANGE);
   //Serial.begin(9600);
  byte numDigits = 2;
  byte digitPins[] = {0,1};
  byte segmentPins[] = {4, 5, 6, 7, 8, 9, 10, 11};
  bool resistorsOnSegments = false;
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(70);
}

void loop() {
  //Serial.write(ePos);
  sevseg.refreshDisplay();
}

void encoderISR(){
  if (digitalRead(eA) == digitalRead(eB) && ePos<100){
    ePos++;
  }else if(ePos>0){
    ePos--;
  }
  sevseg.setNumber(ePos,0);
}
