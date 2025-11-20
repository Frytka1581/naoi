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

const int MAXN = 300;
int n, m, dp[MAXN][MAXN];
int cow[MAXN][MAXN][MAXN];
vector<int> w, l, r;

template <class T>
bool upd_max(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}

void solve() {
    cin >> n >> m;
    w.resize(m);
    l.resize(m);
    r.resize(m);

    for (int i = 0; i < m; i++) {
        cin >> w[i] >> l[i] >> r[i];
        l[i]--, r[i]--;
        for (int j = l[i]; j <= r[i]; j++)
            upd_max(cow[j][l[i]][r[i]], w[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 0; j--) {
            for (int k = i; k < n; k++) {
                if (j > 0) upd_max(cow[i][j-1][k], cow[i][j][k]);
                if (k < n-1) upd_max(cow[i][j][k+1], cow[i][j][k]);
            }
        }
    }

    for (int a = n-1; a >= 0; a--) {
        for (int b = a; b < n; b++) {
            for (int c = a; c < b; c++)
                upd_max(dp[a][b], dp[a][c] + dp[c+1][b]);
            for (int c = a; c <= b; c++) {
                if (cow[c][a][b]) {
                    int res = cow[c][a][b];
                    if (c > a) res += dp[a][c-1];
                    if (c < b) res += dp[c+1][b];
                    upd_max(dp[a][b], res);
                }
            }
        }
    }

    cout << dp[0][n-1] << "\n";
}

int main() {
    fastio;
    int t = 1;
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    // cin >> t;
    while (t--) solve();
    return 0;
}

*/

    return 0;
}