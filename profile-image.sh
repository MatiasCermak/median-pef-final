#!/bin/bash

inputFile=$1;
kernelSize=$2;
filterIterations=$3;
timesToRun=$4;

for ((c=0; c<3; c++))
do
    for ((d=0; d<$timesToRun; d++))
    do
        ./run.sh $inputFile "output"-$inputFile $kernelSize $c $filterIterations
    done
    echo " "
done
