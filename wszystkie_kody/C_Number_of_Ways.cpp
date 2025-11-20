#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(0);
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;

void solve() {
    ll n; cin >> n;
    ll suma = 0,wynik =0;
    vector<ll> v(n);
    vector<ll>pref(n+1);
    unordered_map<ll,ll> ilosc;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        suma+=v[i];
        pref[i+1] = pref[i] + v[i];
    }
    if(suma%3!=0) {cout << 0;return ;}
    suma/=3;
    ilosc[pref[1]]++;
    for (int i = 1; i < n - 1; i++) {
        if(pref[n]-pref[i+1] == suma){
            ll szukany = pref[i+1] - suma;
            wynik += ilosc[szukany];
            
        }
        ilosc[pref[i+1]]++;
    }
    cout << wynik << '\n';
}

int main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}