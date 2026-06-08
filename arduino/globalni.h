#pragma once
#include <Arduino.h>
#include "displej.h"
#include "ledky.h"
#include "prehravac.h"
#include "zastavky.h"
#include "usb.h"
#include "ui.h"

#define pinWriteLow(p) \ 
  ((p) == 4 ? PORTG &= ~(1 << 5) : \
  ((p) == 7 ? PORTH &= ~(1 << 4) : \
  ((p) == 8 ? PORTH &= ~(1 << 5) : \
  ((p) == 22 ? PORTA &= ~(1 << 0) : \
  ((p) == 23 ? PORTA &= ~(1 << 1) : \
  ((p) == 24 ? PORTA &= ~(1 << 2) : \
  ((p) == 25 ? PORTA &= ~(1 << 3) : \
  ((p) == 26 ? PORTA &= ~(1 << 4) : \
  ((p) == 27 ? PORTA &= ~(1 << 5) : \
  ((p) == 28 ? PORTA &= ~(1 << 6) : \
  ((p) == 29 ? PORTA &= ~(1 << 7) : \
  ((p) == 30 ? PORTC &= ~(1 << 7) : \
  ((p) == 31 ? PORTC &= ~(1 << 6) : \
  0)))))))))))))
#define pinWriteHigh(p) \ 
  ((p) == 4 ? PORTG |= (1 << 5) : \
  ((p) == 7 ? PORTH |= (1 << 4) : \
  ((p) == 8 ? PORTH |= (1 << 5) : \
  ((p) == 22 ? PORTA |= (1 << 0) : \
  ((p) == 23 ? PORTA |= (1 << 1) : \
  ((p) == 24 ? PORTA |= (1 << 2) : \
  ((p) == 25 ? PORTA |= (1 << 3) : \
  ((p) == 26 ? PORTA |= (1 << 4) : \
  ((p) == 27 ? PORTA |= (1 << 5) : \
  ((p) == 28 ? PORTA |= (1 << 6) : \
  ((p) == 29 ? PORTA |= (1 << 7) : \
  ((p) == 30 ? PORTC |= (1 << 7) : \
  ((p) == 31 ? PORTC |= (1 << 6) : \
  0)))))))))))))
