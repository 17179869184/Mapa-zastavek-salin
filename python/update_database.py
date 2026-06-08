import requests, zipfile, io, sqlite3, bisect, csv, functools, time

t = time.time()

r = requests.get("https://kordis-jmk.cz/gtfs/gtfs.zip", timeout=10000)
r.raise_for_status()
z = zipfile.ZipFile(io.BytesIO(r.content))
print(f"Data stažena ({(time.time() - t):.2f} s)")

db = "jizdnirady.db"
con = sqlite3.connect(db)
SQL = con.cursor()

@functools.lru_cache(1024)
def validID(id):
    return "N" not in id and int(id[1:].split("Z")[0]) in zastavky

zastavky = [1006,1011,1014,1018,1021,1023,1026,1031,1041,1042,1047,1048,1053,1069,1072,1073,1077,1082,1086,1088,1097,1102,1108,1112,1116,1121,1128,1137,1146,1147,1166,1167,1171,1176,1208,1211,1212,1217,1218,1226,1227,1233,1242,1256,1257,1261,1262,1266,1271,1272,1277,1282,1286,1291,1293,1301,1312,1313,1336,1343,1347,1357,1358,1368,1371,1372,1378,1384,1389,1393,1396,1397,1398,1400,1418,1422,1423,1428,1429,1430,1431,1434,1436,1438,1442,1447,1448,1461,1466,1472,1473,1483,1487,1493,1501,1512,1521,1527,1537,1544,1552,1553,1566,1567,1591,1596,1611,1616,1618,1619,1621,1633,1637,1646,1652,1653,1657,1659,1661,1663,1664,1667,1668,1676,1683,1703,1706,1712,1716,1721,1731,1746,1751,1756,1761,1762,1768,1769,1773,1779,1782,1784,1786,1796,1807,1810,1814,9410,9430,15134,15137]
linky = {"1","2","3","4","5","6","7","8","9","10","12","14"}

@functools.lru_cache(1024)
def gtfs_to_seconds(t):
    h, m, s = map(int, t.split(":"))
    return h * 3600 + m * 60 + s

# calendar.txt -> seznam platných service_id podle start_date a end_date a dne v týdnu
# calendar_dates.txt -> odstranit service_id podle date
# trips.txt -> dictionary trip_id -> route_id podle service_id a route_id
# stop_times.txt -> dictionary trip_id -> stop_id, arrival_time, departure_time a stop_sequence podle trip_id + ukládat seznam stop_id
# stops.txt -> dictionary stop_id -> stop_name podle stop_id

SQL.execute("PRAGMA foreign_keys = ON")
SQL.execute("DROP TABLE IF EXISTS calendar_dates")
SQL.execute("DROP TABLE IF EXISTS stop_times")
SQL.execute("DROP TABLE IF EXISTS stops")
SQL.execute("DROP TABLE IF EXISTS trips")
SQL.execute("DROP TABLE IF EXISTS calendar")
SQL.execute("CREATE TABLE calendar(service_id INTEGER PRIMARY KEY, start_date INTEGER, end_date INTEGER, monday BOOLEAN, tuesday BOOLEAN, wednesday BOOLEAN, thursday BOOLEAN, friday BOOLEAN, saturday BOOLEAN, sunday BOOLEAN)")
SQL.execute("CREATE TABLE calendar_dates(service_id INTEGER, date INTEGER, PRIMARY KEY (service_id, date))")
SQL.execute("CREATE TABLE trips(trip_id INTEGER PRIMARY KEY, route_id INTEGER, service_id INTEGER, FOREIGN KEY (service_id) REFERENCES calendar(service_id))")
SQL.execute("CREATE TABLE stops(stop_id INTEGER PRIMARY KEY, nazev TEXT)")
SQL.execute("CREATE TABLE stop_times(trip_id INTEGER, stop_id TEXT, arrival_time INTEGER, departure_time INTEGER, stop_sequence INTEGER, PRIMARY KEY (trip_id, stop_sequence), FOREIGN KEY (trip_id) REFERENCES trips(trip_id))")

with z.open("calendar.txt") as f:
    SQL.executemany("INSERT INTO calendar VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", [[row["service_id"], int(row["start_date"]), int(row["end_date"]), int(row["monday"]), int(row["tuesday"]), int(row["wednesday"]), int(row["thursday"]), int(row["friday"]), int(row["saturday"]), int(row["sunday"])] for row in csv.DictReader(io.TextIOWrapper(f, encoding="utf-8-sig"))])

with z.open("calendar_dates.txt") as f:
    SQL.executemany("INSERT INTO calendar_dates VALUES (?, ?, ?)", [[row["service_id"], int(row["date"])] for row in csv.DictReader(io.TextIOWrapper(f, encoding="utf-8-sig"))])

with z.open("trips.txt") as f:
    SQL.executemany("INSERT INTO trips VALUES (?, ?, ?)", [[int(row["trip_id"]), row["route_id"][1:].split("D")[0], row["service_id"]] for row in csv.DictReader(io.TextIOWrapper(f, encoding="utf-8-sig")) if row["route_id"][1:].split("D")[0] in linky])

with z.open("stop_times.txt") as f:
    SQL.executemany("INSERT INTO stop_times(trip_id, stop_id, arrival_time, departure_time, stop_sequence) SELECT ?, ?, ?, ?, ? WHERE EXISTS (SELECT 1 FROM trips WHERE trip_id = ?)", [[int(row["trip_id"]), row["stop_id"], gtfs_to_seconds(row["arrival_time"]), gtfs_to_seconds(row["departure_time"]), int(row["stop_sequence"]), int(row["trip_id"])] for row in csv.DictReader(io.TextIOWrapper(f, encoding="utf-8-sig"))])

with z.open("stops.txt") as f:
    SQL.executemany("INSERT OR IGNORE INTO stops VALUES (?, ?)", [[bisect.bisect_right(zastavky, int(row["stop_id"][1:].split("Z")[0])) - 1, row["stop_name"]] for row in csv.DictReader(io.TextIOWrapper(f, encoding="utf-8-sig")) if validID(row["stop_id"])])

SQL.execute("DELETE FROM stop_times WHERE stop_id LIKE \"U1437%\"")
SQL.execute("INSERT OR IGNORE INTO stops VALUES (147, 'Vozovna Pisárky'), (148, 'Vozovna Medlánky')")

SQL.execute("CREATE INDEX idx_stop_times_trip ON stop_times(trip_id)")
SQL.execute("CREATE INDEX idx_stop_times_trip_stop_sequence ON stop_times(trip_id, stop_sequence)")
SQL.execute("CREATE INDEX idx_trips_service ON trips(service_id)")
SQL.execute("CREATE INDEX idx_trips_route ON trips(route_id)")
SQL.execute("CREATE INDEX idx_calendar_dates_service_id ON calendar_dates(service_id)")
SQL.execute("CREATE INDEX idx_calendar_dates_date ON calendar_dates(date)")
SQL.execute("CREATE INDEX idx_calendar_service_id ON calendar(service_id)")

con.commit()
print(f"Datáze uložena ({(time.time() - t):.2f} s)")
