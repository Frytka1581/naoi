#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << "Zrobione" << endl;

    /*
    #include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int MAKS_ILOSC = (1 << 18) + 10;
const int MAKS_POZIOM = 70;

int dp[MAKS_POZIOM + 1][MAKS_ILOSC];
int tablica[MAKS_ILOSC];

void solve() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);

    int ilosc;
    cin >> ilosc;
    for (int index = 0; index < ilosc; index++) {
        cin >> tablica[index];
    }
    for(int i = 0; i <= MAKS_POZIOM; i++)
        fill(dp[i], dp[i] + MAKS_ILOSC, -1);

    int maks = 0;

    for (int poziom = 0; poziom <= MAKS_POZIOM; poziom++) {
        for (int start = 0; start < ilosc; start++) {
            if (tablica[start] == poziom) {
                dp[poziom][start] = start + 1;
                maks = max(maks, poziom);
            } else {
                if (poziom == 0 || dp[poziom - 1][start] == -1 || 
                    dp[poziom - 1][dp[poziom - 1][start]] == -1) {
                    dp[poziom][start] = -1;
                } else {
                    dp[poziom][start] = dp[poziom - 1][dp[poziom - 1][start]];
                    maks = max(maks, poziom);
                }
            }
        }
        dp[poziom][ilosc] = -1;
    }

    cout << maks << "\n";
}

int main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

*/

    return 0;
}