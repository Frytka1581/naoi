#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
#define lld long double

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n, m, w1, w2, c;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> graf(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> w1 >> w2 >> c;
        graf[w1].push_back({w2, c});
        graf[w2].push_back({w1, c}); // bez tego jeœli skierowany
    }
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    vector<ll> dist(n + 1, 1e18);
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        ll dl = pq.top().fi;
        ll wi = pq.top().se;
        pq.pop();
        if (dl > dist[wi]) continue;
        dist[wi] = dl;
        for (pair<ll, ll> p : graf[wi]) {
            ll waga = p.se;
            ll i = p.fi;
            if (dl + waga < dist[i]) {
                dist[i] = dl + waga;
                pq.push({dist[i], i});
            }
        }
    }
}
