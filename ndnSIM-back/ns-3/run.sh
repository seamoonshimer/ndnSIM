#!/bin/bash 

echo " "
echo "[0/16] NoCache             NoCache              NoCache              NoCache"
./waf --run "EdgeComputer --CachePolicy="0000" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[1/16] Lfu                 Lfu                  Lfu                  Lfu"
./waf --run "EdgeComputer --CachePolicy="3333" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[2/16] Lfu                 Lfu                  Lfu                  Random"
./waf --run "EdgeComputer --CachePolicy="3334" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[3/16] Lfu                 Lfu                  Random               Lfu"
./waf --run "EdgeComputer --CachePolicy="3343" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[4/16] Lfu                 Lfu                  Random               Random"
./waf --run "EdgeComputer --CachePolicy="3344" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[5/16] Lfu                 Random               Lfu                  Lfu"
./waf --run "EdgeComputer --CachePolicy="3433" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[6/16] Lfu                 Random               Lfu                  Random"
./waf --run "EdgeComputer --CachePolicy="3434" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[7/16] Lfu                 Random               Random               Lfu"
./waf --run "EdgeComputer --CachePolicy="3443" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[8/16] Lfu                 Random               Random               Random"
./waf --run "EdgeComputer --CachePolicy="3444" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[9/16] Random              Lfu                  Lfu                  Lfu"
./waf --run "EdgeComputer --CachePolicy="4333" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[10/16] Random             Lfu                  Lfu                  Random"
./waf --run "EdgeComputer --CachePolicy="4334" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[11/16] Random             Lfu                  Random               Lfu"
./waf --run "EdgeComputer --CachePolicy="4343" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[12/16] Random             Lfu                  Random               Random"
./waf --run "EdgeComputer --CachePolicy="4344" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[13/16] Random             Random               Lfu                  Lfu"
./waf --run "EdgeComputer --CachePolicy="4433" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[14/16] Random             Random               Lfu                  Random"
./waf --run "EdgeComputer --CachePolicy="4434" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[15/16] Random             Random               Random               Lfu"
./waf --run "EdgeComputer --CachePolicy="4443" --RoutePolicy="best-route" --FIBPolicy="best-route""

echo " "
echo "[16/16] Random             Random               Random               Random"
./waf --run "EdgeComputer --CachePolicy="4444" --RoutePolicy="best-route" --FIBPolicy="best-route""
