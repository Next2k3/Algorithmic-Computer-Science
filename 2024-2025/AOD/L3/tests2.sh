#!/bin/bash

MAIN_FOLDER="results"

SUBFOLDERS=("USA-road-t" "squaren" "squarec" "random4n" "random4c" "longn" "longc")

if [ ! -d "$MAIN_FOLDER" ]; then
    mkdir "$MAIN_FOLDER"
fi

for folder in "${SUBFOLDERS[@]}"; do
    if [ ! -d "$MAIN_FOLDER/$folder" ]; then
        mkdir "$MAIN_FOLDER/$folder"
    fi
done


echo "Long-C (dijkstra)"

for i in {0..15}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Long-C/Long-C.$i.0.gr -ss ch9-1.1/inputs/Long-C/Long-C.$i.0.ss -oss results/longc/longc_$i.dijkstra.ss.res
  echo "$i END"
done


echo "Long-C (radixheap)"

for i in {0..15}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Long-C/Long-C.$i.0.gr -ss ch9-1.1/inputs/Long-C/Long-C.$i.0.ss -oss results/longc/longc_$i.radixheap.ss.res
  echo "$i END"
done

echo "Long-n (dijkstra)"

for i in {10..21}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Long-n/Long-n.$i.0.gr -ss ch9-1.1/inputs/Long-n/Long-n.$i.0.ss -oss results/longn/longn_$i.dijkstra.ss.res
  echo "$i END"
done

echo "Long-n (radixheap)"

for i in {10..21}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Long-n/Long-n.$i.0.gr -ss ch9-1.1/inputs/Long-n/Long-n.$i.0.ss -oss results/longn/longn_$i.radixheap.ss.res
  echo "$i END"
done

echo "Random4-n (dijkstra)"

for i in {10..21}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Random4-n/Random4-n.$i.0.gr -ss ch9-1.1/inputs/Random4-n/Random4-n.$i.0.ss -oss results/random4n/random4n_$i.dijkstra.ss.res
  echo "$i END"
done

echo "Random4-n (radixheap)"

for i in {10..21}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Random4-n/Random4-n.$i.0.gr -ss ch9-1.1/inputs/Random4-n/Random4-n.$i.0.ss -oss results/random4n/random4n_$i.radixheap.ss.res
  echo "$i END"
done

echo "Random4-C (dijkstra)"

for i in {0..15}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Random4-C/Random4-C.$i.0.gr -ss ch9-1.1/inputs/Random4-C/Random4-C.$i.0.ss -oss results/random4c/random4c_$i.dijkstra.ss.res
  echo "$i END"
done

echo "Random4-C (radixheap)"

for i in {0..15}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Random4-C/Random4-C.$i.0.gr -ss ch9-1.1/inputs/Random4-C/Random4-C.$i.0.ss -oss results/random4c/random4c_$i.radixheap.ss.res
  echo "$i END"
done

echo "Square-n (dijkstra)"

for i in {10..21}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Square-n/Square-n.$i.0.gr -ss ch9-1.1/inputs/Square-n/Square-n.$i.0.ss -oss results/squaren/squaren_$i.dijkstra.ss.res
  echo "$i END"
done

echo "Square-n (radixheap)"

for i in {10..21}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Square-n/Square-n.$i.0.gr -ss ch9-1.1/inputs/Square-n/Square-n.$i.0.ss -oss results/squaren/squaren_$i.radixheap.ss.res
  echo "$i END"
done

echo "Square-C (dijkstra)"

for i in {0..15}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Square-C/Square-C.$i.0.gr -ss ch9-1.1/inputs/Square-C/Square-C.$i.0.ss -oss results/squarec/squarec_$i.dijkstra.ss.res
  echo "$i END"
done


echo "Square-C (radixheap)"

for i in {0..15}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Square-C/Square-C.$i.0.gr -ss ch9-1.1/inputs/Square-C/Square-C.$i.0.ss -oss results/squarec/squarec_$i.radixheap.ss.res
  echo "$i END"
done


echo "BAY start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.BAY.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.BAY.ss -oss results/USA-road-t/USA-road-t.BAY.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.BAY.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.BAY.ss -oss results/USA-road-t/USA-road-t.BAY.radixheap.ss.res

echo "CAL start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.CAL.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.CAL.ss -oss results/USA-road-t/USA-road-t.CAL.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.CAL.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.CAL.ss -oss results/USA-road-t/USA-road-t.CAL.radixheap.ss.res

echo "COL start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.COL.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.COL.ss -oss results/USA-road-t/USA-road-t.COL.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.COL.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.COL.ss -oss results/USA-road-t/USA-road-t.COL.radixheap.ss.res

echo "CTR start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.ss -oss results/USA-road-t/USA-road-t.CTR.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.ss -oss results/USA-road-t/USA-road-t.CTR.radixheap.ss.res

echo "E start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.E.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.E.ss -oss results/USA-road-t/USA-road-t.E.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.E.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.E.ss -oss results/USA-road-t/USA-road-t.E.radixheap.ss.res

echo "FLA start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.FLA.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.FLA.ss -oss results/USA-road-t/USA-road-t.FLA.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.FLA.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.FLA.ss -oss results/USA-road-t/USA-road-t.FLA.radixheap.ss.res

echo "LKS start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.LKS.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.LKS.ss -oss results/USA-road-t/USA-road-t.LKS.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.LKS.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.LKS.ss -oss results/USA-road-t/USA-road-t.LKS.radixheap.ss.res

echo "NE start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.NE.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.NE.ss -oss results/USA-road-t/USA-road-t.NE.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.NE.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.NE.ss -oss results/USA-road-t/USA-road-t.NE.radixheap.ss.res

echo "NW start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.NW.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.NW.ss -oss results/USA-road-t/USA-road-t.NW.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.NW.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.NW.ss -oss results/USA-road-t/USA-road-t.NW.radixheap.ss.res

echo "NY start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.NY.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.NY.ss -oss results/USA-road-t/USA-road-t.NY.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.NY.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.NY.ss -oss results/USA-road-t/USA-road-t.NY.radixheap.ss.res

echo "W start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.W.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.W.ss -oss results/USA-road-t/USA-road-t.W.dijkstra.ss.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.W.gr -ss ch9-1.1/inputs/USA-road-t/USA-road-t.W.ss -oss results/USA-road-t/USA-road-t.W.radixheap.ss.res
