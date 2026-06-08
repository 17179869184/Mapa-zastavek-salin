#include "globalni.h"

#define bufferSize 10

char jsonBuffer[bufferSize];
volatile uint16_t jsonBufferIndex;
volatile bool parsedCas;

void USB::init() {
  Serial.begin(9600);
  Serial.setTimeout(5000);
  jsonBufferIndex = 0;
  parsedCas = false;
}

void USB::stop() {
  jsonBufferIndex = 0;
  parsedCas = false;
}

void USB::parse() {
  if (jsonBufferIndex < bufferSize) jsonBuffer[jsonBufferIndex++] = Serial.read();
  if (jsonBuffer[0] == '/') {
    parsedCas = false;
    jsonBufferIndex--;
    ledky::update(true);
  } else if (jsonBufferIndex > 2) {
    uint8_t linka = jsonBuffer[0];
    uint8_t zastavka = jsonBuffer[1];
    uint8_t nastupiste = jsonBuffer[2];
    jsonBufferIndex -= 3;
    if (linka == 0) {
      if (zastavka >= 200) {
        displej::changeTime(zastavka - 200, nastupiste - 20);
        displej::update();
      } else {
        prehravac::precistZastavku(zastavka, nastupiste);
      }
    } else {
      if (nastupiste == 0) {
        prehravac::precistLinku(linka, zastavka);
      }
      ledky::set(najitLedku(zastavka, nastupiste), linka);
    }
  }
}
