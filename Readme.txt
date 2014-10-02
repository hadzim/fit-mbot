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

