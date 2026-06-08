#ifndef PREHRAVAC_H
#define PREHRAVAC_H

class prehravac {
  public:
    static void init();
    static void play(uint8_t index);
    static void precistZastavku(uint8_t zastavka, uint8_t flags);
    static void precistLinku(uint8_t linka, uint8_t zastavka);
};

#endif
