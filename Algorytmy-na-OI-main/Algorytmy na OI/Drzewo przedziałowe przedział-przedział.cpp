#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
int wie, n, duzo = 1e9;
const int mod = 998244353;
vector<ll> lazymn, lazydo, tree, zasiegl, zasiegp; // ten kod tworzy drzewo z operacj¹ mno¿enia przedzie³u poczym dodania na przedziale
                                                   // oraz zapytania o sumê na przedziale

ll tree_size() {
    ll wynik = 1;
    while (wynik < n + 1) wynik *= 2;
    return wynik * 2;
}
void push(ll i) {
    if (i >= wie) return;
    ll b = lazymn[i];
    ll c = lazydo[i];
    tree[i] *= b % mod;
    tree[i] %= mod;
    tree[i] += c * (zasiegp[i + 1] - zasiegl[i + 1] + 1) % mod;
    tree[i] %= mod;
    if (i < wie / 2) {
        lazymn[i * 2] *= b;
        lazymn[i * 2] %= mod;
        lazydo[i * 2] *= b;
        lazydo[i * 2] %= mod;
        lazydo[i * 2] += c;
        lazydo[i * 2] %= mod;

        lazymn[i * 2 + 1] *= b;
        lazymn[i * 2 + 1] %= mod;
        lazydo[i * 2 + 1] *= b;
        lazydo[i * 2 + 1] %= mod;
        lazydo[i * 2 + 1] += c;
        lazydo[i * 2 + 1] %= mod;
    }
    lazymn[i] = 1;
    lazydo[i] = 0;
}
void update(ll i, ll l, ll p, ll b, ll c) {
    push(i);
    if (zasiegl[i] == l and zasiegp[i] == p) {
        tree[i] *= b % mod;
        tree[i] %= mod;
        tree[i] += c * (zasiegp[i + 1] - zasiegl[i + 1] + 1) % mod;
        tree[i] %= mod;
        if (i < wie / 2) {
            lazymn[i * 2] *= b;
            lazymn[i * 2] %= mod;
            lazydo[i * 2] *= b;
            lazydo[i * 2] %= mod;
            lazydo[i * 2] += c;
            lazydo[i * 2] %= mod;

            lazymn[i * 2 + 1] *= b;
            lazymn[i * 2 + 1] %= mod;
            lazydo[i * 2 + 1] *= b;
            lazydo[i * 2 + 1] %= mod;
            lazydo[i * 2 + 1] += c;
            lazydo[i * 2 + 1] %= mod;
        }
    }
    else {
        if (l <= (zasiegl[i] + zasiegp[i]) / 2) {
            update(i * 2, l, min(p, zasiegp[i * 2]), b, c);
        }
        if (p > (zasiegl[i] + zasiegp[i]) / 2) {
            update(i * 2 + 1, max(zasiegl[i * 2 + 1], l), p, b, c);
        }
        push(i * 2);
        push(i * 2 + 1);
        tree[i] = tree[i * 2 + 1] + tree[i * 2];
    }
}
ll query(ll i, ll l, ll p) {
    push(i);
    if (zasiegl[i] == l and zasiegp[i] == p) {
        return tree[i];
    }
    else {
        ll wyn = 0;
        if (l <= (zasiegl[i] + zasiegp[i]) / 2) {
            wyn += query(i * 2, l, min(p, zasiegp[i * 2]));
            wyn %= mod;
        }
        if (p > (zasiegl[i] + zasiegp[i]) / 2) {
            wyn += query(i * 2 + 1, max(zasiegl[i * 2 + 1], l), p);
            wyn %= mod;
        }
        return wyn % mod;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    // przygotowanie drzewa
    wie = tree_size();
    tree.resize(wie);
    lazymn.resize(wie);
    lazydo.resize(wie);
    zasiegl.resize(wie);
    zasiegp.resize(wie);
    for (ll i = wie - 1; i > 0; i--) {
        if (i >= wie / 2) {
            zasiegl[i] = i - wie / 2;
            zasiegp[i] = i - wie / 2;
        }
        else {
            zasiegl[i] = zasiegl[i * 2];
            zasiegp[i] = zasiegp[i * 2 + 1];
        }
        lazydo[i] = 0;
        lazymn[i] = 1;
        tree[i] = 0;
    }
}

