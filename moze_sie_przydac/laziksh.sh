#!/bin/bash

# Utwórz katalogi jeśli nie istnieją
mkdir -p essa/dobre
mkdir -p essa/zle

# Kompilacja programów w C++17
g++ -std=c++17 -O2 laz.cpp -o laz
if [ $? -ne 0 ]; then
    echo "Błąd kompilacji laz.cpp"
    exit 1
fi

g++ -std=c++17 -O2 arturaczyste.cpp -o arturaczyste
if [ $? -ne 0 ]; then
    echo "Błąd kompilacji arturaczyste.cpp"
    exit 1
fi

# Zakres testów
lewy=2
prawy=2
MAX=1000000
NUM_TESTS=10000000  # liczba losowych testów

for ((i=1; i<=NUM_TESTS; i++)); do
    # Losuj n i m w zakresie
    n=$((RANDOM % (MAX - lewy + 1) + lewy))
    m=$((RANDOM % (MAX - prawy + 1) + prawy))
    
    # Pomijamy jeśli nwd(n,m) == 1
    gcd=$(python3 -c "import math; print(math.gcd($n,$m))")
    if [ "$gcd" -eq 1 ]; then
        continue
    fi

    # Uruchom laz i złap jego wyjście
    wynik=$(echo -e "$n $m" | ./laz)
    
    # Uruchom arturaczyste z wynikami laz
    score_output=$(echo -e "$n $m $wynik" | ./arturaczyste)
    
    # Przygotuj nazwę pliku do zapisania testu
    filename="test_n${n}_m${m}.txt"
    
    # Sprawdź, czy score jest 100
    if echo "$score_output" | grep -q "score: 100%"; then
        echo "n=$n m=$m -> SCORE 100"
        # Zapisz test w katalogu essa/dobre
        echo -e "$n $m\n$wynik" > "essa/dobre/$filename"
    else
        echo "n=$n m=$m -> NIE 100"
        # Zapisz test w katalogu essa/zle
        echo -e "$n $m\n$wynik" > "essa/zle/$filename"
    fi
done
