#include "globalni.h"

const uint16_t PROGMEM delky[] = {
  1250, 1812, 1531, 1218, 1125, 812, 937, 1187, 968, 750, 1593, 843, 812, 1156, 968, 718, 968, 1375, 1468, 1187, 1187, 843, 1156, 1062, 1093, 812, 1531, 968, 3062, 1062, 1312, 781, 1062, 843, 843, 1375, 937, 1375, 968, 968, 1250, 1281, 1156, 843, 1687, 1406, 1625, 1000, 906, 968, 937, 875, 2093, 1062, 1093, 1312, 1125, 906, 1281, 1250, 1312, 1843, 1437, 968, 1375, 875, 1531, 1000, 1562, 1312, 1531, 1750, 1156, 906, 2500, 1656, 1531, 1812, 1687, 2062, 875, 1500, 1031, 1468, 1093, 1562, 1281, 1156, 1281, 1031, 1531, 1312, 1031, 1062, 1406, 937, 1593, 1187, 1343, 1812, 875, 1093, 1000, 1000, 937, 1312, 1187, 2000, 1531, 2093, 1187, 1281, 1687, 1468, 1218, 937, 843, 1375, 875, 1281, 1500, 906, 1656, 1187, 750, 1437, 2156, 906, 1031, 1250, 968, 968, 875, 1187, 1000, 3312, 2250, 1718, 1406, 1125, 1000, 1375, 1718, 1156, 1437, 1250, 1437, 1437, 1500, 1718, 1125, 1468, 1343, 2531, 2437, 1312, 687, 1187, 2625, 2375, 1156, 500, 843, 968, 625, 562, 531, 656, 531, 968, 875, 593, 656, 718, 1031, 304, 1221
};

void prehravac::init() {
  Serial1.begin(9600);
}

void prehravac::play(uint8_t index) {
  uint8_t packet[10];
  packet[0] = 0x7E;
  packet[1] = 0xFF;
  packet[2] = 0x06;
  packet[3] = 0x03;
  packet[4] = 0x00;
  packet[5] = (index >> 8) & 0xFF;
  packet[6] = index & 0xFF;
  uint16_t checksum = 0;
  for (int i = 1; i < 7; i++) {
    checksum += packet[i];
  }
  checksum = 0xFFFF - checksum + 1;
  packet[7] = (checksum >> 8) & 0xFF;
  packet[8] = checksum & 0xFF;
  packet[9] = 0xEF;
  for (int i = 0; i < 10; i++) {
    Serial1.write(packet[i]);
  }
  delay(pgm_read_word(&delky[index - 1]));
}

void prehravac::precistZastavku(uint8_t zastavka, uint8_t flags) {
  if (zastavka == MODRICE_SMYCKA) zastavka = 147;
  else if (zastavka == MODRICE_TYRSOVA) zastavka = 148;
  else if (zastavka == VOZOVNA_MEDLANKY) zastavka = 149;
  else if (zastavka == VOZOVNA_PISARKY) zastavka = 150;
  play(177);
  if (!(flags & 0b1000)) {
    if (flags & 0b0100) {
      play(zastavka);
      play(153);
      play(155);
    } else {
      play(151);
      play(zastavka);
    }
    if (flags & 0b0010) {
      if (!(flags & 0b0001)) {
        play(161);
      } else {
        play(159);
      }
      play(vZone(zastavka));
    }
  } else {
    play(152);
    play(zastavka);
    if ((flags & 0b0100)) {
      play(153);
      play(154);
    }
    if (flags & 0b0010) {
      play(158);
      if (!(flags & 0b0001)) {
        play(160);
      } else {
        play(159);
      }
      play(vZone(zastavka));
    }
  }
}

void prehravac::precistLinku(uint8_t linka, uint8_t zastavka) {
  if (zastavka == MODRICE_SMYCKA) zastavka = 147;
  else if (zastavka == MODRICE_TYRSOVA) zastavka = 148;
  else if (zastavka == VOZOVNA_MEDLANKY) zastavka = 149;
  else if (zastavka == VOZOVNA_PISARKY) zastavka = 150;
  play(156);
  if (linka == 12) play(175);
  else if (linka == 14) play(176);
  else play(164 + linka);
  play(157);
  play(zastavka + (zastavka > VOJTOVA ? 0 : 1));
}
