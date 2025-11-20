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

void solve()
{
    string s;
    int n, l, r, suma = 0, wynik = 0;

    cin >> s;
    cin >> n;
    vector<int> v(s.size() + 1);
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
            suma++;
        else if (suma > 0)
        {
            suma--;
            wynik++;
        }
        v[i + 1] = wynik;
    }
    // cout << s << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << endl;   
    for (int i = 0; i < n; i++)
    {
        cin >> l >> r;
        cout << (v[r] - v[l])*2 << '\n';
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