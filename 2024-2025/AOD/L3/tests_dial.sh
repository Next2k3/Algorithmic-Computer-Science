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


echo "Random4-C (dial)"

for i in {0..15}
do
  echo "$i START"
	./Dial -d ch9-1.1/inputs/Random4-C/Random4-C.$i.0.gr -ss ch9-1.1/inputs/Random4-C/Random4-C.$i.0.ss -oss results/random4c/random4c_$i.dial.ss.res
  echo "$i END"
done

