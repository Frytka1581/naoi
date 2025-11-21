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
vector<vector<pair<ll,ll>>> gr;
priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
ll dis[200000];

void dk(ll c,ll v)
{
    for(pair<ll,ll> i : gr[v])
    {
        if(c + i.nd < dis[i.st])
        {
            dis[i.st] = c + i.nd;
            pq.push({c+i.nd,i.st});
        }
    }
}
ll main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m;
    cin>>n>>m;
    gr.resize(n);
    rep(i,m)
    {
        ll a,b,c;
        cin>>a>>b>>c;
        a--;b--;
        gr[a].pb({b,c});
        gr[b].pb({a,c});
    }
    rep(i,n)
    {
        dis[i] = inf;
    }
    dis[0] = 0;
    pq.push({0,0});
    while(!pq.empty())
    {
        pair<ll,ll> c = pq.top();
        pq.pop();
        if(c.st == dis[c.nd]) dk(c.st,c.nd);
    }

    for(ll i = 0; i < n; i++){
        cout << dis[i] << " ";
    }
    cout << "\n";
    return 0;
}















