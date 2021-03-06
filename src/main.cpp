#include <Arduino.h>
#include "RGBControl.h"

RGBControl * rgbControl;

void setup(void){
  Serial.begin(9600);
  rgbControl = new RGBControl();
  rgbControl->initialize();
  rgbControl->perform();
}

void loop(void){
  rgbControl->handleClient();
}