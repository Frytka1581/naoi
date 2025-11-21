#!/bin/bash
set -e

# ==============================
# 🔧 KONFIGURACJA
# ==============================
PROGRAM="${1:-przgrok.cpp}" # plik źródłowy
OUTPUT="${2:-przgrok}"      # plik wykonywalny
NUM_TESTS="${3:-100000}"    # ile testów wygenerować
MAX_TOTAL_LENGTH=40   # maksymalna suma długości wszystkich stron
MIN_LEN=1
MAX_LEN=5
# ==============================

GREEN="\033[32m"
RED="\033[31m"
CYAN="\033[36m"
BOLD="\033[1m"
NC="\033[0m"

# Kompilacja
printf "🔧 Kompiluję ${PROGRAM}...\n"
g++ -O2 -std=c++17 -o "${OUTPUT}" "${PROGRAM}"
printf "✅ Kompilacja zakończona.\n\n"

# Folder testowy
FOLDER="testy"
mkdir -p "$FOLDER"
mkdir -p "bledne2"

for test_id in $(seq 1 $NUM_TESTS); do
    echo "${CYAN}${BOLD}▶️  Test $test_id${NC}"

    # ===== Generowanie testu =====
    IN_FILE="$FOLDER/$test_id.in"
    python3 - <<EOF
import random
import string

max_total_length = $MAX_TOTAL_LENGTH
min_len = $MIN_LEN
max_len = $MAX_LEN

total_len = 0
pages = []

while total_len < max_total_length:
    length = random.randint(min_len, max_len)
    if total_len + length > max_total_length:
        break
    s = ''.join(random.choices(string.ascii_lowercase, k=length))
    pages.append(s)
    total_len += length

with open("$IN_FILE", "w") as f:
    f.write(f"{len(pages)}\\n")
    for p in pages:
        f.write(f"{p}\\n")

print(f"Utworzono test: {len(pages)} stron, suma_dlugosci={total_len}")
EOF

    # ===== Uruchomienie programu =====
    TMP_OUT="$FOLDER/$test_id.out.tmp"
    ./"$OUTPUT" < "$IN_FILE" > "$TMP_OUT"

    # ===== Weryfikacja ciągu =====
    VERIFIER_RESULT=$(python3 - <<EOF
in_file = "$IN_FILE"
out_file = "$TMP_OUT"

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

visited_set = set(visited)
if visited_set == pages_set and len(visited) == n:
    print("OK")
else:
    print("FAIL")
EOF
)

    if [ "$VERIFIER_RESULT" = "OK" ]; then
        echo -e "${GREEN}✅ Weryfikator OK${NC}"
    else
        echo -e "${RED}❌ Weryfikator BŁĄD${NC}"
        # kopiowanie błędnych testów do folderu 'bledne'
        cp "$IN_FILE" bledne2/
        cp "$TMP_OUT" bledne2/
    fi

    echo "───────────────────────────────"
done

echo -e "\n🏁 Testy zakończone. Błędne testy w folderze 'bledne' (jeśli są)."
