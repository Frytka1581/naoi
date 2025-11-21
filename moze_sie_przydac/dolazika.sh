#!/usr/bin/env bash
set -eu

# usage:
# ./dolazika.sh n m [MAXLEN]
# or
# echo "n m" | ./dolazika.sh

# --- read n and m from args or stdin ---
if [ $# -ge 2 ]; then
  n="$1"
  m="$2"
  shift 2
else
  read -r n m
fi

# set MAXLEN: if user provided a 3rd arg use it, otherwise default to n*m
if [ $# -ge 1 ]; then
  MAXLEN="$1"
else
  MAXLEN=$(( n * m ))
fi

TIMEOUT_SEC="${TIMEOUT_SEC:-1}"
COMPILE_ERRORS_FILE="compile_errors.txt"
COMPILE_ERRORS_REF="compile_errors_ref.txt"

# --- compilers to try (priority) ---
compilers=(g++-14 g++-13 g++-12 g++ clang++)
CC=""
for c in "${compilers[@]}"; do
  if command -v "$c" >/dev/null 2>&1; then
    CC="$c"
    break
  fi
done

# --- detect timeout command (coreutils timeout or gtimeout on mac) ---
TIMEOUT_CMD=""
if command -v timeout >/dev/null 2>&1; then
  TIMEOUT_CMD="timeout"
elif command -v gtimeout >/dev/null 2>&1; then
  TIMEOUT_CMD="gtimeout"
else
  TIMEOUT_CMD=""
fi

# --- portable repeat char ---
repeat_char() {
  local char="$1"
  local count="$2"
  if [ "$count" -le 0 ]; then
    printf ''
  else
    printf '%*s' "$count" '' | tr ' ' "$char"
  fi
}

# --- check & compile lazik.cpp ---
if [ -f "lazik.cpp" ]; then
  if [ -z "$CC" ]; then
    echo "Nie znaleziono g++/clang++ w systemie. Zainstaluj kompilator lub umieść binarkę ./lazik." >&2
    exit 2
  fi

  echo "Kompiluję lazik.cpp przy użyciu '$CC'..."
  if ! "$CC" -std=c++17 -O2 -Wall -Wextra lazik.cpp -o lazik 2> "$COMPILE_ERRORS_FILE"; then
    echo "Błąd kompilacji lazik.cpp (zapisano do $COMPILE_ERRORS_FILE)." >&2
    echo ">>> Pierwsze 200 linii błędów kompilatora (lazik):"
    sed -n '1,200p' "$COMPILE_ERRORS_FILE" || true
    echo "Wklej tutaj początek $COMPILE_ERRORS_FILE jeśli chcesz pomocy z debugiem."
    exit 2
  fi
else
  echo "Brak pliku lazik.cpp w katalogu. Umieść plik i spróbuj ponownie." >&2
  exit 2
fi

# --- check & compile ref.cpp (wzorzec) ---
if [ -f "ref.cpp" ]; then
  if [ -z "$CC" ]; then
    echo "Nie znaleziono g++/clang++ w systemie. Zainstaluj kompilator lub umieść binarkę ./ref." >&2
    exit 2
  fi

  echo "Kompiluję ref.cpp (wzorzec) przy użyciu '$CC'..."
  if ! "$CC" -std=c++17 -O2 -Wall -Wextra ref.cpp -o ref 2> "$COMPILE_ERRORS_REF"; then
    echo "Błąd kompilacji ref.cpp (zapisano do $COMPILE_ERRORS_REF)." >&2
    echo ">>> Pierwsze 200 linii błędów kompilatora (ref):"
    sed -n '1,200p' "$COMPILE_ERRORS_REF" || true
    echo "Wklej tutaj początek $COMPILE_ERRORS_REF jeśli chcesz pomocy z debugiem."
    exit 2
  fi
else
  echo "Brak pliku ref.cpp (wzorzec). Aby porównać odpowiedź, umieść plik ref.cpp w katalogu." >&2
  exit 2
fi

# --- check executables ---
if [ ! -x "./lazik" ]; then
  echo "Brak wykonalnego ./lazik. Upewnij się, że skompilowano lazik.cpp." >&2
  exit 3
fi
if [ ! -x "./ref" ]; then
  echo "Brak wykonalnego ./ref. Upewnij się, że skompilowano ref.cpp." >&2
  exit 3
fi

echo "Start brute-force (n=$n m=$m maxlen=$MAXLEN, timeout=${TIMEOUT_SEC}s, timeout_cmd='${TIMEOUT_CMD:-none}')..."

# --- main brute loop: generujemy D^a P^b dla len=2..MAXLEN ---
for (( len=2; len<=MAXLEN; len++ )); do
  for (( b=1; b<=len-1; b++ )); do
    a=$((len - b))
    prefix=$(repeat_char D "$a")
    suffix=$(repeat_char P "$b")
    instr="${prefix}${suffix}"

    prog_input="$n $m $len"$'\n'"$instr"$'\n'

    out=""
    if [ -n "$TIMEOUT_CMD" ]; then
      if out=$(printf "%s" "$prog_input" | "$TIMEOUT_CMD" "${TIMEOUT_SEC}"s ./lazik 2>/dev/null); then
        :
      else
        # timed out or non-zero exit: skip this instr
        continue
      fi
    else
      # no timeout tool: run directly (may block)
      if out=$(printf "%s" "$prog_input" | ./lazik 2>/dev/null); then
        :
      else
        continue
      fi
    fi

    # normalize: first non-empty output line (strip CR)
    out_trimmed="$(printf "%s" "$out" | tr -d '\r' | awk 'NF{print; exit}')"
    if printf "%s\n" "$out_trimmed" | grep -iqFx "TAK"; then
      echo "Znaleziono instrukcję (lazik) długości len=$len"

      # --- run ref and extract first non-empty line (k) robustly using awk ---
      ref_out="$(printf "%s %s\n" "$n" "$m" | ./ref 2>/dev/null || true)"
      ref_k_line="$(printf "%s\n" "$ref_out" | tr -d '\r' | awk 'NF{print; exit}')"
      # trim whitespace and try to parse integer
      ref_k="$(printf "%s" "$ref_k_line" | awk '{$1=$1;print}')"

      # validate ref_k is an integer number
      if ! printf "%s" "$ref_k" | grep -Eq '^[0-9]+$'; then
        echo "Nieoczekiwany format odpowiedzi ref (k): '$ref_k_line'" >&2
        diag_dir="diag_$(date +%s)"
        mkdir -p "$diag_dir"
        printf "%s" "$prog_input" > "$diag_dir/input_brute.txt"
        printf "%s\n" "$out" > "$diag_dir/out_lazik.txt"
        printf "%s\n" "$ref_out" > "$diag_dir/out_ref.txt"
        echo "Zapisano diagnostykę w katalogu: $diag_dir" >&2
        exit 6
      fi

      # numeric comparison
      if [ "$len" -eq "$ref_k" ]; then
        echo "WYNIK: długość znaleziona przez brute (len=$len) zgadza się z k=$ref_k ze wzorca."
        echo "$n $m"
        exit 0
      else
        echo "WYNIK NIE ZGADZA SIĘ: brute len=$len, ref k=$ref_k" >&2
        diag_dir="diag_$(date +%s)"
        mkdir -p "$diag_dir"
        printf "%s" "$prog_input" > "$diag_dir/input_brute.txt"
        printf "%s\n" "$out" > "$diag_dir/out_lazik.txt"
        printf "%s\n" "$ref_out" > "$diag_dir/out_ref.txt"
        echo "Zapisano diagnostykę w katalogu: $diag_dir" >&2
        exit 5
      fi
    fi
  done
done

echo "Nie znaleziono rozwiązania do długości $MAXLEN." >&2
exit 4
