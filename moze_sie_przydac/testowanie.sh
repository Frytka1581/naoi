#!/bin/bash
set -e

# ==============================
# 🔧 KONFIGURACJA
# ==============================
PROG1="maksprz.cpp"
PROG2="przgrok.cpp"
OUT1="maksprz"
OUT2="przgrok"
NUM_TESTS=1000
MAX_TOTAL_LENGTH=100
MIN_LEN=1
MAX_LEN=3
FOLDER="testowaniemaksia/in"
BAD_DIR="testowaniemaksia/outzle"
COMPILER="g++-14"        # lub "g++" jeśli nie masz g++-14
USE_VERIFIER=true         # ⬅️ Ustaw na "false", jeśli chcesz pominąć weryfikator
# ==============================

GREEN="\033[32m"
RED="\033[31m"
CYAN="\033[36m"
YELLOW="\033[33m"
BOLD="\033[1m"
NC="\033[0m"

# --- Kompilacja ---
echo "🔧 Kompiluję programy..."
$COMPILER -O2 -std=c++17 "$PROG1" -o "$OUT1"
$COMPILER -O2 -std=c++17 "$PROG2" -o "$OUT2"
echo -e "✅ Kompilacja zakończona.\n"

# --- Przygotowanie folderów ---
mkdir -p "$FOLDER" "$BAD_DIR"

# --- Pętla testów ---
for test_id in $(seq 1 $NUM_TESTS); do
    echo -e "${CYAN}${BOLD}▶️  Test $test_id${NC}"

    IN_FILE="$FOLDER/$test_id.in"
    OUT1_FILE="$FOLDER/$test_id.$OUT1.out"
    OUT2_FILE="$FOLDER/$test_id.$OUT2.out"

    # ===== Generowanie testu =====
    python3 - <<EOF
import random, string
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

    # ===== Uruchomienie obu programów z pomiarem czasu =====
    start1=$(date +%s.%N)
    ./"$OUT1" < "$IN_FILE" > "$OUT1_FILE" 2>/dev/null
    end1=$(date +%s.%N)
    time1=$(awk "BEGIN {print ($end1 - $start1)*1000}")

    start2=$(date +%s.%N)
    ./"$OUT2" < "$IN_FILE" > "$OUT2_FILE" 2>/dev/null
    end2=$(date +%s.%N)
    time2=$(awk "BEGIN {print ($end2 - $start2)*1000}")

    echo -e "${YELLOW}⏱️  Czas wykonania:${NC} $OUT1 = ${time1}ms, $OUT2 = ${time2}ms"

    # ===== Pobranie i oczyszczenie pierwszej linii (koszt) =====
    line1=$(head -n 1 "$OUT1_FILE" | tr -d '[:space:]')
    line2=$(head -n 1 "$OUT2_FILE" | tr -d '[:space:]')

    if [[ "$line1" == "$line2" ]]; then
        echo -e "${GREEN}✅ Koszt zgodny ($line1)${NC}"
    else
        echo -e "${RED}❌ Różne koszty: '$line1' vs '$line2'${NC}"
        cp "$IN_FILE" "$BAD_DIR/${test_id}.in"
        cp "$OUT1_FILE" "$BAD_DIR/${test_id}.${OUT1}.out"
        cp "$OUT2_FILE" "$BAD_DIR/${test_id}.${OUT2}.out"
        continue
    fi

    # ===== Weryfikacja poprawności wyjścia (opcjonalnie) =====
    if [ "$USE_VERIFIER" = true ]; then
        VERIFIER_RESULT=$(python3 - <<EOF
in_file = "$IN_FILE"
out_file = "$OUT1_FILE"

def clean(s):
    return ''.join(s.split())

with open(in_file) as f:
    n = int(f.readline())
    pages = [f.readline().strip() for _ in range(n)]
    pages_set = set(pages)

with open(out_file) as f:
    lines = [l.strip() for l in f if l.strip()]
if not lines:
    print("FAIL")
    exit()
try:
    k = int(lines[0])
    seq = clean(lines[1])
except Exception:
    print("FAIL")
    exit()

visited, buf = [], ""
for ch in seq:
    if 'a' <= ch <= 'z': buf += ch
    elif ch == 'B': buf = buf[:-1] if buf else buf
    elif ch == 'E': visited.append(buf); buf = ""
    elif ch == 'T':
        for prev in reversed(visited):
            if prev.startswith(buf):
                buf = prev
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
            cp "$IN_FILE" "$BAD_DIR/${test_id}.in"
            cp "$OUT1_FILE" "$BAD_DIR/${test_id}.${OUT1}.out"
        fi
    else
        echo -e "${CYAN}ℹ️  Weryfikator wyłączony — pominięto sprawdzanie sekwencji.${NC}"
    fi

    echo "───────────────────────────────"
done

echo -e "\n🏁 Testy zakończone. Błędne w folderze '${BAD_DIR}'."
