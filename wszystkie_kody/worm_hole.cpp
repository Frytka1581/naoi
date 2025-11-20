#include <bits/stdc++.h>
using namespace std;
vector<int> ciag;
vector<tuple<int, int, int>> wormholes;
vector<int> parent;
vector<int> rang;
int n;
int fajnd(int x)
{
    if (x != parent[x])
        parent[x] = fajnd(parent[x]);
    return parent[x];
}
void onion(int l, int r)
{
    l = fajnd(l);
    r = fajnd(r);
    if (l != r)
    {
        if (rang[l] < rang[r])
        {
            swap(l, r);
        }
        parent[r] = l;
        rang[l] += rang[r];
    }
}
bool czy(int k)
{
    parent.resize(n + 1);
    rang.assign(n + 1, 1);
    for (long long i = 1; i <= n; ++i)
        parent[i] = i;

    for (int i = 0; i < wormholes.size(); ++i)
    {
        if (get<2>(wormholes[i]) >= k)
        {
            onion(get<0>(wormholes[i]), get<1>(wormholes[i]));
            // cout << get<2>(wormholes[i]) << endl;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (fajnd(ciag[i]) != fajnd(i + 1))
            return false;
    }
    return true;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    int m, a, b, c, maks = 0;
    cin >> n >> m;
    ciag.resize(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> ciag[i];
    }
    vector<int> c2 = ciag;
    sort(c2.begin(), c2.end());
    if (c2 == ciag)
    {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < m; ++i)
    {

        cin >> a >> b >> c;
        maks = max(maks, c);
        wormholes.push_back({a, b, c});
    }
    int l = 1, p = maks, sr;
    // cout << czy(10) << endl;
    // onion(1,2);
    //  for(int i=0;i<n;++i){
    //      cout << fajnd(i+1) << endl;
    //  }
    // if(czy(maks)==false) {
    //     cout << 123;
    //     return 0;

    // }
    // cout << czy(9) << endl;
    while (l < p)
    {

        sr = (l + p + 1) / 2;
        //cout << l << ' ' << p << ' ' << sr << endl;
        if (czy(sr))
            l = sr;
        else
            p = sr - 1;
    }
    cout  << p;
    return 0;
}