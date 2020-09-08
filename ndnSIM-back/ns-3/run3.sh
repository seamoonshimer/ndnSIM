#!/bin/bash 
echo " "
echo "[1/8] 0             multicast             Yes updata"
./waf --run "EdgeComputer --CachePolicy="0000" --RoutePolicy="multicast" --Updataing="Yes""

echo " "
echo "[2/8] 1             multicast             Yes updata"
./waf --run "EdgeComputer --CachePolicy="1111" --RoutePolicy="multicast" --Updataing="Yes""

echo " "
echo "[3/8] 3             multicast             Yes updata"
./waf --run "EdgeComputer --CachePolicy="3333" --RoutePolicy="multicast" --Updataing="Yes""

echo " "
echo "[4/8] 3             multicast             Yes updata"
./waf --run "EdgeComputer --CachePolicy="4444" --RoutePolicy="multicast" --Updataing="Yes""
echo " "
echo "[5/8] 0            best-route            Yes updata"
./waf --run "EdgeComputer --CachePolicy="0000" --RoutePolicy="best-route" --Updataing="Yes""

echo " "
echo "[6/8] 1            best-route            Yes updata"
./waf --run "EdgeComputer --CachePolicy="1111" --RoutePolicy="best-route" --Updataing="Yes""

echo " "
echo "[7/8] 3            best-route            Yes updata"
./waf --run "EdgeComputer --CachePolicy="3333" --RoutePolicy="best-route" --Updataing="Yes""

echo " "
echo "[9/8] 3            best-route            Yes updata"
./waf --run "EdgeComputer --CachePolicy="4444" --RoutePolicy="best-route" --Updataing="Yes""
