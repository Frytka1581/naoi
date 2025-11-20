#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool czyda(ll sr, ll m, ll k,ll n)
{
    ll wyn = m/(sr+1);
    ll por = m - wyn * (sr+1);
    if((wyn*sr+por)*n < k ) return false;
    return true; 
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, a, b, c;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> a >> b >> c;
        ll l = 1, p = b, sr;
        while (l < p)
        {
            
            sr=(l+p)/2;
            //cout << l << ' ' << sr << ' '<< p << endl;
            if(czyda(sr, b, c, a)) p = sr;
            else l = sr+1;
            
        }
        // cout << l << ' ' << p << endl;
        cout << l << endl;
    }
    return 0;
}