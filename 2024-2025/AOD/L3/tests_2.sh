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

for i in {15..15}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Long-C/Long-C.$i.0.gr -p2p ch9-1.1/inputs/Long-C/Long-C.$i.0.p2p -op2p results/longc/longc_$i.dijkstra.p2p.res
  echo "$i END"
done

echo "Long-C (dial)"

for i in {15..15}
do
  echo "$i START"
	./Dial -d ch9-1.1/inputs/Long-C/Long-C.$i.0.gr -p2p ch9-1.1/inputs/Long-C/Long-C.$i.0.p2p -op2p results/longc/longc_$i.dial.p2p.res
  echo "$i END"
done

echo "Long-C (radixheap)"

for i in {15..15}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Long-C/Long-C.$i.0.gr -p2p ch9-1.1/inputs/Long-C/Long-C.$i.0.p2p -op2p results/longc/longc_$i.radixheap.p2p.res
  echo "$i END"
done

echo "Long-n (dijkstra)"

for i in {21..21}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Long-n/Long-n.$i.0.gr -p2p ch9-1.1/inputs/Long-n/Long-n.$i.0.p2p -op2p results/longn/longn_$i.dijkstra.p2p.res
  echo "$i END"
done

echo "Long-n (dial)"

for i in {21..21}
do
  echo "$i START"
	./Dial -d ch9-1.1/inputs/Long-n/Long-n.$i.0.gr -p2p ch9-1.1/inputs/Long-n/Long-n.$i.0.p2p -op2p results/longn/longn_$i.dial.p2p.res
  echo "$i END"
done

echo "Long-n (radixheap)"

for i in {21..21}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Long-n/Long-n.$i.0.gr -p2p ch9-1.1/inputs/Long-n/Long-n.$i.0.p2p -op2p results/longn/longn_$i.radixheap.p2p.res
  echo "$i END"
done

echo "Random4-n (dijkstra)"

for i in {21..21}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Random4-n/Random4-n.$i.0.gr -p2p ch9-1.1/inputs/Random4-n/Random4-n.$i.0.p2p -op2p results/random4n/random4n_$i.dijkstra.p2p.res
  echo "$i END"
done

echo "Random4-n (dial)"

for i in {21..21}
do
  echo "$i START"
	./Dial -d ch9-1.1/inputs/Random4-n/Random4-n.$i.0.gr -p2p ch9-1.1/inputs/Random4-n/Random4-n.$i.0.p2p -op2p results/random4n/random4n_$i.dial.p2p.res
  echo "$i END"
done

echo "Random4-n (radixheap)"

for i in {21..21}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Random4-n/Random4-n.$i.0.gr -p2p ch9-1.1/inputs/Random4-n/Random4-n.$i.0.p2p -op2p results/random4n/random4n_$i.radixheap.p2p.res
  echo "$i END"
done

echo "Random4-C (dijkstra)"

for i in {15..15}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Random4-C/Random4-C.$i.0.gr -p2p ch9-1.1/inputs/Random4-C/Random4-C.$i.0.p2p -op2p results/random4c/random4c_$i.dijkstra.p2p.res
  echo "$i END"
done

echo "Random4-C (dial)"

for i in {15..15}
do
  echo "$i START"
	./Dial -d ch9-1.1/inputs/Random4-C/Random4-C.$i.0.gr -p2p ch9-1.1/inputs/Random4-C/Random4-C.$i.0.p2p -op2p results/random4c/random4c_$i.dial.p2p.res
  echo "$i END"
done

echo "Random4-C (radixheap)"

for i in {15..15}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Random4-C/Random4-C.$i.0.gr -p2p ch9-1.1/inputs/Random4-C/Random4-C.$i.0.p2p -op2p results/random4c/random4c_$i.radixheap.p2p.res
  echo "$i END"
done

echo "Square-n (dijkstra)"

for i in {21..21}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Square-n/Square-n.$i.0.gr -p2p ch9-1.1/inputs/Square-n/Square-n.$i.0.p2p -op2p results/squaren/squaren_$i.dijkstra.p2p.res
  echo "$i END"
done

echo "Square-n (dial)"

for i in {21..21}
do
  echo "$i START"
	./Dial -d ch9-1.1/inputs/Square-n/Square-n.$i.0.gr -p2p ch9-1.1/inputs/Square-n/Square-n.$i.0.p2p -op2p results/squaren/squaren_$i.dial.p2p.res
  echo "$i END"
done

echo "Square-n (radixheap)"

for i in {21..21}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Square-n/Square-n.$i.0.gr -p2p ch9-1.1/inputs/Square-n/Square-n.$i.0.p2p -op2p results/squaren/squaren_$i.radixheap.p2p.res
  echo "$i END"
done

echo "Square-C (dijkstra)"

for i in {15..15}
do
  echo "$i START"
	./Dijkstra -d ch9-1.1/inputs/Square-C/Square-C.$i.0.gr -p2p ch9-1.1/inputs/Square-C/Square-C.$i.0.p2p -op2p results/squarec/squarec_$i.dijkstra.p2p.res
  echo "$i END"
done

echo "Square-C (dial)"

for i in {15..15}
do
  echo "$i START"
	./Dial -d ch9-1.1/inputs/Square-C/Square-C.$i.0.gr -p2p ch9-1.1/inputs/Square-C/Square-C.$i.0.p2p -op2p results/squarec/squarec_$i.dial.p2p.res
  echo "$i END"
done

echo "Square-C (radixheap)"

for i in {15..15}
do
  echo "$i START"
	./RadixHeap -d ch9-1.1/inputs/Square-C/Square-C.$i.0.gr -p2p ch9-1.1/inputs/Square-C/Square-C.$i.0.p2p -op2p results/squarec/squarec_$i.radixheap.p2p.res
  echo "$i END"
done

echo "CTR start"
./Dijkstra -d ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.gr -p2p ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.p2p -op2p results/USA-road-t/USA-road-t.CTR.dijkstra.p2p.res
./Dial -d ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.gr -p2p ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.p2p -op2p results/USA-road-t/USA-road-t.CTR.dial.p2p.res
./RadixHeap -d ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.gr -p2p ch9-1.1/inputs/USA-road-t/USA-road-t.CTR.p2p -op2p results/USA-road-t/USA-road-t.CTR.radixheap.p2p.res

