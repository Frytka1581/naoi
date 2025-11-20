#include <bits/stdc++.h>
using namespace std;

const int P1 = 31, P2 = 53, P3 = 97;
const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9, MOD3 = 1e9 + 21;

vector<long long> h1, h2, h3;
vector<long long> pow1, pow2, pow3;

// Precompute hashów prefiksowych i potęg dla stringa s
void compute_hashes(const string &s) {
    int n = s.size();
    h1.assign(n + 1, 0);
    h2.assign(n + 1, 0);
    h3.assign(n + 1, 0);
    pow1.assign(n + 1, 1);
    pow2.assign(n + 1, 1);
    pow3.assign(n + 1, 1);

    for (int i = 0; i < n; ++i) {
        int val = s[i] - 'a' + 1;
        h1[i + 1] = (h1[i] + val * pow1[i]) % MOD1;
        h2[i + 1] = (h2[i] + val * pow2[i]) % MOD2;
        h3[i + 1] = (h3[i] + val * pow3[i]) % MOD3;

        pow1[i + 1] = (pow1[i] * P1) % MOD1;
        pow2[i + 1] = (pow2[i] * P2) % MOD2;
        pow3[i + 1] = (pow3[i] * P3) % MOD3;
    }
}

// Funkcja zwraca hash substringa s[l..r] w O(1)
tuple<long long, long long, long long> get_hash(int l, int r) {
    long long sub_h1 = (h1[r + 1] - h1[l] + MOD1) % MOD1;
    sub_h1 = (sub_h1 * pow1[pow1.size() - 1 - l]) % MOD1; // opcjonalne dopasowanie potęgi

    long long sub_h2 = (h2[r + 1] - h2[l] + MOD2) % MOD2;
    sub_h2 = (sub_h2 * pow2[pow2.size() - 1 - l]) % MOD2;

    long long sub_h3 = (h3[r + 1] - h3[l] + MOD3) % MOD3;
    sub_h3 = (sub_h3 * pow3[pow3.size() - 1 - l]) % MOD3;

    return {sub_h1, sub_h2, sub_h3};
}

int main() {
    string s = "abaaaa";
    compute_hashes(s);

    // porównanie "abaa" w s[0..3] z substringiem "abaa"
    string t = "abaac";
    compute_hashes(t);
    auto hash_s = get_hash(0, 3);
    auto hash_t = get_hash(0, t.size() - 1);

    if (hash_s == hash_t)
        cout << "Substringy są takie same\n";
    else
        cout << "Substringy różne\n";

    return 0;
}
