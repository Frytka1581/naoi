#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
#define lld long double
vector<ll> ojc, gl, od;
vector<vector<ll>> dzie, skoki;
vector<vector<pair<ll, ll>>> graf;
ll lca(ll a, ll b) {
    if (gl[a] < gl[b]) {
        swap(a, b);
    }
    ll ile = gl[a] - gl[b];
    for (int i = 18; i >= 0; i--) {
        ll pot = 1 << i;
        if (pot <= ile) {
            ile -= pot;
            a = skoki[i][a];
        }
    }
    if (a == b) return a;
    for (int i = 18; i >= 0; i--) {
        if (skoki[i][a] != skoki[i][b]) {
            a = skoki[i][a];
            b = skoki[i][b];
        }
    }
    return skoki[0][a];
}
void dfs(ll w) {
    for (pair<ll, ll> p : graf[w]) {
        ll i = p.fi, dl = p.se;
        if (i == ojc[w]) continue;
        ojc[i] = w;
        gl[i] = gl[w] + 1;
        od[i] = od[w] + dl;
        dzie[w].pb(i);
        skoki[0][i] = w;
        dfs(i);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll q, a, b, ile, c, n;
    cin >> n;
    ojc.resize(n + 1);
    dzie.resize(n + 1);
    graf.resize(n + 1);
    gl.resize(n + 1);
    od.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> c;
        graf[a].push_back({b, c});
        graf[b].push_back({a, c});
    }
    ojc[1] = 0;
    od[1] = 0;
    gl[1] = 0;
    skoki.resize(19);
    skoki[0].resize(n + 1);
    dfs(1);
    for (int i = 1; i < 19; i++) {
        skoki[i].resize(n + 1);
        for (int j = 1; j <= n; j++) {
            skoki[i][j] = skoki[i - 1][skoki[i - 1][j]];
        }
    }
}

