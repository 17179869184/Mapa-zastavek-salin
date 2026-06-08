#include "globalni.h"

const PROGMEM uint32_t znaky[12] = {
  /*0*/0x6999996,/*1*/0x4C4444E,/*2*/0x691248F,/*3*/0x6912196,/*4*/0x888AF22,/*5*/0xF8E1196,/*6*/0x698E996,/*7*/0xF122444,/*8*/0x6996996,
  /*9*/0x6997196,/*:*/0x80800,/*%*/0xDD264BB
};
uint8_t displayBuffer[8][4];
uint8_t hodiny;
uint8_t minuty;

void displej::character(uint8_t x, uint8_t ch) {
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t row = (pgm_read_dword(&znaky[ch]) >> (i*4)) % 16;
    for (uint8_t j = 0; j < 4; j++) {
      uint8_t module = (x + j) / 8;
      uint8_t col = (x + j) % 8;
      if ((row >> (3-j)) % 2) {
        displayBuffer[i][module] |= (1 << (col));
      } else {
        displayBuffer[i][module] &= ~(1 << (col));
      }
    }
  }
}

void transfer(uint8_t b) {
  SPDR = b;
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}

void displej::display() {
  for (uint8_t r = 0; r < 8; r++) {
    pinWriteLow(8);
    transfer(r + 1);
    transfer(displayBuffer[r][3]);
    transfer(r + 1);
    transfer(displayBuffer[r][2]);
    transfer(r + 1);
    transfer(displayBuffer[r][1]);
    transfer(r + 1);
    transfer(displayBuffer[r][0]);
    pinWriteHigh(8);
  }
}

void displej::update() {
  for (uint8_t r = 0; r < 8; r++) {
    for (uint8_t m = 0; m < 4; m++) {
      displayBuffer[r][m] = 0x00;
    }
  }
  if (UI::nastaveni == 0) {
    displej::character(1, hodiny / 10);
    displej::character(6, hodiny % 10);
    displej::character(11, 10);
    displej::character(13, minuty / 10);
    displej::character(18, minuty % 10);
  } else if (UI::nastaveni == 1) {
    if (ledky::jas == 100) {
      displej::character(1, 1);
      displej::character(6, 0);
      displej::character(11, 0);
      displej::character(16, 11);
    } else {
      displej::character(1, ledky::jas / 10);
      displej::character(6, ledky::jas % 10);
      displej::character(11, 11);
    }
  }
  displej::display();
}

void displej::init() {
  pinMode(8, OUTPUT);
  pinWriteHigh(8);
  DDRB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
  pinWriteLow(8);
  for (int i = 0; i < 4; i++) {transfer(0x0C);transfer(0x01);}
  pinWriteHigh(8);pinWriteLow(8);
  for (int i = 0; i < 4; i++) {transfer(0x0F);transfer(0x00);}
  pinWriteHigh(8);pinWriteLow(8);
  for (int i = 0; i < 4; i++) {transfer(0x0B);transfer(0x07);}
  pinWriteHigh(8);pinWriteLow(8);
  for (int i = 0; i < 4; i++) {transfer(0x0A);transfer(0x08);}
  pinWriteHigh(8);pinWriteLow(8);
  for (int i = 0; i < 4; i++) {transfer(0x09);transfer(0x00);}
  pinWriteHigh(8);
  displej::display();
  hodiny = 99;
  minuty = 99;
}

void displej::changeTime(uint8_t _hodiny, uint8_t _minuty) {
  hodiny = _hodiny;
  minuty = _minuty;
}
