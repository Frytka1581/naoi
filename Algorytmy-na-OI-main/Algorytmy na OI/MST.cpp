#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lld long double
#define pb push_back
#define fi first
#define se second
vector<int> wiel, grupa;
int gr(int a) {
    if (a == grupa[a]) return a;
    int g = gr(grupa[a]);
    grupa[a] = g;
    return g;
}
bool uni(int a, int b) {
    a = gr(a), b = gr(b);
    if (a == b) return 0;
    if (wiel[b] > wiel[a]) swap(a, b);
    wiel[a] += wiel[b];
    grupa[b] = a;
    return 1;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    wiel.resize(n + 1);
    grupa.resize(n + 1);
    vector<pair<pair<int, int>, pair<int, int>>> kr(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> kr[i].se.fi >> kr[i].se.se >> kr[i].fi.fi;
        kr[i].fi.se = i;
    }
    for (int i = 1; i <= n; i++) grupa[i] = i;
    sort(kr.begin(), kr.end());
    for (pair<pair<int, int>, pair<int, int>> p : kr) {
        if (uni(p.se.fi, p.se.se)) {
            cout << p.fi.se << endl;
        }
    }
}
