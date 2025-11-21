#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<vector<ll>> gr;
bool vis[100000];
ll d[100000];
ll jp[20][100000];


void dfs(ll v,ll dep)
{
    vis[v] = true;
    d[v] = dep;
    for(ll i : gr[v])
    {
        if(!vis[i])
        {
            jp[0][i] = v;
            dfs(i,dep+1);
        }
    }
}


ll lca(ll a,ll b)
{
    for(ll i = 19;i >= 0;i--)
    {
        if(d[a] - (1<<i) >= d[b])
        {
            a = jp[i][a];
        }
        if(d[b] - (1<<i) >= d[a])
        {
            b = jp[i][b];
        }
    }
    for(ll i = 19;i >= 0;i--)
    {
        if(jp[i][a] != jp[i][b])
        {
            a = jp[i][a];
            b = jp[i][b];
        }
    }
    if(a == b)
    {
        return a;
    }
    return jp[0][a];
}


ll main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin>>n;
    gr.resize(n);
    for(ll i = 0;i<n-1;i++)
    {
        ll a,b;
        cin>>a>>b;
        a--;b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    dfs(0,0);
    jp[0][0] = 0;
    for(ll i = 1;i<20;i++)
    {
        for(ll j = 0;j<n;j++)
        {
            jp[i][j] = jp[i-1][jp[i-1][j]];
        }
    }

    return 0;
}