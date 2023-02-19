#!/usr/bin/env bash

inputFile = $1
outputFile = $2
timesToRun = $3
kernelSize = $4


for ((c=0; c<3; c++))
do
    for ((c=0; c<3; c++))
    do
        for ((c=0; c<$timesToRun; c++))
        do
            ./run.sh $inputFile $outputFile $kernelSize
        done
    done
done