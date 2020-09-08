#!/bin/bash 

echo " "
echo "[1/12] 0             best-route            No updata"
#./waf --run "EdgeComputer --CachePolicy="0000" --RoutePolicy="best-route" --Updataing="No""

echo " "
echo "[2/12] 1             best-route            No updata"
#./waf --run "EdgeComputer --CachePolicy="1111" --RoutePolicy="best-route" --Updataing="No""

echo " "
echo "[3/12] 3             best-route            No updata"
#./waf --run "EdgeComputer --CachePolicy="3333" --RoutePolicy="best-route" --Updataing="No""

echo " "
echo "[4/12] 0             multicast             No updata"
./waf --run "EdgeComputer --CachePolicy="0000" --RoutePolicy="multicast" --Updataing="No""

echo " "
echo "[5/12] 1             multicast             No updata"
./waf --run "EdgeComputer --CachePolicy="1111" --RoutePolicy="multicast" --Updataing="No""

echo " "
echo "[6/12] 3             multicast             No updata"
./waf --run "EdgeComputer --CachePolicy="3333" --RoutePolicy="multicast" --Updataing="No""

echo " "
echo "[7/12] 0             multicast             Yes updata"
./waf --run "EdgeComputer --CachePolicy="0000" --RoutePolicy="multicast" --Updataing="Yes""

echo " "
echo "[8/12] 1             multicast             Yes updata"
./waf --run "EdgeComputer --CachePolicy="1111" --RoutePolicy="multicast" --Updataing="Yes""

echo " "
echo "[9/12] 3             multicast             Yes updata"
./waf --run "EdgeComputer --CachePolicy="3333" --RoutePolicy="multicast" --Updataing="Yes""

echo " "
echo "[10/12] 0            best-route            Yes updata"
#./waf --run "EdgeComputer --CachePolicy="0000" --RoutePolicy="best-route" --Updataing="Yes""

echo " "
echo "[11/12] 1            best-route            Yes updata"
#./waf --run "EdgeComputer --CachePolicy="1111" --RoutePolicy="best-route" --Updataing="Yes""

echo " "
echo "[12/12] 3            best-route            Yes updata"
#./waf --run "EdgeComputer --CachePolicy="3333" --RoutePolicy="best-route" --Updataing="Yes""

