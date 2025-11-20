#!/bin/bash

for((i = 0; i < 1000000; i++))
do
    echo "$i" > ziarno
    python3 gener.py < ziarno > wejscie.in
    python3 brut.py < wejscie.in > brutOut.out
    python3 wzor.py < wejscie.in > wzorOut.out
    if diff -n -b brutOut.out wzorOut.out
    then
        echo "Ok $i"
    else
        echo "NIEEEE $i"
        exit
    fi
done