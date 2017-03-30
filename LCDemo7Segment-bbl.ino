// Mostly borrowed from LedControl Library available at
// https://github.com/wayoda/LedControl

//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;
unsigned long delaytimeshort=100;
unsigned long bigCounter=0;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() {
  lc.setChar(0,7,'a',false);
  delay(delaytimeshort);
  lc.setRow(0,6,0x05);
  delay(delaytimeshort);
  lc.setChar(0,5,'d',false);
  delay(delaytimeshort);
  lc.setRow(0,4,0x1c);
  delay(delaytimeshort);
  lc.setRow(0,3,B00010000);
  delay(delaytimeshort);
  lc.setRow(0,2,0x15);
  delay(delaytimeshort);
  lc.setRow(0,1,0x1D);
  //delay(delaytime*1);
  for(int i=7; i>=0;i--) {
    lc.setChar(0,i,' ',false);
    delay(delaytimeshort);
  }
  lc.clearDisplay(0);
  delay(delaytimeshort);
} 

/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=0;i<9;i++) {
    lc.setDigit(0,7,i,false);
    lc.setDigit(0,6,i+1,false);
    lc.setDigit(0,5,i+2,false);
    lc.setDigit(0,4,i+3,false);
    lc.setDigit(0,3,i+4,false);
    lc.setDigit(0,2,i+5,false);
    lc.setDigit(0,1,i+6,false);
    lc.setDigit(0,0,i+7,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}
void scrollSingleDigit(byte dig, long dtime) {
  for(int i=0; i<8; i++) {
    lc.setDigit(0,i,dig,false);
    delay(dtime);
  }
  for(int i=0; i<8; i++) {
    lc.setChar(0,i,' ',false);
    delay(dtime);
  }
  lc.clearDisplay(0);
  for(int i=7; i>=0; i--) {
    lc.setDigit(0,i,dig,false);
    delay(dtime);
  }
  for(int i=7; i>=0; i--) {
    lc.setChar(0,i,' ',false);
    delay(dtime);
  }
  lc.clearDisplay(0);
  //delay(dtime);
}
void bCounter(long incSpeed) {
  long stepDown;
  while(bigCounter < 100000000) {
    lc.setDigit(0,0,bigCounter%10000000,false);
    stepDown = bigCounter/10000000;
    lc.setDigit(0,1,stepDown%1000000,false);
    stepDown = stepDown/1000000;
    lc.setDigit(0,2,stepDown%100000,false);
    stepDown = stepDown/100000;
    lc.setDigit(0,3,stepDown%10000,false);
    stepDown = stepDown/10000;
    lc.setDigit(0,4,stepDown%1000,false);
    stepDown = stepDown/1000;
    lc.setDigit(0,5,stepDown%100,false);
    stepDown = stepDown/100;
    lc.setDigit(0,6,stepDown%10,false);
    stepDown = stepDown/10;
    lc.setDigit(0,7,stepDown,false);
    bigCounter++;
    //delay(1);
  }
  bigCounter=0;
}

void loop() { 
  writeArduinoOn7Segment();
  writeArduinoOn7Segment();
  writeArduinoOn7Segment();
  writeArduinoOn7Segment();
  //scrollDigits();
  scrollSingleDigit(0,15);
  scrollSingleDigit(1,15);
  scrollSingleDigit(2,15);
  scrollSingleDigit(3,15);
  scrollSingleDigit(4,15);
  scrollSingleDigit(5,15);
  scrollSingleDigit(6,15);
  scrollSingleDigit(7,15);
  scrollSingleDigit(8,15);
  scrollSingleDigit(9,15);
 // bCounter(1);
}
