# Mapa šalin

## Ukázka
[Video](https://youtube.com/watch?v=xEewmRj0Wb8)

## Software
### Získání dat
Data jsou od společnosti KORDIS JMK, ve formátu GTFS (*[General Transit Feed Specification](https://gtfs.org/documentation/schedule)*), stažená [zde](https://kordis-jmk.cz/gtfs/gtfs.zip). Z dat se vezmou soubory `calendar_dates.txt`, `calendar.txt`, `stop_times.txt`, `stops.txt` a `trips.txt` a načtou se do databáze. Ze souboru `calendar.txt` se vezme `start_date`, `end_date`, `monday`-`sunday` a `service_id`. Dané `service_id` platí od `start_date` do `end_date` v dané dny v týdnu. Z `calendar_dates.txt` se vezme `date` a `service_id`. Dané `service_id` v den `date` neplatí, přestože by podle `calendar.txt` mělo. Z `trips.txt` se vezme `trip_id`, `route_id` a `service_id`. Určitá trasa v určitý čas má unikátní `trip_id`, platí podle `service_id` a na dané trase jede linka číslo `route_id`. Odsud se vyfiltrují pouze `route_id`, která odpovídají linkám 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12 a 14. Ze `stop_times.txt` se vezme `trip_id`, `stop_id`, `arrival_time`, `departure_time` a `stop_sequence`. Na daném `trip_id` vůz přijede / odjede v `arrival_time` / `departure_time` (často se rovnají, u konečných zastávek je `departure_time` vlastně `arrival_time` příštího `trip_id` na stejné lince ze stejné zastávky) na / ze zastávky `stop_id`, která je v pořadí číslo `stop_sequence` (od 1). Odsud se vyfiltrují pouze `trip_id`, která zbyla v `trips.txt`. Ze `stops.txt` se vezme `stop_id` a `stop_name`. Vyfiltrují se pouze ta `stop_id`, která zbyla v `stop_times.txt`. Pomocí SQL příkazů se pak hledají odjezdy.
- V živém módu a zrychleném módu se vezme aktuální den a aktuální čas (ve zrychleném se přičítá 1 minuta každé 2 sekundy, v živém 15 sekund každých 15 sekund), najdou se všechny spoje, které vyjedou nejdříve za 5 minut, už vyjely nebo přijely nejpozději před 5 minutami. Nebere tedy v potaz zpoždění spojů ani mimořádné události, ale mezi zobrazením nevzniká žádná prodleva a je možné se dívat i do budoucnosti.
- V linkovém módu se projdou všechny spoje v daný den od 6:00 do 15:00, které obsahují dané linky v daném pořadí, potom se postupně zobrazí všechny unikátní linky s unikátní sekvencí zastávek a přečte se jejich číslo a směr.

Ve statických datech je u každé zastávky i nástupiště, podle kterého se určuje, která LEDka se rozsvítí. U většiny zastávek se rozsvítí LEDka na pravé straně ve směru jízdy. Zastávka `Nemocnice Bohunice` má západní LEDku pro západní kolej a východní LEDku pro východní kolej, zastávka `Mifkova` má západní LEDku pro západní kolej a východní LEDku pro obě východní koleje, zastávky `Vozovna Medlánky` a `Vozovna Pisárky` mají jednu LEDku pro každou linku, zastávky `Česká`, `Hlavní nádraží`, `Jugoslávská`, `Malinovského náměstí`, `Mendlovo náměstí`, `Moravské náměstí`, `Semilasso` a `Šilingrovo náměstí` používají LEDky podle [těchto schémat](/schemata/).

### Přenos dat
Přes USB se pošle packet ve formátu:
X (1 B, *linka*) | Y (1 B, *zastávka*) | Z (1 B, *nástupiště*) | význam
---|---|---|---
0 | 0 - 149 | b0??? | přečti zastávku Y jako aktuální zastávku
0 | 0 - 149 | b1??? | přečti zastávku Y jako příští zastávku
0 | 0 - 149 | b?1?? | přečti zastávku Y jako konečnou zastávku
0 | 0 - 149 | b??10 | přečti zastávku Y jako první v tarifní zóně
0 | 0 - 149 | b??11 | přečti zastávku Y jako poslední v tarifní zóně
0 | 200 - 223 | 20-79 | nastav hodiny na 200 - Y a minuty na 20 - Z
1 - 12, 14 | 0 - 149 | 0 | přečti zastávku Y jako směr linky X
1 - 12, 14 | 0 - 149 | 1 - 50 | rozsviť zastávku Y nástupiště Z barvou X

### Zpracování dat
Arduino u každé šaliny zjistí ze zastávky a nástupiště, kolikátá LEDka v řetězu se má rozsvítit a z linky zjistí, kterou barvou. Pokud je linka nula, dále se rozliší jestli jde o změnu času, nebo o přečtení zastávky. V kódu jsou také informace o tarifních zónách.

## Hardware
### Arduino Mega
Arduino Mega 2560
 - 16 MHz ATmega2560 8-bitový procesor
 - 8 kB RAM
 - 256 kB flash paměti
 - 54 GPIO pinů

### NeoPixel LEDky
NeoPixel RGB LEDky mají čip s 3 B RAM. Na `D-IN` se pošle RGB sekvence LEDek, každá si vezme první 3 B (interpretuje v pořadí GRB místo RGB), zbytek posílá do `D-OUT`. Arduino generuje signál takto:
```
ldi %[counter], 8
loop:
st   %a[port], %[hi]
sbrc %[byte], 7
mov  %[next], %[hi]
dec  %[bit]
st   %a[port], %[next]
mov  %[next], %[lo]
rol  %[byte]
st   %a[port], %[lo]
dec %[counter]
brne loop
ldi  %[bit], 8
ld   %[byte], %a[ptr]+
st   %a[port], %[lo]
sbiw %[count], 1
```
V programu jsou 2 buffery, první pro seznam RGB hodnot (včetně jasu, ten se posílá, v kódu nahoře je to `ptr`) a druhý pro seznam linek. Při aktualizaci se z druhého vypočítá první, při změně jasu se přepočítá první ze svých vlastních hodnot, změna jasu tedy neovlivňuje data postupně přicházející přes USB.
Dole jsou přesné RGB hodnoty při základní hodnotě jasu, dále to lze snížit na polovinu nebo čtvrtinu pomocí tlačítek přímo na desce:
linka | R | G | B | proud
---|---:|---:|---:|---
1 | 192 | 0 | 0 | 15 mA
2 | 0 | 192 | 0 | 15 mA
3 | 0 | 144 | 48 | 15 mA
4 | 156 | 36 | 0 | 15 mA
5 | 144 | 0 | 48 | 15 mA
6 | 0 | 0 | 192 | 15 mA
7 | 60 | 60 | 60 | 14,0625 mA
8 | 120 | 72 | 0 | 15 mA
9 | 96 | 0 | 96 | 15 mA
10 | 108 | 60 | 24 | 15 mA
12 | 0 | 72 | 120 | 15 mA
14 | 132 | 24 | 36 | 15 mA

### Ovládací panel
Panel obsahuje 3 výstupy: 2 LEDky a reproduktor a 4 vstupy: 2 tlačítka, páčku a potenciometr zesilovače, dále je zezadu nouzový vypínač.
pin | funkce
---|---
|||
2 | červené tlačítko
3 | zelené tlačítko
|||
4 | oranžová LEDka
|||
7 | LEDky
|||
8 | pin CS displeje
|||
22 | větev Starý Lískovec
23 | větev Modřice
24 | větev Náměstí Míru
25 | větev Komárov
26 | větev Královo Pole
27 | větev Líšeň
28 | větev Bystrc
29 | větev Maloměřice
30 | větev Řečkovice
31 | větev Lesná
32 | okruh 0
33 | okruh 1
34 | okruh 2
35 | okruh 3
36 | okruh 4
37 | okruh 5
38 | okruh 6
39 | okruh 7
40 | okruh 8
41 | okruh 9
42 | okruh 10
43 | okruh 11
44 | okruh 12
45 | okruh 13
46 | okruh 14
|||
51 | pin DIN displeje
52 | pin CLK displeje

### LED displej
Displej se skládá z 8 × 32 (= 256) červených LEDek, ovládaných 5 dráty pomocí SPI (*Serial Peripheral Interface*). Font je zkopírován z cedulí na zastávkách, kde znaky mají jen 7 řádků, proto je horní řádek volný.

### DFPlayer mini
DFPlayer mini je přehrávač s SD kartou s jednotlivými nahrávkami, které se skládají do hlášení. Je připojen k Arduinu a zesilovači, ten je připojen k reproduktoru.

### Tlačítka
Pro úsporu pinů jsou tlačítka uspořádána do obdélníku 10x15 (*button matrix*). Po spuštění se všechny řádky nastaví na `HIGH`. Pak se jeden po druhém nastaví na `LOW` a zbytek na `HIGH`, pokud se na některém sloupci detekuje `LOW`, znamená to, že z řádku který je `LOW` prošel signál tlačítkem do daného sloupce, tlačítko na průsečíku řádku a sloupce tedy bylo zmáčknuto. U každého tlačítka je dioda, aby vše správně fungovalo, pokud by bylo zmáčknuto více tlačítek zaráz (jelikož by se `LOW` mohl šířit i pozpátku -> ze sloupců do řádků a stisknutí by byla detekována i tam, kde nejsou, tzv. *ghosting*). Jeden skenovací cyklus trvá pouze pár mikrosekund.

### Deska
Deska se skládá ze 6 30x30 cm desek, s vygravírovanou mapou (na školní gravírce). Její rozměry jsou 90 × 60 × 4,5 cm, podle článku 6, odstavce 2, písmene c [Tarifu Integrovaného dopravního systému Jihomoravského kraje](https://www.idsjmk.cz/api/document-download/cs/ceny-jizdneho/tarif_2020_01_01/2025-12-14) se tedy jedná o ruční zavazadlo jehož přeprava je bezplatná. Celá deska je vystužená dřevěným rámem. Deska má zdroj do zásuvky na 5 V 10 A (lze ji tedy zapojit například ve vlaku), nouzový vypínač, běžný vypínač a 2 tlačítka na ovládání. Na desce je přibližně 2 500 připájených spojů a 50 metrů drátů.

## Cena
Název | Cena / ks | ks | Celkem
:---|---:|:---:|---:
NeoPixel LED | 4,5 | 328 | 1 476
Arduino Mega | 1 045 | 1 | 1 045
Zdroj | 635 | 1 | 635
SD karta | 249 | 1 | 249
Displej | 169 | 1 | 169
Mikrospínače | 1 | 148 | 148
Diody | 1 | 148 | 148
Dřevo | 28 | 3 | 112
Oranžový kabel | 3,5 | 30 | 105
USB kabel | 60 | 1 | 60
Vodiče | 59 | 1 | 59
DFPlayer mini | 57 | 1 | 57
Velké nálepky | 28 | 2 | 56
Zesilovač | 39 | 1 | 39
Fialový kabel | 3,5 | 10 | 35
Červený kabel | 3,5 | 10 | 35
Černý kabel | 3,5 | 10 | 35
Bílý kabel | 3,5 | 10 | 35
Relé | 32 | 1 | 32
Tlačítka | 12 | 2 | 24
Vypínač | 19 | 1 | 19
Malé nálepky | 5 | 3 | 15
Páčka | 15 | 1 | 15
Školní cín  | 0 | 1 | 0
Školní desky | 0 | 6 | 0
|||
Celkem |||4 603
