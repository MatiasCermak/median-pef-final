#!/usr/bin/env bash

programArgs = $1
timesToRun = $2


for ((c=0; c<3; c++))
do
    for ((c=0; c<3; c++))
    do
        for ((c=0; c<$timesToRun; c++))
        do
            ./$outputExec $programArgs
        done
    done
done