#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 998244353;
vector<pair<ll, pair<ll, ll>>> drzewo;
vector<ll> dlugosc;

void propaguj(ll index, ll l, ll r) {
    if (drzewo[index].second.first != 1 || drzewo[index].second.second != 0) {
        ll stara_suma = drzewo[index].first;
        drzewo[index].first = (drzewo[index].first * drzewo[index].second.first % MOD +
                              drzewo[index].second.second * dlugosc[index] % MOD) % MOD;
        
        if (l != r) {
            drzewo[index * 2].second.first = (drzewo[index * 2].second.first * drzewo[index].second.first) % MOD;
            drzewo[index * 2 + 1].second.first = (drzewo[index * 2 + 1].second.first * drzewo[index].second.first) % MOD;
            drzewo[index * 2].second.second = (drzewo[index * 2].second.second * drzewo[index].second.first % MOD +
                                              drzewo[index].second.second) % MOD;
            drzewo[index * 2 + 1].second.second = (drzewo[index * 2 + 1].second.second * drzewo[index].second.first % MOD +
                                                  drzewo[index].second.second) % MOD;
        }
        
        drzewo[index].second = {1, 0};
    }
}

void dodaj(ll l, ll r, ll lq, ll rq, ll index, ll b, ll c) {
    propaguj(index, l, r);
    
    if (rq < l || r < lq) return;
    if (lq <= l && r <= rq) {
        drzewo[index].second.first = (drzewo[index].second.first * b) % MOD;
        drzewo[index].second.second = (drzewo[index].second.second * b % MOD + c) % MOD;
        propaguj(index, l, r);
        return;
    }
    
    ll sr = (l + r) / 2;
    dodaj(l, sr, lq, rq, index * 2, b, c);
    dodaj(sr + 1, r, lq, rq, index * 2 + 1, b, c);
    
    drzewo[index].first = (drzewo[index * 2].first + drzewo[index * 2 + 1].first) % MOD;
}

ll sprawdz(ll l, ll r, ll lq, ll rq, ll index) {
    propaguj(index, l, r);
    
    if (rq < l || r < lq) return 0;
    if (lq <= l && r <= rq) return drzewo[index].first;
    
    ll sr = (l + r) / 2;
    ll lewa_suma = sprawdz(l, sr, lq, rq, index * 2);
    ll prawa_suma = sprawdz(sr + 1, r, lq, rq, index * 2 + 1);
    return (lewa_suma + prawa_suma) % MOD;
}

void buduj(vector<ll>& tab, ll k) {
    for (ll i = 0; i < tab.size(); i++) {
        drzewo[k + i].first = tab[i];
        dlugosc[k + i] = 1;
    }
    for (ll i = k - 1; i >= 1; i--) {
        drzewo[i].first = (drzewo[i * 2].first + drzewo[i * 2 + 1].first) % MOD;
        dlugosc[i] = dlugosc[i * 2] + dlugosc[i * 2 + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n, q;
    cin >> n >> q;
    
    ll k = 1;
    while (k < n) k *= 2;
    drzewo.resize(2 * k, {0, {1, 0}});
    dlugosc.resize(2 * k, 0);
    
    vector<ll> tab(n);
    for (ll i = 0; i < n; i++) {
        cin >> tab[i];
        tab[i] %= MOD;
    }
    
    buduj(tab, k);
    
    while (q--) {
        ll typ, l, r;
        cin >> typ >> l >> r;
        r--;
        if (typ == 0) {
            ll b, c;
            cin >> b >> c;
            dodaj(0, k - 1, l, r, 1, b, c);
        } else {
            cout << sprawdz(0, k - 1, l, r, 1) << '\n';
        }
    }
    
    return 0;
}