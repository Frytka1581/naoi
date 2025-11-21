#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lld long double
#define fi first
#define se second
#define pb push_back
vector<vector<ll>> dist;
ll inf = 1e18, n;
void dodaj(ll x, ll y, ll z) {
    dist[x][y] = min(dist[x][y], z);
    dist[y][x] = dist[x][y];
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j < i; j++) {
            dist[i][j] = min(min(dist[i][j], dist[i][x] + dist[y][j] + z), dist[i][y] + dist[x][j] + z);
            dist[j][i] = dist[i][j];
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll m, a, b, c, q, x, y, z;
    cin >> n >> m >> q;
    dist.resize(n + 1);
    for (int i = 0; i <= n; i++) dist[i].resize(n + 1, inf);
    ll wyn = 0;
    for (ll i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }
    for (ll i = 0; i < m; i++) {
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = dist[a][b];
    }
    for (ll k = 1; k <= n; k++) {
        for (ll i = 1; i <= n; i++) {
            for (ll j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                dist[j][i] = dist[i][j];
            }
        }
    }
    while (q--) {
        cin >> x >> y;
        if (dist[x][y] != inf) cout << dist[x][y] << endl;
        else cout << -1 << endl;
    }
}


