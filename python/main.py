import datetime, serial, time, bisect, sqlite3, functools, sys
zastavky = [1006,1011,1014,1018,1021,1023,1026,1031,1041,1042,1047,1048,1053,1069,1072,1073,1077,1082,1086,1088,1097,1102,1108,1112,1116,1121,1128,1137,1146,1147,1166,1167,1171,1176,1208,1211,1212,1217,1218,1226,1227,1233,1242,1256,1257,1261,1262,1266,1271,1272,1277,1282,1286,1291,1293,1301,1312,1313,1336,1343,1347,1357,1358,1368,1371,1372,1378,1384,1389,1393,1396,1397,1398,1400,1418,1422,1423,1428,1429,1430,1431,1434,1436,1438,1442,1447,1448,1461,1466,1472,1473,1483,1487,1493,1501,1512,1521,1527,1537,1544,1552,1553,1566,1567,1591,1596,1611,1616,1618,1619,1621,1633,1637,1646,1652,1653,1657,1659,1661,1663,1664,1667,1668,1676,1683,1703,1706,1712,1716,1721,1731,1746,1751,1756,1761,1762,1768,1769,1773,1779,1782,1784,1786,1796,1807,1810,1814,9410,9430,15134,15137]

t = time.time()

NOUSB = False

def connect():
    usb = serial.Serial()
    usb.timeout = 5
    usb.port = "COM4"
    usb.baudrate = 9600
    usb.dtr = False
    usb.open()
    return usb

if not NOUSB:
    usb = connect()
    print(f"USB připojeno ({(time.time() - t):.2f} s)")

db = "jizdnirady.db"
con = sqlite3.connect(db)
SQL = con.cursor()

def validID(id):
    return "N" not in id and int(id[1:].split("Z")[0]) in zastavky

print(f"Databáze načtena ({(time.time() - t):.2f} s)")

@functools.lru_cache(1024)
def aktivni(service_id, datum):
    d_int = int(datum.strftime("%Y%m%d"))
    dny = SQL.execute("SELECT 1 FROM calendar_dates WHERE service_id = ? AND date = ?", [service_id, d_int]).fetchone()
    if dny is not None:
        return False
    kalendar = SQL.execute("SELECT monday, tuesday, wednesday, thursday, friday, saturday, sunday FROM calendar WHERE service_id = ? AND start_date <= ? AND end_date >= ? LIMIT 1", [service_id, d_int, d_int]).fetchone()
    if kalendar is None:
        return False
    return kalendar[datum.weekday()]

@functools.lru_cache(1024)
def nazev(zastavka):
    return SQL.execute("SELECT nazev FROM stops WHERE stop_id = ? LIMIT 1", [zastavka]).fetchone()[0]

posledniminuty = -10

lastupdate = 0
ZIVE = 1
TIMELAPSE = 2
CESTA = 3
try:
    mod = int(sys.argv[1])
except:
    mod = ZIVE
cas = datetime.datetime.now()

def rozsvititZastavku(l, z, n):
    if z == 15:
        if n == 10: n = 6
        elif n == 9: n = 5
    elif z == 28:
        if n == 25: n = 7
        elif n == 26: n = 8
    elif z == 35:
        if n == 7: n = 5
        elif n == 8: n = 6
    elif z == 66:
        if n == 15: n = 5
        elif n == 16: n = 6
    elif z == 115:
        if n == 4: n = 2
    usb.write(bytes([l]) + bytes([z]) + bytes([n]))

def mod_zt():
    global lastupdate, cas
    if time.time() < lastupdate + (3 if mod == TIMELAPSE else 15): return
    if mod == TIMELAPSE:
        cas += datetime.timedelta(minutes=1)
    else:
        cas = datetime.datetime.now()
    lastupdate = time.time()

    current_sec = (cas.hour * 3600 + cas.minute * 60 + cas.second)
    if not NOUSB:
        usb.write(b"\x00" + bytes([200 + cas.hour]) + bytes([20 + cas.minute]))

    vehicles = set()
    datum = cas.date()
    for trip_id, service_id, linka in SQL.execute("SELECT trip_id, service_id, route_id FROM trips").fetchall():
        stops = SQL.execute("SELECT stop_id, arrival_time, departure_time FROM stop_times WHERE trip_id = ? ORDER BY stop_sequence", [trip_id]).fetchall()
        if not stops or not service_id or not aktivni(service_id, datum):
            continue
            
        prijezdy = list(map(lambda e: e[1], stops))
        first_dep = stops[0][1]
        last_arr = stops[-1][2]  # asi by mělo být [-1][1], ale takhle se zobrazí i spoje, který asi stojí na konečné a čekají (možná)

        index = bisect.bisect_right(prijezdy, current_sec) - 1

        if index < 0:
            continue

        stop_id = stops[index][0]

        zastavka, nastupiste = stop_id.split("Z")
        zastavka = int(zastavka[1:])
        nastupiste = int(nastupiste)

        if zastavka == 0: continue
        try:
            zastavka = bisect.bisect_right(zastavky, zastavka) - 1
        except:
            continue
        
        if current_sec < first_dep - 300:
            if zastavka == 59:
                zastavka = 147
            elif zastavka not in [133, 147, 148]:
                continue

        if current_sec > last_arr + 300:
            if zastavka == 59:
                zastavka = 147
            elif zastavka not in [133, 147, 148]:
                continue

        if zastavka in [133, 147, 148]:
            nastupiste = int(linka)
        vehicles.add((linka, zastavka, nastupiste))
    
    for linka, zastavka, nastupiste in vehicles:
        if not NOUSB:
            rozsvititZastavku(int(linka), zastavka, nastupiste)
            print(f"Linka {linka} je na zastávce {nazev(zastavka)}, nástupišti č. {nastupiste}")
    if not NOUSB:
        usb.write(b'\x2f')
    print("update", len(vehicles))
    vehicles = set()

def mod_cesta():
    usb.write(b'\x2f')
    stop1 = b''
    stop2 = b''
    while not stop1: stop1 = usb.readline()
    while not stop2: stop2 = usb.readline()
    stop1 = int(stop1)
    stop2 = int(stop2)
    print(stop1, stop2)
    print(nazev(stop1), nazev(stop2))
    mod_l(stop1, stop2, presne=False)

def mod_l(stop1, stop2, presne=True):
    results = set()
    for trip_id, route_id, service_id in SQL.execute("SELECT trip_id, route_id, service_id FROM trips").fetchall():
        if not aktivni(service_id, datetime.datetime.now().date()):
            continue
        stops = list(map(lambda e: e[0], SQL.execute("SELECT stop_id FROM stop_times WHERE trip_id = ? ORDER BY stop_sequence", [trip_id]).fetchall()))
        departure = SQL.execute("SELECT departure_time FROM stop_times WHERE trip_id = ? AND stop_sequence = 1", [trip_id]).fetchone()[0]/60
        if departure < 360 or departure > 900: continue
        if presne:
            prvni = stops[0]
            posledni = stops[-1]
            if bisect.bisect_right(zastavky, int(prvni[1:].split("Z")[0])) - 1 == stop1 and bisect.bisect_right(zastavky, int(posledni[1:].split("Z")[0])) - 1 == stop2:
                results.add((route_id, tuple(stops), -1))
        else:
            prvni = -1
            druha = -1
            for n, stop in enumerate(stops):
                stop = bisect.bisect_right(zastavky, int(stop[1:].split("Z")[0])) - 1
                if stop == stop1 and prvni == -1:
                    prvni = n
                if stop == stop2:
                    druha = n
            if min(prvni, druha) > -1 and prvni < druha:
                results.add((route_id, tuple(stops[prvni:druha + 1]), bisect.bisect_right(zastavky, int(stops[-1][1:].split("Z")[0])) - 1))
    time.sleep(3)
    for (linka, stops, konecna) in results:
        for stop in stops:
            zastavka, nastupiste = stop[1:].split("Z")
            if not NOUSB:
                rozsvititZastavku(linka, bisect.bisect_right(zastavky, int(zastavka)) - 1, int(nastupiste))
            print(linka, nazev(bisect.bisect_right(zastavky, int(zastavka)) - 1), nastupiste)
        if not NOUSB:
            usb.write(b"\x2f")
            usb.write(bytes([linka]) + bytes([konecna]) + bytes([0]))
        time.sleep(3)

while not False:
    if posledniminuty != cas.minute:
        posledniminuty = cas.minute
        if not NOUSB:
            usb.write(b"\x00" + bytes([200 + cas.hour]) + bytes([20 + cas.minute]))
    if mod == ZIVE or mod == TIMELAPSE:
        mod_zt()
    elif mod == CESTA:
        mod_cesta()
