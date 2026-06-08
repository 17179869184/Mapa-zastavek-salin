#include "globalni.h"

const uint8_t r0[15] PROGMEM = {   NEMOCNICE_BOHUNICE,  STARY_LISKOVEC_SMYCKA,       ZAPADNI_BRANA,           DUNAJSKA,                BELORUSKA,         KARPATSKA,             KREMATORIUM,               OSOVA,        ARENA_BRNO,               SVERMOVA,  VYSTAVISTE_VSTUP_G2,             PORICI,               CELNI,  VYSTAVISTE_HLAVNI_VSTUP,  NEMOCNICE_MILOSRDNYCH_BRATRI }; // stary liskovec
const uint8_t r1[15] PROGMEM = {      MORAVANSKE_LANY,         MODRICE_SMYCKA,          MORAVANSKA,    MODRICE_TYRSOVA,  USTREDNI_HRBITOV_SMYCKA,  MODRICKA_CIHELNA,        USTREDNI_HRBITOV,          ORECHOVSKA,         NOVE_SADY,              BOHUNICKA,           SOUKENICKA,            VOJTOVA,             HLUBOKA,              KRIDLOVICKA,                     VSETINSKA }; // modrice
const uint8_t r2[15] PROGMEM = {          HEINRICHOVA,               HYBESOVA,        NAMESTI_MIRU,          VACLAVSKA,               OBILNI_TRH,  MENDLOVO_NAMESTI,  NEMOCNICE_U_SVATE_ANNY,          VSETICKOVA,           GROHOVA,                   UVOZ,                CESKA,  KONECNEHO_NAMESTI,  SILINGROVO_NAMESTI,       KOMENSKEHO_NAMESTI,                           255 }; // namesti miru
const uint8_t r3[15] PROGMEM = {                 UZKA,                KOMAROV,  AUTOBUSOVE_NADRAZI,            KONOPNA,          NAMESTI_SVOBODY,        ZELEZNICNI,                   VLHKA,      HLAVNI_NADRAZI,         KORNEROVA,              ZELNY_TRH,           TKALCOVSKA,   NAMESTI_28_RIJNA,               MASNA,         DETSKA_NEMOCNICE,          MALINOVSKEHO_NAMESTI }; // komarov
const uint8_t r4[15] PROGMEM = {              KRALOVA,              SOCHOROVA,   BURIANOVO_NAMESTI,  ROSICKEHO_NAMESTI,       TECHNOLOGICKY_PARK,           MOZOLKY,        TECHNICKE_MUZEUM,               TABOR,          TEREROVA,                RYBKOVA,           KLUSACKOVA,        DOBROVSKEHO,          CERVINKOVA,                 NERUDOVA,                     SKACELOVA }; // kralovo pole
const uint8_t r5[15] PROGMEM = {         NOVOLISENSKA,                MIFKOVA,            MASAROVA,             JIROVA,                BILA_HORA,         KOTLANOVA,          STRANSKA_SKALA,            LISENSKA,  ZIDOVSKY_HRBITOV,  STRANSKA_SKALA_SMYCKA,           ZIVOTSKEHO,           KRASNEHO,          BELOHORSKA,               GEISLEROVA,                   PODSTRANSKA }; // lisen
const uint8_t r6[15] PROGMEM = {          PRISTAVISTE,                ECEROVA,           RAKOVECKA,        ONDROUSKOVA,                  PODLESI,         KUBICKOVA,                  BRANKA,  ZOOLOGICKA_ZAHRADA,        STRANSKEHO,              KAMENOLOM,              BRAFOVA,      VOZOVNA_KOMIN,           SVRATECKA,                  PISARKY,                  KOMIN_SMYCKA }; // bystrc
const uint8_t r7[15] PROGMEM = {     PROSKOVO_NAMESTI,         OBRANY_BABICKA,    OBRANSKA_U_SKOLY,      OBRANSKY_MOST,        NAMESTI_REPUBLIKY,       CTVERY_HONY,                JULIANOV,    MALOMERICKY_MOST,           BUZKOVA,        TOMKOVO_NAMESTI,              KULDOVA,    OTAKARA_SEVCIKA,        DELNICKY_DUM,       VOJENSKA_NEMOCNICE,                   STARA_OSADA }; // malomerice
const uint8_t r8[15] PROGMEM = { KRALOVO_POLE_NADRAZI,              RECKOVICE,             HUDCOVA,          FILKUKOVA,                 HUSITSKA,         KORISKOVA,             JUNGMANNOVA,              TYLOVA,         PIONYRSKA,              SEMILASSO,           ANTONINSKA,          HRNCIRSKA,          KARTOUZSKA,         MORAVSKE_NAMESTI,                      SUMAVSKA }; // reckovice
const uint8_t r9[15] PROGMEM = {             LESNICKA,          CERTOVA_ROKLE,            BIEBLOVA,   HALASOVO_NAMESTI,                VENHUDOVA,         FUGNEROVA,                TOMANOVA,          ZEMEDELSKA,          MOSTECKA,      STEFANIKOVA_CTVRT,          TRAVNICKOVA,        JUGOSLAVSKA,          ZDRAHALOVA,         VOZOVNA_HUSOVICE,                           255 }; // lesna

uint16_t najitLedku(uint8_t z, uint8_t s) {
  if (z == ANTONINSKA) {
    if (s == 1) return 160;
    if (s == 2) return 188;
  } else if (z == AUTOBUSOVE_NADRAZI) {
    if (s == 1) return 40;
    if (s == 2) return 47;
  } else if (z == OBRANY_BABICKA) {
    if (s == 1) return 101;
    if (s == 2) return 102;
  } else if (z == BELOHORSKA) {
    if (s == 1) return 62;
    if (s == 2) return 77;
  } else if (z == BELORUSKA) {
    if (s == 1) return 323;
    if (s == 2) return 10;
  } else if (z == BIEBLOVA) {
    if (s == 1) return 143;
    if (s == 2) return 150;
  } else if (z == BILA_HORA) {
    if (s == 1) return 63;
    if (s == 2) return 76;
  } else if (z == BOHUNICKA) {
    if (s == 1) return 16;
    if (s == 2) return 29;
  } else if (z == BRAFOVA) {
    if (s == 1) return 254;
    if (s == 2) return 253;
  } else if (z == BRANKA) {
    if (s == 1) return 232;
    if (s == 2) return 249;
  } else if (z == BURIANOVO_NAMESTI) {
    if (s == 1) return 225;
    if (s == 2) return 259;
  } else if (z == BUZKOVA) {
    if (s == 1) return 80;
    if (s == 2) return 87;
  } else if (z == CELNI) {
    if (s == 1) return 321;
    if (s == 2) return 284;
  } else if (z == CERTOVA_ROKLE) {
    if (s == 1) return 146;
    if (s == 2) return 147;
  } else if (z == CERVINKOVA) {
    if (s == 1) return 199;
    if (s == 2) return 216;
  } else if (z == CESKA) {
    if (s == 1) return 264;
    if (s == 2 || s == 6) return 190;
    if (s == 3 || s == 4) return 191;
    if (s == 5) return 276;
  } else if (z == CTVERY_HONY) {
    if (s == 1) return 99;
    if (s == 2) return 104;
  } else if (z == DELNICKY_DUM) {
    if (s == 1) return 82;
    if (s == 2) return 85;
  } else if (z == DETSKA_NEMOCNICE) {
    if (s == 1) return 129;
    if (s == 2) return 156;
  } else if (z == DOBROVSKEHO) {
    if (s == 1) return 197;
    if (s == 2) return 218;
  } else if (z == DUNAJSKA) {
    if (s == 1) return 3;
    if (s == 2) return 6;
  } else if (z == ECEROVA) {
    if (s == 1) return 241;
    if (s == 2) return 242;
  } else if (z == FILKUKOVA) {
    if (s == 1) return 173;
    if (s == 2) return 176;
  } else if (z == FUGNEROVA) {
    if (s == 1) return 144;
    if (s == 2) return 149;
  } else if (z == GEISLEROVA) {
    if (s == 1) return 53;
    if (s == 2) return 113;
  } else if (z == GROHOVA) {
    if (s == 1) return 192;
    if (s == 2) return 263;
  } else if (z == HALASOVO_NAMESTI) {
    if (s == 1) return 145;
    if (s == 2) return 148;
  } else if (z == HEINRICHOVA) {
    return 271;
  } else if (z == HLAVNI_NADRAZI) {
    if (s == 1 || s == 3 || s == 7 || s == 8) return 37;
    if (s == 2 || s == 6) return 116;
    if (s == 4 || s == 5) return 38;
  } else if (z == HLUBOKA) {
    if (s == 1) return 12;
    if (s == 2) return 31;
  } else if (z == HRNCIRSKA) {
    if (s == 1) return 162;
    if (s == 2) return 186;
  } else if (z == HUDCOVA) {
    if (s == 1) return 171;
    if (s == 2) return 178;
  } else if (z == HUSITSKA) {
    if (s == 1) return 166;
    if (s == 2) return 182;
  } else if (z == HYBESOVA) {
    if (s == 1) return 317;
    if (s == 2) return 288;
  } else if (z == JIROVA) {
    if (s == 1) return 68;
    if (s == 2) return 71;
  } else if (z == JUGOSLAVSKA) {
    if (s == 1 || s == 6) return 154;
    if (s == 2 || s == 5) return 130;
    if (s == 3) return 131;
    if (s == 4) return 155;
  } else if (z == JULIANOV) {
    if (s == 1) return 83;
    if (s == 2) return 84;
  } else if (z == VOZOVNA_KOMIN) {
    if (s == 1) return 229;
    if (s == 2) return 251;
  } else if (z == JUNGMANNOVA) {
    if (s == 1) return 165;
    if (s == 2) return 183;
  } else if (z == KAMENOLOM) {
    if (s == 1) return 234;
    if (s == 2) return 247;
  } else if (z == KARPATSKA) {
    if (s == 1) return 2;
    if (s == 2) return 7;
  } else if (z == KARTOUZSKA) {
    if (s == 1) return 164;
    if (s == 2) return 184;
  } else if (z == KLUSACKOVA) {
    if (s == 1) return 195;
    if (s == 2) return 220;
  } else if (z == KOMAROV) {
    if (s == 1) return 43;
    if (s == 2) return 44;
  } else if (z == KOMENSKEHO_NAMESTI) {
    if (s == 1) return 265;
    if (s == 2) return 275;
  } else if (z == KOMIN_SMYCKA) {
    return 230;
  } else if (z == KONECNEHO_NAMESTI) {
    if (s == 1) return 193;
    if (s == 2) return 262;
  } else if (z == KONOPNA) {
    if (s == 1) return 42;
    if (s == 2) return 45;
  } else if (z == KORNEROVA) {
    if (s == 1) return 119;
    if (s == 2) return 123;
  } else if (z == KORISKOVA) {
    if (s == 1) return 172;
    if (s == 2) return 177;
  } else if (z == KOTLANOVA) {
    if (s == 1) return 67;
    if (s == 2) return 72;
  } else if (z == KRALOVA) {
    return 224;
  } else if (z == KRALOVO_POLE_NADRAZI) {
    if (s == 1) return 168;
    if (s == 2) return 169;
  } else if (z == KRASNEHO) {
    if (s == 1) return 55;
    if (s == 2) return 78;
  } else if (z == KREMATORIUM) {
    if (s == 1) return 322;
    if (s == 2) return 11;
  } else if (z == KRIDLOVICKA) {
    if (s == 1) return 281;
    if (s == 2) return 34;
  } else if (z == KUBICKOVA) {
    if (s == 1) return 239;
    if (s == 2) return 244;
  } else if (z == KULDOVA) {
    if (s == 1) return 89;
    if (s == 2) return 90;
  } else if (z == LESNICKA) {
    if (s == 1) return 142;
    if (s == 2) return 151;
  } else if (z == ARENA_BRNO) {
    if (s == 1) return 298;
    if (s == 2 || s == 6) return 309;
  } else if (z == LISENSKA) {
    if (s == 1) return 64;
    if (s == 2) return 75;
  } else if (z == MALINOVSKEHO_NAMESTI) {
    if (s == 1 || s == 4) return 118;
    if (s == 2) return 124;
    if (s == 3) return 125;
  } else if (z == MALOMERICKY_MOST) {
    if (s == 1) return 96;
    if (s == 2) return 95;
  } else if (z == MASAROVA) {
    if (s == 1) return 66;
    if (s == 2) return 73;
  } else if (z == NAMESTI_MIRU) {
    if (s == 1) return 269;
    if (s == 2) return 270;
  } else if (z == MASNA) {
    if (s == 1) return 50;
    if (s == 2) return 114;
  } else if (z == MENDLOVO_NAMESTI) {
    if (s == 1 || s == 4) return 295;
    if (s == 2 || s == 3) return 293;
    if (s == 5 || s == 6) return 294;
  } else if (z == MIFKOVA) {
    if (s == 1) return 69;
    if (s == 2) return 70;
  } else if (z == MODRICKA_CIHELNA) {
    if (s == 1) return 20;
    if (s == 2) return 25;
  } else if (z == MORAVANSKA) {
    if (s == 1) return 19;
    if (s == 2) return 26;
  } else if (z == MORAVANSKE_LANY) {
    if (s == 1) return 18;
    if (s == 2) return 27;
  } else if (z == MORAVSKE_NAMESTI) {
    if (s == 1) return 159;
    if (s == 2) return 127;
    if (s == 3) return 158;
    if (s == 4) return 189;
  } else if (z == MOSTECKA) {
    if (s == 1) return 110;
    if (s == 2) return 133;
  } else if (z == MOZOLKY) {
    if (s == 1) return 226;
    if (s == 2) return 258;
  } else if (z == NAMESTI_28_RIJNA) {
    if (s == 1) return 128;
    if (s == 2) return 157;
  } else if (z == NAMESTI_REPUBLIKY) {
    if (s == 1) return 93;
    if (s == 2) return 108;
  } else if (z == NAMESTI_SVOBODY) {
    if (s == 1) return 277;
    if (s == 2) return 126;
  } else if (z == NEMOCNICE_U_SVATE_ANNY) {
    if (s == 1) return 292;
    if (s == 2) return 316;
  } else if (z == NEMOCNICE_BOHUNICE) {
    if (s == 1) return 327;
    if (s == 2) return 0;
  } else if (z == NEMOCNICE_MILOSRDNYCH_BRATRI) {
    if (s == 1) return 320;
    if (s == 2) return 285;
  } else if (z == NERUDOVA) {
    if (s == 1) return 194;
    if (s == 2) return 221;
  } else if (z == VOZOVNA_HUSOVICE) {
    if (s == 1) return 92;
    if (s == 2) return 109;
  } else if (z == NOVE_SADY) {
    if (s == 1 || s == 3) return 279;
    if (s == 2 || s == 4) return 36;
  } else if (z == NOVOLISENSKA) {
    if (s == 1) return 65;
    if (s == 2) return 74;
  } else if (z == OBILNI_TRH) {
    if (s == 1) return 266;
    if (s == 2) return 274;
  } else if (z == OBRANSKA_U_SKOLY) {
    if (s == 1) return 98;
    if (s == 2) return 105;
  } else if (z == OBRANSKY_MOST) {
    if (s == 1) return 100;
    if (s == 2) return 103;
  } else if (z == ONDROUSKOVA) {
    if (s == 1) return 240;
    if (s == 2) return 243;
  } else if (z == ORECHOVSKA) {
    if (s == 1) return 17;
    if (s == 2) return 28;
  } else if (z == OSOVA) {
    if (s == 1) return 325;
    if (s == 2) return 8;
  } else if (z == OTAKARA_SEVCIKA) {
    if (s == 1) return 81;
    if (s == 2) return 86;
  } else if (z == PIONYRSKA) {
    if (s == 1) return 161;
    if (s == 2) return 187;
  } else if (z == PISARKY) {
    if (s == 1) return 299;
    if (s == 2) return 300;
  } else if (z == PODLESI) {
    if (s == 1) return 233;
    if (s == 2) return 248;
  } else if (z == PODSTRANSKA) {
    if (s == 1) return 56;
    if (s == 2) return 61;
  } else if (z == PORICI) {
    if (s == 1) return 319;
    if (s == 2) return 286;
  } else if (z == PROSKOVO_NAMESTI) {
    if (s == 1) return 97;
    if (s == 2) return 106;
  } else if (z == PRISTAVISTE) {
    if (s == 1) return 236;
    if (s == 2) return 245;
  } else if (z == RAKOVECKA) {
    if (s == 1) return 237;
    if (s == 2) return 238;
  } else if (z == ROSICKEHO_NAMESTI) {
    if (s == 1) return 227;
    if (s == 2) return 257;
  } else if (z == RYBKOVA) {
    if (s == 1) return 222;
    if (s == 2) return 261;
  } else if (z == RECKOVICE) {
    if (s == 1) return 174;
    if (s == 2) return 175;
  } else if (z == SEMILASSO) {
    if (s == 1) return 180;
    if (s == 2) return 181;
    if (s == 3) return 167;
  } else if (z == SKACELOVA) {
    if (s == 1) return 198;
    if (s == 2) return 217;
  } else if (z == SOCHOROVA) {
    if (s == 1) return 228;
    if (s == 2) return 256;
  } else if (z == SOUKENICKA) {
    if (s == 1) return 280;
    if (s == 2) return 35;
  } else if (z == STARA_OSADA) {
    if (s == 1) return 88;
    if (s == 2) return 91;
  } else if (z == STARY_LISKOVEC_SMYCKA) {
    if (s == 1) return 4;
    if (s == 2) return 5;
  } else if (z == STRANSKA_SKALA) {
    if (s == 1) return 57;
    if (s == 2) return 60;
  } else if (z == STRANSKA_SKALA_SMYCKA) {
    if (s == 1) return 58;
    if (s == 2) return 59;
  } else if (z == STRANSKEHO) {
    if (s == 1) return 255;
    if (s == 2) return 252;
  } else if (z == SVRATECKA) {
    if (s == 1) return 231;
    if (s == 2) return 250;
  } else if (z == SILINGROVO_NAMESTI) {
    if (s == 1) return 289;
    if (s == 2 || s == 4) return 291;
    if (s == 3) return 290;
  } else if (z == STEFANIKOVA_CTVRT) {
    if (s == 1) return 136;
    if (s == 2) return 137;
  } else if (z == SUMAVSKA) {
    if (s == 1) return 163;
    if (s == 2) return 185;
  } else if (z == SVERMOVA) {
    if (s == 1) return 324;
    if (s == 2) return 9;
  } else if (z == TABOR) {
    if (s == 1) return 223;
    if (s == 2) return 260;
  } else if (z == TECHNOLOGICKY_PARK) {
    if (s == 1) return 213;
    if (s == 2) return 214;
  } else if (z == TEREROVA) {
    if (s == 1) return 196;
    if (s == 2) return 219;
  } else if (z == TKALCOVSKA) {
    if (s == 1) return 120;
    if (s == 2) return 122;
  } else if (z == TECHNICKE_MUZEUM) {
    if (s == 1) return 200;
    if (s == 2) return 215;
  } else if (z == TOMANOVA) {
    if (s == 1) return 140;
    if (s == 2) return 153;
  } else if (z == TOMKOVO_NAMESTI) {
    if (s == 1) return 94;
    if (s == 2) return 107;
  } else if (z == TRAVNICKOVA) {
    if (s == 1) return 111;
    if (s == 2) return 132;
  } else if (z == TYLOVA) {
    if (s == 1) return 170;
    if (s == 2) return 179;
  } else if (z == USTREDNI_HRBITOV) {
    if (s == 1) return 13;
    if (s == 2) return 30;
  } else if (z == USTREDNI_HRBITOV_SMYCKA) {
    if (s == 1) return 14;
    if (s == 2) return 15;
  } else if (z == UVOZ) {
    if (s == 1) return 267;
    if (s == 2) return 273;
  } else if (z == UZKA) {
    if (s == 1) return 39;
    if (s == 2) return 48;
  } else if (z == VACLAVSKA) {
    if (s == 1) return 318;
    if (s == 2) return 287;
  } else if (z == VENHUDOVA) {
    if (s == 1) return 135;
    if (s == 2) return 138;
  } else if (z == VLHKA) {
    if (s == 1) return 49;
    if (s == 2) return 115;
  } else if (z == VOJTOVA) {
    if (s == 1) return 282;
    if (s == 2) return 33;
  } else if (z == VSETINSKA) {
    if (s == 1) return 283;
    if (s == 2) return 32;
  } else if (z == VSETICKOVA) {
    if (s == 1) return 268;
    if (s == 2) return 272;
  } else if (z == VYSTAVISTE_HLAVNI_VSTUP) {
    if (s == 1) return 296;
    if (s == 2) return 315;
  } else if (z == VYSTAVISTE_VSTUP_G2) {
    if (s == 1) return 297;
    if (s == 2) return 314;
  } else if (z == VOJENSKA_NEMOCNICE) {
    if (s == 1) return 121;
    if (s == 2) return 112;
  } else if (z == ZAPADNI_BRANA) {
    if (s == 1) return 326;
    if (s == 2) return 1;
  } else if (z == ZDRAHALOVA) {
    if (s == 1) return 134;
    if (s == 2) return 139;
  } else if (z == ZELNY_TRH) {
    if (s == 1) return 278;
    if (s == 2) return 117;
  } else if (z == ZEMEDELSKA) {
    if (s == 1) return 141;
    if (s == 2) return 152;
  } else if (z == ZOOLOGICKA_ZAHRADA) {
    if (s == 1) return 235;
    if (s == 2) return 246;
  } else if (z == ZELEZNICNI) {
    if (s == 1) return 41;
    if (s == 2) return 46;
  } else if (z == ZIDOVSKY_HRBITOV) {
    if (s == 1) return 54;
    if (s == 2) return 79;
  } else if (z == ZIVOTSKEHO) {
    if (s == 1) return 52;
    if (s == 2) return 51;
  } else if (z == VOZOVNA_PISARKY) {
    if (s == 1) return 301;
    if (s == 2) return 302;
    if (s == 3) return 308;
    if (s == 4) return 303;
    if (s == 5) return 307;
    if (s == 6) return 310;
    if (s == 7) return 304;
    if (s == 8) return 306;
    if (s == 9) return 311;
    if (s == 10) return 305;
    if (s == 12) return 312;
    if (s == 14) return 313;
  } else if (z == VOZOVNA_MEDLANKY || s == VOZOVNA_MEDLANKY_2) {
    if (s == 1) return 210;
    if (s == 2) return 209;
    if (s == 3) return 204;
    if (s == 4) return 203;
    if (s == 5) return 211;
    if (s == 6) return 208;
    if (s == 7) return 205;
    if (s == 8) return 202;
    if (s == 9) return 212;
    if (s == 10) return 207;
    if (s == 12) return 206;
    if (s == 14) return 201;
  } else if (z == MODRICE_SMYCKA) {
    if (s == 4) return 22;
    if (s == 3) return 23;
  } else if (z == MODRICE_TYRSOVA) {
    if (s == 1) return 21;
    if (s == 2) return 24;
  }
  return 65535;
}

const uint8_t PROGMEM z101[] = {
  ECEROVA, ONDROUSKOVA, KUBICKOVA, RAKOVECKA, PRISTAVISTE, ZOOLOGICKA_ZAHRADA, KAMENOLOM, PODLESI, BRANKA, SVRATECKA, KOMIN_SMYCKA, VOZOVNA_KOMIN,
  SOCHOROVA, ROSICKEHO_NAMESTI, SKACELOVA, CERVINKOVA, TECHNICKE_MUZEUM, TECHNOLOGICKY_PARK, VOZOVNA_MEDLANKY, RECKOVICE, FILKUKOVA, KORISKOVA,
  HUDCOVA, TYLOVA, SEMILASSO, HUSITSKA, KRALOVO_POLE_NADRAZI, HALASOVO_NAMESTI, CERTOVA_ROKLE, PODSTRANSKA, STRANSKA_SKALA, STRANSKA_SKALA_SMYCKA,
  BELOHORSKA, BILA_HORA, LISENSKA, NOVOLISENSKA, MASAROVA, KOTLANOVA, JIROVA, MIFKOVA, KOMAROV, USTREDNI_HRBITOV, USTREDNI_HRBITOV_SMYCKA, BOHUNICKA,
  ORECHOVSKA, MORAVANSKE_LANY, MORAVANSKA, MODRICKA_CIHELNA, KREMATORIUM, BELORUSKA, SVERMOVA, OSOVA, ZAPADNI_BRANA, NEMOCNICE_BOHUNICE, KARPATSKA,
  DUNAJSKA, STARY_LISKOVEC_SMYCKA
};

uint8_t vZone(uint8_t z) {
  if (z == MODRICE_TYRSOVA || z == MODRICE_SMYCKA) {
    return 164;
  } else if (z == VOZOVNA_MEDLANKY + 1) {
    return 163;
  } else if (z == VOZOVNA_PISARKY + 3) {
    return 162;
  }
  for (uint8_t i = 0; i < 57; i++) {
    if (pgm_read_byte(&z101[i]) + 1 == z || (z > VOJTOVA && pgm_read_byte(&z101[i]) + 2 == z)) {
      return 163;
    }
  }
  return 162;
}

uint8_t tlacitkoNaZastavku(uint8_t r, uint8_t c) {
  if (r == 0) return pgm_read_byte(&r0[c]);
  if (r == 1) return pgm_read_byte(&r1[c]);
  if (r == 2) return pgm_read_byte(&r2[c]);
  if (r == 3) return pgm_read_byte(&r2[c]);
  if (r == 4) return pgm_read_byte(&r4[c]);
  if (r == 5) return pgm_read_byte(&r5[c]);
  if (r == 6) return pgm_read_byte(&r6[c]);
  if (r == 7) return pgm_read_byte(&r7[c]);
  if (r == 8) return pgm_read_byte(&r8[c]);
  if (r == 9) return pgm_read_byte(&r9[c]);
  return 255;
}
