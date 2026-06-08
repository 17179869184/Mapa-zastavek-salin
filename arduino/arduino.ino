#include "globalni.h"

void setup() {
  USB::init();
  prehravac::init();
  ledky::init();
  displej::init();
  UI::init();
}

void loop() {
  if (UI::mod == 5) {
    ledky::debugMode();
  }
  UI::update();
  if (Serial.available()) {
    USB::parse();
  }
}
