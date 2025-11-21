#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lld long double
#define pb push_back
#define fi first
#define se second
ll m, n, li = 0;
vector<ll> ids, sil, bylo;
vector<vector<pair<ll, ll>>> grafout;
deque<ll> s;
void dfs(ll ak) {
    s.push_back(ak);
    bylo[ak] = 1;
    li++;
    ids[ak] = li;
    sil[ak] = li;
    for (pair<ll, ll> p : grafout[ak]) {
        ll j = p.first;
        if (ids[j] == -1) dfs(j);
        if (bylo[j]) sil[ak] = min(sil[ak], sil[j]);
    }
    if (ids[ak] == sil[ak]) {
        while (s.size() > 0 and s.back() != ak) {
            bylo[s.back()] = 0;
            sil[s.back()] = sil[ak];
            s.pop_back();
        }
        bylo[ak] = 0;
        s.pop_back();
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll a, b, ak, w;
    cin >> n >> m;
    queue<ll> zera;
    grafout.resize(n + 1);
    vector<vector<pair<ll, ll>>> ngrafout(n + 1), ngrafin(n + 1);

    // wczytywanie
    for (ll i = 0; i < m; i++) {
        cin >> a >> b >> w;
        grafout[a].pb({b, w});
    }

    // podzail na silnie spojne skladne
    ids.resize(n + 1, -1), sil.resize(n + 1, -1), bylo.resize(n + 1, 0);
    unordered_map<ll, vector<ll>> podzial;
    unordered_set<ll> ind;

    for (ll i = 1; i <= n; i++) {
        if (ids[i] == -1) {
             dfs(i);
        }
    }
    for (ll i = 1; i <= n; i++) {
        podzial[sil[i]].pb(i);
        ind.insert(sil[i]);
    }

    // nowy graf z silnych spojnych
    vector<ll> bilans(n + 1, 0);
    li = 1;
    for (ll i : ind) { // biorê jak¹œ silnie spójn¹
        for (ll j : podzial[i]) { // biorê ka¿dy wierzcho³ek tej spójnej
            for (pair<ll, ll> p : grafout[j]) {
                ll k = p.first;
                ll c = p.second;
                if (sil[k] != sil[j]) {
                    ngrafout[i].push_back({sil[k], c});
                    ngrafin[sil[k]].push_back({i, c});
                    bilans[i]++;
                }
            }
        }
    }
    cout << podzial.size() << endl;
}


