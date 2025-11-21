import os
import random
import string

# KONFIGURACJA
folder = "testy"
num_tests = 1000       # liczba plików testowych
min_n = 1_000_000      # minimalna liczba stron
max_n = 1_000_000      # maksymalna liczba stron
min_len = 100            # minimalna długość strony
max_len = 1000          # maksymalna długość strony
max_total_length = int(1e6)  # maksymalna suma długości wszystkich stron

# Utwórz folder, jeśli nie istnieje
os.makedirs(folder, exist_ok=True)

for test_id in range(1, num_tests + 1):
    n = random.randint(min_n, max_n)
    pages = []
    total_length = 0

    for _ in range(n):
        length = random.randint(min_len, max_len)
        if total_length + length > max_total_length:
            break  # przerywamy generowanie nowych stron
        s = ''.join(random.choices(string.ascii_lowercase, k=length))
        pages.append(s)
        total_length += length

    filename = os.path.join(folder, f"{test_id}.in")
    with open(filename, "w") as f:
        f.write(f"{len(pages)}\n")  # faktyczna liczba stron w tym teście
        for page in pages:
            f.write(f"{page}\n")

    print(f"Utworzono test: {filename} (n={len(pages)}, suma_dlugosci={total_length})")
