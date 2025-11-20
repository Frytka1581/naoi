#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll p = 31;
const ll MOD = 1e9 + 7;
vector<ll> hashe(1e6+7);
vector<ll> potegi(1e6+7, 1);
ll dlugosc;
void nazwa(string napis)
{
    for (int i = 1; i <= napis.length(); ++i)
    {
        potegi[i] = (potegi[i - 1] * p) % MOD;
        potegi[i] += MOD;
        potegi[i] %= MOD;
        hashe[i] = (hashe[i - 1] + napis[i - 1] * potegi[i]) % MOD;
        hashe[i] += MOD;
        hashe[i] %= MOD;
    }
}
ll hashe_ale_nie_prefix(ll i, ll j)
{
    ll wynik;
    wynik = hashe[j] - hashe[i - 1];
    wynik += MOD;
    wynik %= MOD;
    wynik *= potegi[dlugosc - i];
    wynik %= MOD;
    wynik += MOD;
    wynik %= MOD;
    return wynik;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    string napis;
    for (int i = 0; i < n; ++i)
    {
        cin >> napis;
        hashe.resize(1e6 + 7);
        // // potegi.resize(1e5+7,1);
        dlugosc = napis.length();
        nazwa(napis);
        ll s = 0, i1 = 1, i4 = dlugosc, i3 = 1, i2 = i4;
        pair<ll, ll> cos;
        while (i1 < i2)
        {
            // cout << i1 << ' ' << i3 << endl;
            // cout << i2 << ' ' << i4 << endl;
            if (hashe_ale_nie_prefix(i1, i3) == hashe_ale_nie_prefix(i2, i4))
            {
                s += 2;
                cos = {i1, i3};
                i1 = i3 + 1;
                i4 = i2 - 1;
            }
            i3++;
            i2--;
        }
        
        pair<ll, ll> cos2 = {i1, i3};
        if (cos != cos2 && i1 <= i2)
            cout << s + 1 << endl;
        else
            cout << s << endl;
    }
    return 0;
}