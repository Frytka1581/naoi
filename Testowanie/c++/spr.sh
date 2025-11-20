#!/bin/bash

for((i = 0; i < 1000000; i++))
do
    echo "$i" > ziarno
    ./gener < ziarno > wejscie.in
    ./brut < wejscie.in > brutOut.out
    ./wzor < wejscie.in > wzorOut.out
    if diff -n -b brutOut.out wzorOut.out
    then
        echo "Ok $i"
    else
        echo "NIEEEE $i"
        exit
    fi
done