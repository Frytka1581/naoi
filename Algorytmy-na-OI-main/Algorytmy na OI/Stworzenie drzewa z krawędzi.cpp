#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
ll n;
vector<vector<pair<ll, ll>>> dzie, graf;
vector<pair<ll, ll>> ojc;
vector<ll> wie;
void dfs(ll w) {
    for (pair<ll, ll> p : graf[w]) {
        ll i = p.fi, dl = p.se;
        if (i == ojc[w].fi) continue;
        ojc[i] = {w, dl};
        dzie[w].pb({i, dl});
        dfs(i);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a, b, c;
    cin >> n;
    ojc.resize(n + 1);
    dzie.resize(n + 1);
    graf.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> c;
        graf[a].push_back({b, c});
        graf[b].push_back({a, c});
    }
    ojc[1] = {0, -1};
    dfs(1);
}

