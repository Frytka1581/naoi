#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k, v;
    cin >> n >> m;
    vector<int> gdzie(n + 1, -1);
    vector<vector<int>> stosy(m + 1);
    pair<int, int> b1 = {1e9, 1e9}, b2 = b1;
    int ok = 2, pusty = -1, jed;
    for (int i = 1; i <= m; i++) {
        cin >> k;
        v = 0;
        for (int j = 0; j < k; j++) {
            cin >> v;
            if (v == 1) {
                ok = 1;
                jed = i;
            }
            else if (jed == i and ok == 1 and gdzie[v - 1] != i) ok = 0;
            gdzie[v] = i;
            stosy[i].pb(v);
        }
        if (v < b1.fi) b1 = {v, i};
        else if (v < b2.fi) b2 = {v, i};
        if (stosy[i].size() == 0) pusty = i;
    }
    if (ok == 1) {
        cout << n - stosy[jed].size() << endl;
        for (int i = stosy[jed].size() + 1; i <= n; i++) cout << gdzie[i] << " " << jed << endl;
        return 0;
    }
    if (pusty != -1) {
        cout << n << endl;
        for (int i = 1; i <= n; i++) cout << gdzie[i] << " " << pusty << endl;
        return 0;
    }
    int dokad = 1e9, skad = 1e9, il = 1e9;
    for (int i = 1; i <= m; i++) {
        if (b1.se == i) swap(b1, b2);
        if (b1.fi < stosy[i][0] and stosy[i].size() < il) {
            il = stosy[i].size();
            skad = i;
            dokad = b1.se;
        }
        if (b1.fi >b2.fi) swap(b1, b2);
    }
    if (skad == 1e9) {
        cout << -1;
        return 0;
    }
    cout << n + stosy[skad].size() << endl;
    for (int i = 0; i < stosy[skad].size(); i++) {
        cout << skad << " " << dokad << endl;
        gdzie[stosy[skad][i]] = dokad;
    }
    for (int i = 1; i <= n; i++) cout << gdzie[i] << " " << skad << endl;
}
