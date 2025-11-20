#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll k = 1;
vector<ll> ile_przedzialow;
vector<ll> dlugosc_przedzialow;
void update(ll l, ll r, ll lq, ll rq, ll index, ll wartosc)
{
    //if(r>l) return;
    if (rq < l || lq > r)
        return;
    else if (lq <= l && r <= rq)
    {
        ile_przedzialow[index] += wartosc;
    }
    else
    {
        ll sr = (l + r + 1) / 2;
        update(l, sr - 1, lq, rq, index * 2, wartosc);
        update(sr, r, lq, rq, index * 2 + 1, wartosc);
    }
    if (ile_przedzialow[index] > 0)
        dlugosc_przedzialow[index] = r - l + 1;
    else if (l == r)
        dlugosc_przedzialow[index] = 0;
    else
        dlugosc_przedzialow[index] = dlugosc_przedzialow[index * 2] + dlugosc_przedzialow[index * 2 + 1];
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // w tree 1 biore ile przedzialow nachodzi
    // w tree 2 jaka jest dlugosc przedzialu w l r k
    ll n, z, pomoc = 1;
    cin >> n >> z;
    vector<ll> poz( n+1);
    vector<ll> ciag(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> ciag[i];
        poz[ciag[i]] = i+1;
    }
    while (pomoc < n)
        pomoc *= 2;
    while (k <= n)
        k *= 2;
    ile_przedzialow.resize(k * 2);
    dlugosc_przedzialow.resize(k * 2);
    //update(1, pomoc, 1, 4, 1, 1);
    for (int i = 1; i <= n; ++i)
    {
        if (poz[i] <= i - 1)
        {
            update(1,pomoc,poz[i],i-1,1,1);
        }
    }
    cout << n - dlugosc_przedzialow[1] << endl;
    ll l,r;
    for(int i=0;i<z-1;++i){
        cin >> l >> r;
        ll x = poz[ciag[l-1]];
        ll y = poz[ciag[r-1]];
        if(x <= ciag[l-1]-1){
            update(1,pomoc,x,ciag[l-1]-1,1,-1);
        }
        if(y<=ciag[r-1]-1){
            update(1,pomoc,y,ciag[r-1]-1,1,-1);
        }
        poz[ciag[l-1]] = r;
        poz[ciag[r-1]] = l;
        swap(ciag[l-1],ciag[r-1]);
        x = poz[ciag[l-1]];
        y = poz[ciag[r-1]];
        if(x <= ciag[l-1]-1){
            update(1,pomoc,x,ciag[l-1]-1,1,1);
        }
        if(y<=ciag[r-1]-1){
            update(1,pomoc,y,ciag[r-1]-1,1,1);
        }
        cout << n-dlugosc_przedzialow[1] << endl;
    }
    return 0;
}