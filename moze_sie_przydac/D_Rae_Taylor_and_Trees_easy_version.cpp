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
vector<int> tree;
void dodaj(int index)
{
    while (index > 0)
    {
        tree[index]++;
        index /= 2;
    }
}
int zwroc(int lq, int rq, int l, int r, int index)
{
    if (l > rq || r < lq)
        return 0;
    else if (l >= lq && r <= rq)
        return tree[index];
    else
    {
        int sr = (l + r + 1) / 2;
        return zwroc(lq, rq, l, sr - 1, index * 2) + zwroc(lq, rq, sr, r, index * 2 + 1);
    }
}
void solve()
{
    int n, k = 1;
    cin >> n;
    while (k < n)
        k *= 2;
    tree = {};
    tree.resize(k * 2);
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }
    // dodaj(k);
    // dodaj(k + 1);
    // for (int i = 1; i < tree.size(); i++)
    // {
    //     cout << tree[i] << ' ';
    // }
    // cout << zwroc(2, 3, 1, k, 1);
    int s = 0;
    for (int i = n - 1; i > 0; i--)
    {
        s++;
        dodaj(k+v[i]-1);
        int wynik = zwroc(1,s,1,k,1);
        if(wynik==s){
            cout << "NO" << endl;
            return ;
        }
    }
    cout << "YES" << endl;
}

int main()
{
    fastio;
    int t = 1;
    cin >> t;
    // t = 1;
    while (t--)
        solve();
    return 0;
}