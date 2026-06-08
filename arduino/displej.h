#ifndef DISPLEJ_H
#define DISPLEJ_H

class displej {
  public:
    static void init();
    static void update();
    static void display();
    static void character(uint8_t x, uint8_t ch);
    static void changeTime(uint8_t hodiny, uint8_t minuty);
};

#endif
