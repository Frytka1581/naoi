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
vector<int> tree2;
vector<int> tree3;
void dodaj(int index)
{
    while (index > 0)
    {
        tree[index]++;
        index /= 2;
    }
}
void dodaj2(int index, int wartosc)
{
    tree2[index] = max(tree2[index], wartosc); // max w tree2
    tree3[index] = min(tree3[index], wartosc); // min w tree3
    while (index > 1)
    {
        index /= 2;
        tree2[index] = max(tree2[2 * index], tree2[2 * index + 1]);
        tree3[index] = min(tree3[2 * index], tree3[2 * index + 1]);
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
int zwroc3(int lq, int rq, int l, int r, int index)
{
    if (l > rq || r < lq)   // brak przecięcia
        return 1e9;         // neutralny element dla min
    if (lq <= l && r <= rq) // pełne pokrycie przedziału
        return tree3[index];
    int m = (l + r) / 2; // klasyczny podział na połowy
    return min(zwroc3(lq, rq, l, m, index * 2),
               zwroc3(lq, rq, m + 1, r, index * 2 + 1));
}

void solve()
{
    int n, k = 1;
    cin >> n;
    while (k < n)
        k *= 2;
    tree = {};
    tree.resize(k * 2);
    tree2.resize(k * 2);
    tree3.resize(k * 2, 1e9);
    vector<int> v(n);
    vector<int> is(n + 1);
    vector<int> v2(n + 1);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
        v2[v[i]] = i;
    }
    // dodaj(k);
    // dodaj(k + 1);
    // for (int i = 1; i < tree.size(); i++)
    // {
    //     cout << tree[i] << ' ';
    // }
    // cout << zwroc(2, 3, 1, k, 1);
    int s = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        dodaj2(v2[i] + k, i + 1);
    }
    for (int i = n - 1; i > 0; i--)
    {
        s++;
        dodaj(k + v[i] - 1);
        int wynik = zwroc(1, s, 1, k, 1);
        if (wynik == s)
        {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
    vector<int> minimalny(n + 1, 1e9);
    for (int i = 1; i < v.size(); i++)
    {
        minimalny[i] = min(minimalny[i - 1], v[i - 1]);
    }

    for (int i = n; i > 0; i--)
    {
        if (is[i] == 0)
        {
            int ostatni = 0;
            for (int j = v2[i] - 1; j >= 0; j--)
            {
                if (v[j] > i)
                {
                    ostatni = j;
                    break;
                }
                else
                {
                    is[v[j]] = 1;
                    cout << v[j] << ' ' << i << endl;
                }
            }
            int wynik = minimalny[ostatni];
            if (wynik != 1000000000)
                cout << wynik << ' ' << i << endl;
        }
    }
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