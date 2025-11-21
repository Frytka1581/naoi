#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
ll inf = 1e18;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	ll n, m, q, s, u, v, w;
	cin >> n >> m >> q >> s;
    vector<vector<pair<int, ll>>> graf(n + 1);
    vector<ll> dist(n + 1, inf);
    dist[s] = 0;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        graf[u].pb({v, w});
    }

    for (int prz = 0; prz < n - 1; prz++) { // n - 1 przejœæ
        for (int i = 1; i <= n; i++) {
            if (dist[i] == inf) continue;
            for (pair<ll, ll> p : graf[i]) {
                dist[p.fi] = min(dist[p.fi], dist[i] + p.se);
            }
        }
    }

    queue<int> kol;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == inf) continue;
        for (pair<int, ll> p : graf[i]) {
            // wszystko co siê updejtuje po n - 1 ruchach jest w ujemnym cyklu
            if (dist[i] + p.se < dist[p.fi]) kol.push(p.fi);
        }
    }

    vector<int> ujemny_cykl(n + 1, 0);
    while (!kol.empty()) {
        ll w = kol.front();
        kol.pop();
        ujemny_cykl[w] = 1;
        for (pair<int, ll> p : graf[w]) {
            if (ujemny_cykl[p.fi]) continue;
            kol.push(p.fi);
        }
    }
}
