/* https://github.com/TinkerKit
 Read values from the T000090 LDR Analog Sensor connected to I0, 
 then uses the result to set the brightness on a T010111 LED 
 Module connected on O0. Also prints the values on the 
 serial monitor.

 created 29 Dec. 2008
 Modified 4 Sep 2010
 by Tom Igoe
 modified 7 dec 2010
 by Davide Gomba
 modified on Ded 2011
 by Federico Vanzati
 modified Jun 2013
 by Matteo Loglio<http://matlo.me>

 This example code is in the public domain.
 */

#include <TinkerKit.h>

TKLightSensor ldr(I1);	//create the "ldr" object on port I0
TKPotentiometer pot(I0);
TKButton button(I2);

TKLed ledPot(O3);
TKLed ledButton(O2);		//create the "led" object on port O0
TKLed ledPhotoDark(O5);
TKLed ledPhotoLight(O4);
void setup() {
  // nothing here.
}

void loop() {
  // store the ldr values into a variable called brightnessVal
  int brightnessVal = ldr.read();            
  int brightnessPot = pot.read();
  // set the led brightness
  ledPot.brightness(brightnessPot);       
  if(brightnessVal > 512) {
    ledPhotoDark.off();
    ledPhotoLight.on();
  } else {
    ledPhotoDark.on();
    ledPhotoLight.off();
  }
  if(button.pressed()) {
    ledButton.on();
  }
  if(button.held()) {
    ledButton.off();
    delay(50);
    ledButton.on();
    delay(50);
  }
  if(button.released()) {
    ledButton.off();
  }
  
  // wait 10 milliseconds before the next loop
  delay(10);                    
}
