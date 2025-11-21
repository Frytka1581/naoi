#!/bin/bash

# generator.sh n k output_path
# Jeśli output_path jest katalogiem → automatycznie tworzy nazwę pliku.
# Jeśli output_path jest plikiem → zapisuje do niego.

if [ "$#" -ne 3 ]; then
  echo "Użycie: $0 <n> <k> <plik|katalog>"
  exit 1
fi

n=$1
k=$2
out=$3

if (( k > n*n )); then
  echo "Za dużo królów!"
  exit 1
fi

# Jeśli out jest katalogiem → generujemy nazwę pliku
if [ -d "$out" ]; then
  mkdir -p "$out"
  out="$out/test_${n}_${k}.in"
fi

# Jeśli rodzicielski katalog nie istnieje → tworzymy
parent=$(dirname "$out")
mkdir -p "$parent"


# === Funkcja: sprawdzanie pozycji króla ===
function can_place() {
  local r=$1
  local c=$2
  for dr in {-1..1}; do
    for dc in {-1..1}; do
      local nr=$((r+dr))
      local nc=$((c+dc))
      if ((nr >= 0 && nr < n && nc >= 0 && nc < n)); then
        if [[ ${board[$((nr*n+nc))]} -ne 0 ]]; then
          return 1
        fi
      fi
    done
  done
  return 0
}

# === Tworzymy pustą planszę początkową ===
board=()
for ((i=0; i<n*n; i++)); do board+=(0); done

# === Losowo rozmieszczamy królów ===
placed=0
while ((placed < k)); do
  r=$((RANDOM % n))
  c=$((RANDOM % n))
  if can_place $r $c; then
    board[$((r*n+c))]=$((placed+1))
    ((placed++))
  fi
done

# === Zapis stanu początkowego ===
{
  echo "$n $k"
  for ((i=0; i<n; i++)); do
    for ((j=0; j<n; j++)); do
      printf "%d " "${board[$((i*n+j))]}"
    done
    echo
  done
} > "$out"


# === Generujemy drugi stan ===

target=()
for ((i=0; i<n*n; i++)); do target+=(0); done

placed=0
while ((placed < k)); do
  r=$((RANDOM % n))
  c=$((RANDOM % n))

  ok=1
  for dr in {-1..1}; do
    for dc in {-1..1}; do
      nr=$((r+dr))
      nc=$((c+dc))
      if ((nr >= 0 && nr < n && nc >= 0 && nc < n)); then
        if [[ ${target[$((nr*n+nc))]} -ne 0 ]]; then
          ok=0
        fi
      fi
    done
  done

  if ((ok)); then
    target[$((r*n+c))]=$((placed+1))
    ((placed++))
  fi
done

# === Dopisujemy końcową planszę ===
{
  for ((i=0; i<n; i++)); do
    for ((j=0; j<n; j++)); do
      printf "%d " "${target[$((i*n+j))]}"
    done
    echo
  done
} >> "$out"

echo "Wygenerowano test: $out"
