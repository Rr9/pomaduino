#include <SevSeg.h>

#include "SevSeg.h"
SevSeg sevseg;

int timer = 0;
int timeNow = 0;
#define eA 2
#define eB 3
volatile int ePos = 0;
bool eASet = false;
bool eBSet = false;


void setup() {
  pinMode(eA, INPUT);
  pinMode(eB, INPUT);
  pinMode(12, INPUT);
  digitalWrite(eA, HIGH);       // turn on pull-up resistor
  digitalWrite(eB, HIGH);       // turn on pull-up resistor
  attachInterrupt(0, encAIsr, CHANGE);
  attachInterrupt(1, encBIsr, CHANGE);

  //Serial.begin(9600);
  
   byte numDigits = 2;
   byte digitPins[] = {0,1};
   byte segmentPins[] = {4, 5, 6, 7, 8, 9, 10, 11};
   bool resistorsOnSegments = false;
   sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
   sevseg.setBrightness(70);
}

void loop() {
  //Serial.println(ePos);
  sevseg.refreshDisplay();
}


void encAIsr() {

  eASet = digitalRead(eA) == HIGH;
  // and adjust counter + if A leads B
  ePos += (eASet != eBSet) ? +1 : -1;
  sevseg.setNumber(ePos,0);
}


void encBIsr() {

  eBSet = digitalRead(eB) == HIGH;
  // and adjust counter + if B follows A
  ePos += (eASet == eBSet) ? +1 : -1;
  sevseg.setNumber(ePos,0);
}




/*void encoderISR(){
  if (digitalRead(eA) == digitalRead(eB)){
    ePos++;
    //sevseg.setNumber(ePos,0);
  }else if(ePos>0){
    ePos--;
    //sevseg.setNumber(ePos,0);
  }

  Serial.println(ePos, DEC);
}*/
