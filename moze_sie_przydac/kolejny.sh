#!/usr/bin/env bash
set -eu

# run_batch.sh
# Uruchamia dolazika.sh dla par (n,m) w zakresie 2..1000 (pomija n==m),
# zapisuje logi do /logi/tak lub /logi/nie w zależności od exit code,
# oraz zbiera wyniki w /logi/results.csv.
#
# Jeśli nie masz praw do tworzenia /logi, skrypt przełączy się automatycznie
# na ./logi_fallback.

# ---------- KONFIGURACJA ----------
START_N=2
END_N=1000
START_M=2
END_M=1000

DOLAZIKA="./dolazika.sh"   # ścieżka do skryptu dolazika.sh
LOG_ROOT="/logi"           # główny katalog logów (spróbuje utworzyć /logi)
FALLBACK_LOG_ROOT="./logi_fallback"  # jeśli brak uprawnień do /logi
RESULTS_FILE="results.csv" # nazwa pliku wyników (umieszczona w LOG_ROOT)

# ---------- PRÓBA UTWORZENIA KATALOGU LOG_ROOT ----------
use_fallback=0
if ! mkdir -p "$LOG_ROOT" 2>/dev/null; then
  echo "Uwaga: brak uprawnień do utworzenia $LOG_ROOT — przełączam na fallback: $FALLBACK_LOG_ROOT"
  LOG_ROOT="$FALLBACK_LOG_ROOT"
  use_fallback=1
fi

# teraz utwórz struktury tak/nie
mkdir -p "$LOG_ROOT/tak" "$LOG_ROOT/nie"

# ---------- SPRAWDZENIE dolazika.sh ----------
if [ ! -f "$DOLAZIKA" ]; then
  echo "Nie znaleziono $DOLAZIKA w katalogu. Umieść plik i uruchom ponownie." >&2
  exit 1
fi

if [ ! -x "$DOLAZIKA" ]; then
  DOLAZIKA_RUN="bash $DOLAZIKA"
else
  DOLAZIKA_RUN="$DOLAZIKA"
fi

RESULTS_PATH="${LOG_ROOT}/${RESULTS_FILE}"
# nagłówek results.csv jeśli nie istnieje
if [ ! -f "$RESULTS_PATH" ]; then
  printf "n,m,exit_code,start_iso,end_iso,duration_s,logfile\n" > "$RESULTS_PATH"
fi

echo "Start batch: n=${START_N}..${END_N}, m=${START_M}..${END_M} (pomijam n==m)"
echo "Logi będą zapisywane w: $LOG_ROOT/tak i $LOG_ROOT/nie"
echo "Plik wyników: $RESULTS_PATH"

# ---------- GŁÓWNA PĘTLA ----------
for n in $(seq "$START_N" "$END_N"); do
  for m in $(seq "$START_M" "$END_M"); do
    # pomiń n == m
    if [ "$n" -eq "$m" ]; then
      continue
    fi

    # tymczasowy plik logu (najpierw w katalogu roboczym, potem przeniesiemy)
    tmp_log="$(mktemp "./tmp_log_${n}_${m}.XXXXXX")"
    start_iso=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
    start_ts=$(date +%s)

    echo "==> Uruchamiam: $n $m  (tmp log: $tmp_log)"

    # uruchom dolazika i złap kod powrotu (stdout+stderr do tmp_log)
    if $DOLAZIKA_RUN "$n" "$m" > "$tmp_log" 2>&1; then
      exit_code=0
    else
      exit_code=$?
    fi

    end_iso=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
    end_ts=$(date +%s)
    duration=$(( end_ts - start_ts ))

    # docelowy plik logu (w zależności od exit_code)
    if [ "$exit_code" -eq 0 ]; then
      dest_dir="$LOG_ROOT/tak"
    else
      dest_dir="$LOG_ROOT/nie"
    fi

    dest_log="${dest_dir}/${n}_${m}.log"

    # przenieś tmp_log do dest_log (nadpisz jeśli istnieje)
    mv -f "$tmp_log" "$dest_log"

    # zapisz w results.csv
    # format: n,m,exit_code,start_iso,end_iso,duration_s,logfile
    printf "%s,%s,%d,%s,%s,%d,%s\n" "$n" "$m" "$exit_code" "$start_iso" "$end_iso" "$duration" "$dest_log" >> "$RESULTS_PATH"

    # krótka informacja
    if [ "$exit_code" -eq 0 ]; then
      echo "    Wynik: OK (exit 0), trwało ${duration}s — log: $dest_log"
    else
      echo "    Wynik: ERROR (exit $exit_code), trwało ${duration}s — log: $dest_log"
    fi

  done
done

echo "Gotowe. Wyniki w $RESULTS_PATH. Logi w $LOG_ROOT/tak i $LOG_ROOT/nie."
if [ "$use_fallback" -eq 1 ]; then
  echo "Użyto katalogu zapasowego: $LOG_ROOT (brak uprawnień do /logi)."
fi
