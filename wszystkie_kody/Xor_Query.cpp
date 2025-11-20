#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define f first
#define s second
const int N = 4e5 + 5;

// Funkcja dodaj: Dodaje element k do bazy liniowej z indeksem kolejnosc
vector<pll> dodaj(ll k, vector<pll> ciag, vector<ll>& repr, vector<ll>& idx, ll kolejnosc) {
    ll a = k;
    ll rep = 0;
    for (int i = 60; i >= 0; --i) {
        if (a & (1LL << i)) {
            if (ciag[i].f) {
                a ^= ciag[i].f;
                rep ^= ciag[i].s;
            } else {
                ciag[i].f = a;
                ciag[i].s = rep | (1LL << i);
                idx[i] = kolejnosc;
                break;
            }
        }
    }
    if (!a) {
        pll mn = {N, N};
        for (int i = 60; i >= 0; --i) {
            if (rep & (1LL << i)) {
                mn = min(mn, {idx[i], i});
            }
        }
        if (mn.f != N) {
            for (int i = 60; i >= 0; --i) {
                if (ciag[i].s & (1LL << mn.s)) {
                    ciag[i].s ^= rep ^ (1LL << mn.s);
                }
            }
            idx[mn.s] = kolejnosc;
        }
    }
    return ciag;
}

// Funkcja sprawdz: Sprawdza, czy k można wyrazić jako XOR elementów bazy w przedziale [l, r]
bool sprawdz(ll k, ll l, vector<pll> ciag, vector<ll>& idx) {
    ll a = k;
    ll repr = 0;
    for (int i = 60; i >= 0; --i) {
        if (a & (1LL << i)) {
            if (ciag[i].f) {
                a ^= ciag[i].f;
                repr ^= ciag[i].s;
            }
        }
    }
    if (!a) {
        ll mn = N;
        for (int i = 60; i >= 0; --i) {
            if (repr & (1LL << i)) {
                mn = min(mn, idx[i]);
            }
        }
        return mn >= l;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<pll> ciag(61); // Baza liniowa: {wartość, maska reprezentacji}
    vector<ll> idx(61, N); // Indeksy elementów w bazie

    ll n, q;
    cin >> n >> q;
    vector<ll> wejscie(n);
    vector<string> wypisz(q);
    vector<tuple<ll, ll, ll, ll>> pytanie(q); // {r, l, x, idx}
    for (ll i = 0; i < n; ++i) {
        cin >> wejscie[i];
    }
    for (ll i = 0; i < q; ++i) {
        ll l, r, x;
        cin >> l >> r >> x;
        pytanie[i] = {r, l, x, i};
    }
    sort(pytanie.begin(), pytanie.end()); // Sortowanie po r

    ll index = 0;
    vector<ll> repr(61, 0); // Maska reprezentacji bitowej
    for (ll i = 0; i < n; ++i) {
        ciag = dodaj(wejscie[i], ciag, repr, idx, i + 1);
        while (index < q && get<0>(pytanie[index]) == i + 1) {
            ll l = get<1>(pytanie[index]);
            ll x = get<2>(pytanie[index]);
            ll idx_q = get<3>(pytanie[index]);
            wypisz[idx_q] = sprawdz(x, l, ciag, idx) ? "Yes" : "No";
            index++;
        }
    }
    for (ll i = 0; i < q; ++i) {
        cout << wypisz[i] << endl;
    }
    return 0;
}