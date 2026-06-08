#ifndef LEDKY_H
#define LEDKY_H

#define NUMPIXELS 328

#define B1_R 192
#define B1_G 0
#define B1_B 0

#define B2_R 0
#define B2_G 192
#define B2_B 0

#define B3_R 0
#define B3_G 144
#define B3_B 48

#define B4_R 156
#define B4_G 36
#define B4_B 0

#define B5_R 144
#define B5_G 0
#define B5_B 48

#define B6_R 0
#define B6_G 0
#define B6_B 192

#define B7_R 60
#define B7_G 60
#define B7_B 60

#define B8_R 120
#define B8_G 72
#define B8_B 0

#define B9_R 96
#define B9_G 0
#define B9_B 96

#define B10_R 108
#define B10_G 60
#define B10_B 24

#define B12_R 0
#define B12_G 72
#define B12_B 120

#define B14_R 132
#define B14_G 24
#define B14_B 36

class ledky {
  public:
    static void init();
    static void display();
    static void debugMode();
    static volatile uint8_t jas;
    static void update(bool reset);
    static void zmenJas(uint16_t i);
    static void reset(bool l1, bool l2);
    static void set(uint16_t index, uint8_t col);
};

#endif
