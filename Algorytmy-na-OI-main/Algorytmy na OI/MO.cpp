#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define st first
#define nd second
#define pb push_back
#define lld long double
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n, q, l, r;
    cin >> n >> q;
    ll pier = sqrt(n);
    vector<ll> arr(n), kom(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    vector<pair<pair<ll, ll>, pair<ll, ll>>> zapytania;
    for (int i = 0; i < q; i++) {
        cin >> l >> r;
        zapytania = {l / pier, r, l, i};
    }
    sort(zapytania.begin(), zapytania.end()); // po przejœciu w ten sposób po zapyaniach otrzymamy pierwiastkow¹ z³o¿onoœæ
}


