#include <bits/stdc++.h>
using namespace std;

const long long MOD1 = 1000000007;
const long long MOD2 = 1000000009;
const long long MOD3 = 998244353;

const long long P1 = 31;
const long long P2 = 37;
const long long P3 = 41;

const int MAXN = 1000000 + 7;

vector<long long> pot1(MAXN, 1), pot2(MAXN, 1), pot3(MAXN, 1);
vector<long long> h1(MAXN), h2(MAXN), h3(MAXN);
vector<long long> h1b(MAXN), h2b(MAXN), h3b(MAXN);

void haszuj(string &s) {
    int n = s.size();
    for (int i = 1; i <= n; i++) {
        pot1[i] = pot1[i - 1] * P1 % MOD1;
        pot2[i] = pot2[i - 1] * P2 % MOD2;
        pot3[i] = pot3[i - 1] * P3 % MOD3;

        h1[i] = (h1[i - 1] + (s[i - 1] - 'a' + 1) * pot1[i]) % MOD1;
        h2[i] = (h2[i - 1] + (s[i - 1] - 'a' + 1) * pot2[i]) % MOD2;
        h3[i] = (h3[i - 1] + (s[i - 1] - 'a' + 1) * pot3[i]) % MOD3;
    }
}

void haszuj_odw(string &s) {
    int n = s.size();
    for (int i = 1; i <= n; i++) {
        h1b[i] = (h1b[i - 1] + (s[i - 1] - 'a' + 1) * pot1[i]) % MOD1;
        h2b[i] = (h2b[i - 1] + (s[i - 1] - 'a' + 1) * pot2[i]) % MOD2;
        h3b[i] = (h3b[i - 1] + (s[i - 1] - 'a' + 1) * pot3[i]) % MOD3;
    }
}

tuple<long long, long long, long long> zwroc(int i, int j, int n) {
    long long x1 = (h1[j] - h1[i - 1] + MOD1) % MOD1 * pot1[n - j] % MOD1;
    long long x2 = (h2[j] - h2[i - 1] + MOD2) % MOD2 * pot2[n - j] % MOD2;
    long long x3 = (h3[j] - h3[i - 1] + MOD3) % MOD3 * pot3[n - j] % MOD3;
    return {x1, x2, x3};
}

tuple<long long, long long, long long> zwroc_odw(int i, int j, int n) {
    long long x1 = (h1b[j] - h1b[i - 1] + MOD1) % MOD1 * pot1[n - j] % MOD1;
    long long x2 = (h2b[j] - h2b[i - 1] + MOD2) % MOD2 * pot2[n - j] % MOD2;
    long long x3 = (h3b[j] - h3b[i - 1] + MOD3) % MOD3 * pot3[n - j] % MOD3;
    return {x1, x2, x3};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();

        string r = s;
        reverse(r.begin(), r.end());

        haszuj(s);
        haszuj_odw(r);

        int wsp = 0;
        while (wsp < n - wsp - 1 && s[wsp] == s[n - wsp - 1])
            wsp++;

        if (wsp * 2 >= n) {
            cout << s << "\n";
            continue;
        }

        int lewy = n - wsp - 1;
        int maks1 = 0, maks2 = 0;

        int i = lewy;
        while (i >= wsp) {
            if (zwroc(wsp + 1, i + 1, n) == zwroc_odw(n - i, n - wsp, n)) break;
            i--;
        }
        maks1 = i - wsp + 1;

        i = wsp;
        while (i <= lewy) {
            if (zwroc(i + 1, lewy + 1, n) == zwroc_odw(n - lewy, n - i, n)) break;
            i++;
        }
        maks2 = lewy - i + 1;

        if (maks1 >= maks2) {
            for (int j = 0; j < wsp + maks1; j++) cout << s[j];
            for (int j = n - wsp; j < n; j++) cout << s[j];
        } else {
            for (int j = 0; j < wsp; j++) cout << s[j];
            for (int j = n - maks2 - wsp; j < n; j++) cout << s[j];
        }
        cout << "\n";
    }
}
