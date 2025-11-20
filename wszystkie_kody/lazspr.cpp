#include <bits/stdc++.h>
using namespace std;

inline int fast_gcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}
inline bool coprime(int a, int b) { return fast_gcd(a, b) == 1; }

string generuj_instrukcje(int n, int m) {
    int k = fast_gcd(n, m);
    if (n == m) {
        string s = "P";
        s.append(n - 1, 'D');
        return to_string(n) + '\n' + s;
    }
    if (k == 1) return "2\nDP";

    int l = 0, r = 0;
    for (int i = 1; i < k; ++i)
        if (coprime(n, i) && coprime(k - i, m)) { l = i; r = k - i; break; }

    string res = to_string(k) + '\n';
    if (l && r) {
        res.append(l, 'D');
        res.append(r, 'P');
    } else {
        char first = (n < m) ? 'D' : 'P';
        char second = (first == 'D') ? 'P' : 'D';
        if ((n < m ? n : m) % (k - 1) != 0) {
            res.append(k - 1, first);
            res += second;
        } else {
            res.append(k - 1, second);
            res += first;
        }
    }
    return res;
}

string sprawdz(long long n, long long m, const string& instr) {
    const size_t L = instr.size();
    const long long limit = n * m * L;
    vector<char> visited(n * m * L, 0);
    long long x = 0, y = 0, idx = 0;
    long long visited_cnt = 1;

    auto hash = [&](long long xx, long long yy, long long ii) {
        return xx * m * L + yy * L + ii;
    };
    visited[hash(0,0,0)] = 1;

    for (long long step = 0; step < limit; ++step) {
        char c = instr[idx % L];
        if (c == 'D') ++x;
        else if (c == 'P') ++y;
        x %= n; y %= m;
        ++idx;

        long long h = hash(x, y, idx % L);
        if (visited[h]) break;
        visited[h] = 1;
        ++visited_cnt;

        if (visited_cnt == n * m) return "TAK";
    }
    return "NIE";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int SIGMA, LIGMA, L2, L3;
    cin >> SIGMA >> LIGMA >> L2 >> L3;

    ofstream out_file("zle.in");
    if (!out_file.is_open()) {
        cerr << "Błąd: Nie można otworzyć pliku zle.in do zapisu!\n";
        return 1;
    }

    const long long total = (SIGMA - L2 + 1LL) * (LIGMA - L3 + 1LL);
    long long done = 0;
    bool all_ok = true;
    pair<int,int> first_bad = {0,0};

    const int bar_len = 50;
    string bar(bar_len, ' ');
    cout << "Progress: [" << bar << "] 0.00%\r" << flush;

    for (int n = L2; n <= SIGMA; ++n) {
        for (int m = L3; m <= LIGMA; ++m) {
            string raw = generuj_instrukcje(n, m);
            string instr = raw.substr(raw.find('\n') + 1);
            string verdict = sprawdz(n, m, instr);

            if (verdict == "NIE") {
                all_ok = false;
                if (first_bad.first == 0) first_bad = {n, m};
                cout << "\nBŁĄD: n=" << n << " m=" << m << "  instrukcje=\"" << instr << "\"\n";
                out_file << n << " " << m << " " << instr << "\n";
            }

            ++done;
            if (done % 128 == 0 || done == total) {
                double perc = 100.0 * done / total;
                int pos = static_cast<int>(bar_len * done / total);
                fill(bar.begin(), bar.begin() + pos, '#');
                fill(bar.begin() + pos, bar.end(), ' ');
                cout << "Progress: [" << bar << "] "
                     << fixed << setprecision(2) << perc << "%\r" << flush;
            }
        }
    }
    out_file.close();
    cout << "\n";
    if (all_ok) cout << "Wszystkie pary poprawne!\n";
    else        cout << "Pierwsza błędna para: n=" << first_bad.first
                     << " m=" << first_bad.second << '\n';
}