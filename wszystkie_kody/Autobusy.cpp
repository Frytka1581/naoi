#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<long long> bilety(n);
    vector<long long> trasy(k);
    vector<long long> sumy_prefiksowe(k + 1);

    for (int i = 0; i < n; ++i) {
        cin >> bilety[i];
    }

    sumy_prefiksowe[0] = 0;
    for (int i = 0; i < k; ++i) {
        cin >> trasy[i];
        sumy_prefiksowe[i + 1] = sumy_prefiksowe[i] + trasy[i];
    }

    vector<int> dp(1 << n, 0);
    vector<long long> suma_biletow(1 << n, 0);

    for (int maska = 0; maska < (1 << n); ++maska) {
        for (int j = 0; j < n; ++j) {
            if (!(maska & (1 << j))) {
                long long czas_biletu = bilety[j];
                auto it = upper_bound(sumy_prefiksowe.begin(), sumy_prefiksowe.end(), sumy_prefiksowe[dp[maska]] + czas_biletu);
                if (it != sumy_prefiksowe.begin()) {
                    it--;
                    int nowe_odcinki = it - sumy_prefiksowe.begin();
                    dp[maska | (1 << j)] = max(dp[maska | (1 << j)], nowe_odcinki);
                    suma_biletow[maska | (1 << j)] = suma_biletow[maska] + bilety[j];
                }
            }
        }
    }

    long long min_suma = INT64_MAX;
    for (int maska = 0; maska < (1 << n); ++maska) {
        if (dp[maska] == k) {
            min_suma = min(min_suma, suma_biletow[maska]);
        }
    }

    long long calkowita_suma = 0;
    for (int i = 0; i < n; ++i) {
        calkowita_suma += bilety[i];
    }

    if (min_suma == INT64_MAX) {
        cout << "spacer, odpoczynek, dobry sen, swieza glowa" << endl;
    } else {
        cout << calkowita_suma - min_suma << endl;
    }

    return 0;
}