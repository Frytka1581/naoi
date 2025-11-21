import sys

in_file = "bledne/1.in"
out_file = "bledne/1.out.tmp"  # czyli wyjście Twojego programu

# Wczytanie stron z wejścia
with open(in_file) as f:
    n = int(f.readline())
    pages = [f.readline().strip() for _ in range(n)]
    pages_set = set(pages)

# Wczytanie wygenerowanego ciągu klawiszy
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
        # jeśli nie znaleziono, buffer nie zmienia się
    else:
        print("BŁĄD: Nieprawidłowy znak:", ch)
        sys.exit(1)

visited_set = set(visited)

# Sprawdzenie poprawności
if visited_set == pages_set and len(visited) == n:
    print("✅ Wszystkie strony odwiedzone poprawnie!")
else:
    print("❌ BŁĄD w odwiedzinach!")
    print("Oczekiwane strony:", pages)
    print("Odwiedzone strony:", visited)
