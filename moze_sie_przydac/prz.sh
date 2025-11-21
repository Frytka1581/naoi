#!/bin/bash
set -e

# ==============================
# 🔧 KONFIGURACJA — do wpisania / zmiany
# ==============================
FOLDER="${1:-bledne}"        # 📁 folder z testami (.in / .out)
PROGRAM="${2:-przgrok.cpp}" # 💻 plik źródłowy do kompilacji
OUTPUT="${3:-przgrok}"      # 🧱 nazwa pliku wykonywalnego po kompilacji
LINES="${4:-1}"             # 🔹 ile linii wyjścia pokazywać i porównywać (use 'all' for everything)
# ==============================

printf "🔧 Kompiluję ${PROGRAM}...\n"
g++ -O2 -std=c++17 -o "${OUTPUT}" "${PROGRAM}"
printf "✅ Kompilacja zakończona pomyślnie.\n\n"

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
CYAN="\033[36m"
BOLD="\033[1m"
NC="\033[0m"

# Sprawdzenie folderu
if [ ! -d "$FOLDER" ]; then
    printf "${RED}❌ Folder testów '${FOLDER}' nie istnieje.${NC}\n"
    exit 1
fi

found_any=false
any_error=false

for in_file in "$FOLDER"/*.in; do
    [ -e "$in_file" ] || continue
    found_any=true
    base_name=$(basename "$in_file" .in)
    tmp_out="${FOLDER}/${base_name}.out.tmp"

    printf "${CYAN}${BOLD}▶️  Test: ${base_name}${NC}\n"

    start_time=$(date +%s%N)
    ./"${OUTPUT}" < "$in_file" | tr -d '\r' > "$tmp_out"
    end_time=$(date +%s%N)
    elapsed_ms=$(( (end_time - start_time) / 1000000 ))

    # Pokaż wyjście programu
    echo "🔹 Wyjście programu:"
    if [ "$LINES" = "all" ]; then
        sed 's/[[:space:]]*$//' "$tmp_out"
    else
        head -n "$LINES" "$tmp_out" | sed 's/[[:space:]]*$//'
    fi

    # Weryfikacja ciągu klawiszy Pythonem
    verifier_output=$(python3 - <<EOF
import sys

in_file = "$in_file"
out_file = "$tmp_out"

try:
    with open(in_file) as f:
        n = int(f.readline())
        pages = [f.readline().strip() for _ in range(n)]
        pages_set = set(pages)

    with open(out_file) as f:
        k = int(f.readline())
        seq = f.readline().strip()

    visited = []
    buffer = ""

    for ch in seq:
        if 'a' <= ch <= 'z':
            buffer += ch
        elif ch == 'B':
            if buffer:
                buffer = buffer[:-1]
        elif ch == 'E':
            visited.append(buffer)
            buffer = ""
        elif ch == 'T':
            found = False
            for prev in reversed(visited):
                if prev.startswith(buffer):
                    buffer = prev
                    found = True
                    break
        else:
            print("VERIFIER_ERROR")
            print("Nieprawidłowy znak:", ch)
            sys.exit(0)

    visited_set = set(visited)

    if visited_set == pages_set and len(visited) == n:
        print("VERIFIER_OK")
    else:
        print("VERIFIER_ERROR")
        print("Odwiedzone:", visited)
        print("Oczekiwane:", pages)

except Exception as e:
    print("VERIFIER_ERROR")
    print("Wyjątek:", str(e))
EOF
)

    if echo "$verifier_output" | grep -q "^VERIFIER_OK"; then
        printf "${GREEN}✅ Weryfikator: OK${NC} (%d ms)\n" "$elapsed_ms"
    else
        printf "${RED}❌ Weryfikator: BŁĄD${NC} (%d ms)\n" "$elapsed_ms"
        echo "$verifier_output" | tail -n +2
        any_error=true
    fi

    echo "───────────────────────────────"
done

if [ "$found_any" = false ]; then
    printf "${YELLOW}⚠️  Brak plików .in w folderze ${FOLDER}.${NC}\n"
    exit 1
fi

if [ "$any_error" = true ]; then
    printf "\n🏁 Testy zakończone z błędami.\n"
    exit 1
else
    printf "\n🏁 Testy zakończone.\n"
    exit 0
fi
