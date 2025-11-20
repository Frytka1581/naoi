#!/bin/bash

# Sprawdzamy, czy podano plik jako argument
if [ -z "$1" ]; then
  echo "Użycie: $0 <nazwa_pliku.cpp>"
  exit 1
fi

# Pobieramy nazwę pliku (bez rozszerzenia)
plik=$(basename "$1" .cpp)

# Ustawiamy odpowiednie zmienne środowiskowe, jeśli są potrzebne
export PATH="/opt/homebrew/opt/gcc/bin:$PATH"
export LIBRARY_PATH="/opt/homebrew/opt/gcc/lib/gcc/14"
export LD_LIBRARY_PATH="/opt/homebrew/opt/gcc/lib/gcc/14:$LD_LIBRARY_PATH"

# Kompilujemy kod i uruchamiamy program
g++-14 -o "$plik" "$1" && ./"$plik" < test.in
