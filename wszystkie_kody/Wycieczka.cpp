#include <bits/stdc++.h>
using namespace std;

#define fastio                   \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define s(x) x.size()
#define sort(x) sort(x.begin(), x.end())
#define rsort(x) sort(x.rbegin(), x.rend())
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;
vector<ll> v;
ll maxi;
bool possible(ll k)
{
    ll last = 0, sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        last += v[i];
        if (last > k)
        {
            sum++;
            last = v[i];
        }
    }
    if (last > 0)
        sum++;
    if (sum > maxi)
        return false;
    else
        return true;
}
void solve()
{
    ll n,maxi2 = 0;
    cin >> n >> maxi;
    //cout << n << '|' << maxi << '/';
    v.resize(n-1);
    for (int i = 0; i < n-1; ++i)
    {
        cin >> v[i];
        maxi2 = max(v[i],maxi2);
    }
    //cout << endl;
    ll l=0,r=INFL;
    while(l<r){
        ll sr = (l+r)/2;
        if(!possible(sr)) l = sr+1;
        else r = sr;
        //cout << l << ' ' << r << ' ' << sr << endl;
    }
    cout << max(maxi2,l) << endl;
}

int main()
{
    fastio;
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}