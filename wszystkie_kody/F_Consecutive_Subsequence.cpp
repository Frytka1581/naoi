#include <bits/stdc++.h>
using namespace std;

#define fastio                   \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define s(x) x.size()
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18
#define rsort(x) sort(x.rbegin(), x.rend())
#define sort(x) sort(x.begin(), x.end())
using ll = long long;
using pii = pair<int, int>;

void solve()
{
    int n, k;
    cin >> n;
    vector<int> v, sortv(n); 
    vector<vector<int>>index(n);
    unordered_map<int, int> indexy;
    for (int i = 0; i < n; ++i)
    {
        cin >> sortv[i];
    }
    v = sortv;
    sort(sortv);
    for (int i = 0; i < sortv.size(); i++)
    {
        indexy[sortv[i]] = i;
        
    }
    for (int i = 0; i < v.size(); i++)
    {
        index[indexy[v[i]]].push_back(i);
    }
    for (int i = 0; i < index.size(); i++) {
        for (int j = 0;j < index[i].size(); j++) {
            cout << index[i][j] << ' ';
        }
        cout << endl;
    }
    int poprzedni = -1, suma = 0, maks = 0;
    vector<int>wynik,wyjscie;
    for (int i = 0; i < n; i++)
    {
        wynik.push_back(index[i]+1);
        if (poprzedni < index[i])
        {
            suma++;
        }
        else
        {
            suma = 1;
            wynik = {index[i]+1};
        }
        poprzedni = index[i];
        maks = max(maks, suma);
        if(wyjscie.size()<wynik.size()) wyjscie = wynik;
    }
    cout << maks << '\n';
    for (int i = 0; i < wyjscie.size(); i++) {
        cout << wyjscie[i] << ' ';
    }
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