#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<i64> sito(i64 n) {
    vector<i64> najmniejszy_dzielnik(n + 1, 0);
    vector<i64> liczba_czynnikow(n + 1, 0);

    for (i64 i = 2; i <= n; ++i) {
        if (najmniejszy_dzielnik[i] == 0) {
            for (i64 j = i; j <= n; j += i) {
                if (najmniejszy_dzielnik[j] == 0) {
                    najmniejszy_dzielnik[j] = i;
                }
                liczba_czynnikow[j]++;
            }
        }
    }
    return liczba_czynnikow;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    const i64 MAX_N = 1e7;
    vector<i64> liczba_czynnikow = sito(MAX_N);

    i64 n, a;
    cin >> n;
    for (i64 i = 1; i < MAX_N; ++i) {
        liczba_czynnikow[i] += liczba_czynnikow[i - 1];
    }
    for (i64 i = 0; i < n; ++i) {
        cin >> a;
        cout << liczba_czynnikow[a] << endl;
    }

    return 0;
}
