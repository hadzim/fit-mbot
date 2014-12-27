
------------------------------
Moduly:
------------------------------

TBS - knihovna utilit
TBS.Services - RPC knihovna
TBS.Robo - knihovna s definici robotickych modulu + komunikace po RS232
TBS.Robo.Can - knihovna pro komunikaci pres CAN podle Alikova protokolu

HAL.API - RPC rozhrani HALu - generovano
HAL.Movement - server implementujici HAL.API pro POHYB
HAL.CanModules - server implementujici HAL.API pro KAMEROVY SLOUPEK, MANIPULATOR a BIORADAR
HAL.UltraSound - server implementujici HAL.API pro DALKOVE SENZORY


------------------------------
Spusteni:
------------------------------

./HAL.Movement --mode=real

./HAL.CanModules --bioradar=1 --manipulator=1 --port1=5 --port2=14
	port1 - RS232 port pro kloub 1
	port2 - RS232 port pro kloub 2
	bioradar - ozivi modul bioradar
	manipulator - ozivi modul manipulator
	modul kamerovy sloupek je vzdy oziven

./HAL.UltraSound --mode=real

------------------------------
Cisla Portu:
------------------------------
Na Win odpovidaji COMxxx
Na linuxu je mapovaci tabulka:

0  = "/dev/ttyS0",
1  = "/dev/ttyS1",
2  = "/dev/ttyS2",
3  = "/dev/ttyS3",
4  = "/dev/ttyS4",
5  = "/dev/ttyS5",
6  = "/dev/ttyS6",
7  = "/dev/ttyS7",
8  = "/dev/ttyS8",
9  = "/dev/ttyS9",
10 = "/dev/ttyS10",
11 = "/dev/ttyS11",
12 = "/dev/ttyS12",
13 = "/dev/ttyS13",
14 = "/dev/ttyS14",
15 = "/dev/ttyS15",
16 = "/dev/ttyUSB0",
17 = "/dev/ttyUSB1",
18 = "/dev/ttyUSB2",
19 = "/dev/ttyUSB3",
20 = "/dev/ttyUSB4",
21 = "/dev/ttyUSB5",
22 = "/dev/ttyAMA0",
23 = "/dev/ttyAMA1",
24 = "/dev/ttyACM0",
25 = "/dev/ttyACM1",
26 = "/dev/rfcomm0",
27 = "/dev/rfcomm1",
28 = "/dev/ircomm0",
29 = "/dev/ircomm1"

