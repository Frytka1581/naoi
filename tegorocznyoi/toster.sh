#!/bin/bash
set -e

# ==============================
# 🔧 KONFIGURACJA — do wpisania / zmiany
# ==============================
FOLDER="${1:-smol}"        # 📁 folder z testami (.in / .out)
PROGRAM="${2:-han.cpp}" # 💻 plik źródłowy do kompilacji
OUTPUT="${3:-han}"      # 🧱 nazwa pliku wykonywalnego po kompilacji
LINES="${4:-1}"             # 🔹 ile linii wyjścia pokazywać i porównywać (use 'all' for everything)
# ==============================

# 🔧 DODANE: folder z błędnymi testami
BAD_FOLDER="zle"
mkdir -p "$BAD_FOLDER"

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

for in_file in "$FOLDER"/*.in; do
    [ -e "$in_file" ] || continue   # pomija brak plików .in
    found_any=true
    base_name=$(basename "$in_file" .in)
    out_file="${FOLDER}/${base_name}.out"
    tmp_out="${FOLDER}/${base_name}.out.tmp"

    printf "${CYAN}${BOLD}▶️  Test: ${base_name}${NC}\n"

    start_time=$(date +%s%N)
    ./"${OUTPUT}" < "$in_file" | tr -d '\r' > "$tmp_out"
    end_time=$(date +%s%N)
    elapsed_ms=$(( (end_time - start_time) / 1000000 ))

    echo "🔹 Wyjście programu:"
    if [ "$LINES" = "all" ]; then
        sed 's/[[:space:]]*$//' "$tmp_out"
    else
        head -n "$LINES" "$tmp_out" | sed 's/[[:space:]]*$//'
    fi

    if [ -f "$out_file" ]; then
        if diff -u -b -B <(tr -d '\r' < "$out_file" | sed 's/[[:space:]]*$//') \
                        <(sed 's/[[:space:]]*$//' "$tmp_out") > /dev/null 2>&1; then
            printf "${GREEN}✅ %s OK${NC} (%d ms)\n" "$base_name" "$elapsed_ms"
        else
            printf "${RED}❌ %s BŁĄD${NC} (%d ms)\n" "$base_name" "$elapsed_ms"
            echo "🔹 Oczekiwane wyjście:"
            if [ "$LINES" = "all" ]; then
                sed 's/[[:space:]]*$//' "$out_file"
            else
                head -n "$LINES" "$out_file" | sed 's/[[:space:]]*$//'
            fi

            echo "🔹 Różnice:"
            if [ "$LINES" = "all" ]; then
                diff -u -b -B <(tr -d '\r' < "$out_file" | sed 's/[[:space:]]*$//') \
                                <(sed 's/[[:space:]]*$//' "$tmp_out")
            else
                diff -u -b -B <(tr -d '\r' < "$out_file" | sed 's/[[:space:]]*$//') \
                                <(head -n "$LINES" "$tmp_out" | sed 's/[[:space:]]*$//')
            fi

            # 🔥 DODANE: zapis błędnego testu
            cp "$in_file" "$BAD_FOLDER/${base_name}.in"
            cp "$tmp_out" "$BAD_FOLDER/${base_name}.out"          # faktyczne wyjście
            cp "$out_file" "$BAD_FOLDER/${base_name}.expected"    # oczekiwane

            printf "${YELLOW}📁 Zapisano błędny test do folderu '${BAD_FOLDER}'.${NC}\n"
            exit 1
        fi
    else
        printf "${YELLOW}⚠️  Brak oczekiwanego pliku wyjścia dla %s${NC}\n" "$base_name"
        exit 1
    fi

    echo "───────────────────────────────"
done

if [ "$found_any" = false ]; then
    printf "${YELLOW}⚠️  Brak plików .in w folderze ${FOLDER}.${NC}\n"
    exit 1
fi

printf "\n🏁 Testy zakończone.\n"
