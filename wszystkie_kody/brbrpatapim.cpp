#include <bits/stdc++.h>
using namespace std;

const long long MOD1 = 1e9 + 7;
const long long MOD2 = 998244353;
const long long p = 31;
vector<long long> potegi(21, 1); // Maksymalna długość słowa to 20

// Funkcja obliczająca hash dla całego napisu (podwójne hashowanie)
pair<long long, long long> nazwa(const string& napis) {
    long long hash1 = 0, hash2 = 0;
    for (int i = 0; i < napis.length(); ++i) {
        // Używamy pełnej wartości ASCII znaku, bez przesunięcia
        hash1 = (hash1 * p + napis[i]) % MOD1;
        hash1 = (hash1 + MOD1) % MOD1;
        hash2 = (hash2 * p + napis[i]) % MOD2;
        hash2 = (hash2 + MOD2) % MOD2;
    }
    return {hash1, hash2};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // Wczytaj n
    int n;
    cin >> n;

    // Oblicz potęgi p (dla zgodności z Twoim kodem, choć nie używamy ich wprost)
    for (int i = 1; i <= 20; ++i) {
        potegi[i] = (potegi[i - 1] * p) % MOD1;
        potegi[i] = (potegi[i] + MOD1) % MOD1;
    }

    // Mapa: hash -> wektor par {napis, licznik} do obsługi kolizji
    unordered_map<long long, vector<pair<string, int>>> hash_map;

    // Wczytaj n napisów i zlicz ich wystąpienia
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        long long h1 = nazwa(s).first; // Używamy pierwszego hasha jako klucza
        bool found = false;
        for (auto& p : hash_map[h1]) {
            if (p.first == s) {
                p.second++;
                found = true;
                break;
            }
        }
        if (!found) {
            hash_map[h1].push_back({s, 1});
        }
    }

    // Wczytaj q zapytań
    int q;
    cin >> q;

    // Przetwarzaj q zapytań
    for (int i = 0; i < q; ++i) {
        string s;
        cin >> s;
        long long h1 = nazwa(s).first;
        int count = 0;
        for (const auto& p : hash_map[h1]) {
            if (p.first == s) {
                count = p.second;
                break;
            }
        }
        cout << count << "\n";
    }

    return 0;
}