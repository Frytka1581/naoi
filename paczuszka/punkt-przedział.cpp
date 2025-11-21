#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(),a.end()
#define rep(a,b) for(ll a = 0;a<b;a++)
const ll inf = 1e9;
const ll infl = 1e18;


const ll ize = 100000;
ll tr[ize*2];


void add(ll p,ll v)
{
    p+=ize;
    tr[p] += v;
    p/=2;
    while(p > 0)
    {
        tr[p] = tr[p*2] + tr[p*2+1];
        p/=2;
    }
}


ll check(ll l,ll r)
{
    l+=ize;
    r+=ize;
    ll ans = tr[l];
    if(l != r) ans += tr[r];
    while(l/2 != r/2)
    {
        if(l%2==0)ans+=tr[l+1];
        if(r%2==1)ans+=tr[r-1];
        l/=2;r/=2;
    }
    return ans;
}

int main(){
    
}