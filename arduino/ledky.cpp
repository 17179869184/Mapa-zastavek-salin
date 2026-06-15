#include "globalni.h"

uint32_t lastLedUpdateTime;
uint8_t* LEDBuffer1;
uint8_t* port;
uint8_t pin2;
uint8_t LEDBuffer2[328];
volatile uint8_t ledky::jas;

void ledky::init() {
  pinMode(7, OUTPUT);
  pinMode(12, INPUT);
  pinWriteLow(7);
  LEDBuffer1 = malloc(NUMPIXELS * 3);
  port = portOutputRegister(digitalPinToPort(7));
  pin2 = digitalPinToBitMask(7);
  jas = 100;
  memset(LEDBuffer1, 0, NUMPIXELS * 3);
  reset(true, true);
  display();
}

void ledky::reset(bool l1, bool l2) {
  if (l1) memset(LEDBuffer1, 0, NUMPIXELS * 3);
  if (l2) memset(LEDBuffer2, 0, 328);
}

void ledky::update(bool reset) {
  ledky::reset(true, false);
  for (int i = 0; i < 328; i++) {
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
    if (LEDBuffer2[i] == 1) {R = B1_R; G = B1_G; B = B1_B;}
    if (LEDBuffer2[i] == 2) {R = B2_R; G = B2_G; B = B2_B;}
    if (LEDBuffer2[i] == 3) {R = B3_R; G = B3_G; B = B3_B;}
    if (LEDBuffer2[i] == 4) {R = B4_R; G = B4_G; B = B4_B;}
    if (LEDBuffer2[i] == 5) {R = B5_R; G = B5_G; B = B5_B;}
    if (LEDBuffer2[i] == 6) {R = B6_R; G = B6_G; B = B6_B;}
    if (LEDBuffer2[i] == 7) {R = B7_R; G = B7_G; B = B7_B;}
    if (LEDBuffer2[i] == 8) {R = B8_R; G = B8_G; B = B8_B;}
    if (LEDBuffer2[i] == 9) {R = B9_R; G = B9_G; B = B9_B;}
    if (LEDBuffer2[i] == 10) {R = B10_R; G = B10_G; B = B10_B;}
    if (LEDBuffer2[i] == 12) {R = B12_R; G = B12_G; B = B12_B;}
    if (LEDBuffer2[i] == 14) {R = B14_R; G = B14_G; B = B14_B;}
    if (jas == 50) {R = R / 2; G = G / 2; B = B / 2;}
    if (jas == 25) {R = R / 4; G = G / 4; B = B / 4;}
    LEDBuffer1[i*3] = G;
    LEDBuffer1[i*3+1] = R;
    LEDBuffer1[i*3+2] = B;
    if (reset) LEDBuffer2[i] = 0;
  }
  display();
}

void ledky::display() {
  while ((micros() - lastLedUpdateTime) < 300L);
  noInterrupts();
  volatile uint16_t i = NUMPIXELS * 6;
  volatile uint8_t *ptr = LEDBuffer1, b = *ptr++, hi, lo;
  volatile uint8_t counter;

  volatile uint8_t next, bit;
  volatile uint8_t B;

  hi = *port | pin2;
  lo = *port & ~pin2;
  next = lo;
  bit = 8;

  while (i--) {
    bit = 8;

    asm volatile(
        "ldi %[counter], 8\n\t"
        "loop:\n\t"
        "st   %a[port], %[hi]\n\t"
        "sbrc %[byte], 7\n\t"
        "mov  %[next], %[hi]\n\t"
        "dec  %[bit]\n\t"
        "st   %a[port], %[next]\n\t"
        "mov  %[next], %[lo]\n\t"
        "rol  %[byte]\n\t"
        "st   %a[port], %[lo]\n\t"
        "dec %[counter]\n\t"
        "brne loop\n\t"
        "ldi  %[bit], 8\n\t"
        "ld   %[byte], %a[ptr]+\n\t"
        "st   %a[port], %[lo]\n\t"
        "sbiw %[count], 1\n\t"
        : [port]  "+e"(port),
          [byte]  "+r"(b),
          [bit]   "+r"(bit),
          [counter] "+r"(counter),
          [next]  "+r"(next),
          [count] "+w"(i),
          [ptr]   "+e"(ptr)
        : [hi] "r"(hi),
          [lo] "r"(lo)
    );
  };
  interrupts();
  lastLedUpdateTime = micros();
}

void ledky::debugMode() {
  LEDBuffer2[0] = 1;
  LEDBuffer2[1] = 2;
  LEDBuffer2[2] = 3;
  LEDBuffer2[3] = 4;
  LEDBuffer2[4] = 5;
  LEDBuffer2[5] = 6;
  LEDBuffer2[6] = 7;
  LEDBuffer2[7] = 8;
  LEDBuffer2[8] = 9;
  LEDBuffer2[9] = 10;
  LEDBuffer2[10] = 12;
  LEDBuffer2[11] = 14;
  LEDBuffer2[12] = random(1,13);
  if (LEDBuffer2[12] == 12) LEDBuffer2[12] = 14;
  for (int i = NUMPIXELS - 1; i > 11; i--) {
    LEDBuffer2[i] = LEDBuffer2[i - 1];
  }
  update(false);
  if (digitalRead(2)) delay(250);
}

void ledky::set(uint16_t index, uint8_t col) {
  if (index >= 328) return;
  LEDBuffer2[index] = col;
}

void ledky::zmenJas(uint16_t i) {
  LEDBuffer1[i*3] = LEDBuffer1[i*3] * (ledky::jas == 100 ? 4 : 0.5f);
  LEDBuffer1[i*3+1] = LEDBuffer1[i*3+1] * (ledky::jas == 100 ? 4 : 0.5f);
  LEDBuffer1[i*3+2] = LEDBuffer1[i*3+2] * (ledky::jas == 100 ? 4 : 0.5f);
}
