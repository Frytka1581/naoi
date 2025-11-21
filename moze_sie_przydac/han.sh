#!/bin/bash
set -e

# ==============================
# 🔧 KONFIGURACJA
# ==============================
PROG1="han.cpp"
PROG2="hankus.cpp"
PROG3="mkohan.cpp"
OUT1="han"
OUT2="hankus"
OUT3="mkohan"

NUM_TESTS=1000
MAX_N=3  # maksymalne n (<= 1_000_000 w zadaniu)
MAX_M=3         # maksymalne m (<= n)
FOLDER="testy_han/in"
BAD_DIR="testy_han/out_zle"
COMPILER="g++-14"  # lub "g++" jeśli nie masz g++-14
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
$COMPILER -O2 -std=c++17 "$PROG3" -o "$OUT3"
echo -e "✅ Kompilacja zakończona.\n"

mkdir -p "$FOLDER" "$BAD_DIR"

# --- Pętla testów ---
for test_id in $(seq 1 $NUM_TESTS); do
    echo -e "${CYAN}${BOLD}▶️  Test $test_id${NC}"

    IN_FILE="$FOLDER/$test_id.in"
    OUT1_FILE="$FOLDER/$test_id.$OUT1.out"
    OUT2_FILE="$FOLDER/$test_id.$OUT2.out"
    OUT3_FILE="$FOLDER/$test_id.$OUT3.out"

    # ===== Generowanie testu =====
    python3 - <<EOF
import random

MAX_N = $MAX_N
MAX_M = $MAX_M

n = random.randint(2, MAX_N)
m = random.randint(2, min(n, MAX_M))

# Generujemy permutację 1..n
blocks = list(range(1, n + 1))
random.shuffle(blocks)

# Tworzymy m pustych stosów
piles = [[] for _ in range(m)]
for b in blocks:
    piles[random.randint(0, m - 1)].append(b)

# Każdy stos posortowany rosnąco
for pile in piles:
    pile.sort()

with open("$IN_FILE", "w") as f:
    f.write(f"{n} {m}\\n")
    for pile in piles:
        f.write(str(len(pile)))
        if pile:
            f.write(" " + " ".join(map(str, pile)))
        f.write("\\n")
EOF

    # ===== Uruchamianie programów =====
    run_and_time() {
        local exe="$1"
        local infile="$2"
        local outfile="$3"
        local start=$(date +%s.%N)
        ./"$exe" < "$infile" > "$outfile" 2>/dev/null
        local end=$(date +%s.%N)
        awk "BEGIN {print ($end - $start)*1000}"
    }

    time1=$(run_and_time "$OUT1" "$IN_FILE" "$OUT1_FILE")
    time2=$(run_and_time "$OUT2" "$IN_FILE" "$OUT2_FILE")
    time3=$(run_and_time "$OUT3" "$IN_FILE" "$OUT3_FILE")

    echo -e "${YELLOW}⏱️  Czas:${NC} $OUT1=${time1}ms, $OUT2=${time2}ms, $OUT3=${time3}ms"

    # ===== Porównanie kosztów (tylko 1 linia) =====
    cost1=$(head -n 1 "$OUT1_FILE" | tr -d '[:space:]')
    cost2=$(head -n 1 "$OUT2_FILE" | tr -d '[:space:]')
    cost3=$(head -n 1 "$OUT3_FILE" | tr -d '[:space:]')

    if [[ "$cost1" == "$cost2" && "$cost1" == "$cost3" ]]; then
        echo -e "${GREEN}✅ Koszty zgodne: $cost1${NC}"
    else
        echo -e "${RED}⚠️  Różne koszty: $cost1 / $cost2 / $cost3${NC}"
        cp "$IN_FILE" "$BAD_DIR/${test_id}.in"
        cp "$OUT1_FILE" "$BAD_DIR/${test_id}.${OUT1}.out"
        cp "$OUT2_FILE" "$BAD_DIR/${test_id}.${OUT2}.out"
        cp "$OUT3_FILE" "$BAD_DIR/${test_id}.${OUT3}.out"
    fi

    # ===== Weryfikator poprawności =====
    for prog in "$OUT1" "$OUT2" "$OUT3"; do
        OUT_FILE="$FOLDER/$test_id.$prog.out"
        VER_RESULT=$(python3 - "$IN_FILE" "$OUT_FILE" <<'PYCODE'
import sys

def verify(in_path, out_path):
    try:
        with open(in_path) as f:
            n, m = map(int, f.readline().split())
            piles = []
            for _ in range(m):
                arr = list(map(int, f.readline().split()))
                k = arr[0]
                seq = arr[1:] if k else []
                piles.append(seq)

        with open(out_path) as f:
            lines = [l.strip() for l in f if l.strip()]
        if not lines:
            return False
        try:
            cost = int(lines[0])
        except:
            return False

        # Weryfikacja danych wejściowych – wszystkie klocki muszą być różne
        all_blocks = [b for pile in piles for b in pile]
        if sorted(all_blocks) != list(range(1, n + 1)):
            return False
        return True
    except Exception:
        return False

ok = verify(sys.argv[1], sys.argv[2])
print("OK" if ok else "FAIL")
PYCODE
)
        if [[ "$VER_RESULT" == "OK" ]]; then
            echo -e "${GREEN}✅ Weryfikator $prog: OK${NC}"
        else
            echo -e "${RED}❌ Weryfikator $prog: FAIL${NC}"
            cp "$IN_FILE" "$BAD_DIR/${test_id}.in"
            cp "$OUT_FILE" "$BAD_DIR/${test_id}.${prog}.out"
        fi
    done

    echo "───────────────────────────────"
done

echo -e "\n🏁 Testy zakończone. Wyniki błędne w folderze '${BAD_DIR}'."
