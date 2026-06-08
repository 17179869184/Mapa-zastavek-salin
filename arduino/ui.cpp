#include "globalni.h"

volatile unsigned long lastPressTime;
volatile bool canScan;
volatile uint8_t UI::nastaveni;
volatile uint8_t UI::mod;

void disable() {
  lastPressTime = millis();
  canScan = false;
  pinWriteLow(4);
}

void t1() {
  if (digitalRead(3) == LOW) {
    UI::mod = 5;
    UI::nastaveni = 0;
    USB::stop();
    return;
  }
  if (!canScan) return;
  disable();
  UI::nastaveni = (UI::nastaveni + 1) % 2;
  displej::update();
}

void t2() {
  if (digitalRead(2) == LOW) {
    UI::mod = 5;
    UI::nastaveni = 0;
    USB::stop();
    return;
  }
  if (!canScan) return;
  disable();
  if (UI::nastaveni == 1) {
    if (ledky::jas == 100) ledky::jas = 50;
    else if (ledky::jas == 50) ledky::jas = 25;
    else if (ledky::jas == 25) ledky::jas = 100;
    for (int i = 0; i < 328; i++) {
      ledky::zmenJas(i);
    }
  }
  ledky::display();
  displej::update();
}

void scan() {
  for (int r = 0; r < 10; r++) {
    pinWriteLow(22 + r);
    for (int c = 0; c < 15; c++) {
      if (digitalRead(32 + c) == LOW) {
        disable();
        uint8_t zastavka = tlacitkoNaZastavku(r, c);
        Serial.println(zastavka);
        prehravac::precistZastavku(tlacitkoNaZastavku(r, c) + (zastavka > VOJTOVA ? 0 : 1), 0);
      }
    }
    pinWriteHigh(22 + r);
  }
}

void UI::update() {
  if (!canScan && millis() - lastPressTime > 250) {
    canScan = true;
    pinWriteHigh(4);
  }
  if (canScan) {
    scan();
  }
}

void UI::init() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), t1, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), t2, FALLING);
  pinMode(4, OUTPUT);
  pinWriteHigh(4);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(42, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);
  pinWriteHigh(22);
  pinWriteHigh(23);
  pinWriteHigh(24);
  pinWriteHigh(25);
  pinWriteHigh(26);
  pinWriteHigh(27);
  pinWriteHigh(28);
  pinWriteHigh(29);
  pinWriteHigh(30);
  pinWriteHigh(31);
  lastPressTime = 0;
  canScan = true;
}
