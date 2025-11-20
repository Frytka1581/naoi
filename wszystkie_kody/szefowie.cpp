#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> graf;
int n;

int BFS(int y)
{
    vector<bool> odwiedzone(n + 1);
    int wynik = 0;
    queue<pair<int, int>> kolejka;
    kolejka.push({y, 0});
    while (!kolejka.empty())
    {
        //cout << wynik << endl;
        pair<int, int> p = kolejka.front();
        kolejka.pop();
        if (odwiedzone[p.first])
            continue;
        odwiedzone[p.first] = 1;
        wynik += p.second;
        for (int u : graf[p.first])
            kolejka.push({u, p.second + 1});
    }
    for (int i = 1; i <= n; ++i) if(!odwiedzone[i]) return 1e9;
    return wynik;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m, k;
    cin >> n;
    graf.resize(n + 1);
    for (int i = 0; i < n; ++i)
    {
        cin >> m;
        for (int j = 0; j < m; ++j)
        {
            cin >> k;
            graf[k].push_back(i+1);
        }
    }
    int minn=INT32_MAX;
    for(int i=1;i<=n;++i){
        minn=min(minn,BFS(i));
    }
    cout << minn+n;
    return 0;
}