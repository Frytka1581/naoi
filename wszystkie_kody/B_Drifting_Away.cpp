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
    string n;
    cin >> n;
    int l = 0, r = 0, p = 0;
    for (int i = 0; i < n.size(); i++)
    {
        if (n[i] == '<')
        {
            if (r > 0)
            {
                cout << -1 << '\n';
                return;
            }
            if (i > 0 && n[i - 1] == '*')
            {
                cout << -1 << '\n';
                return;
            }
            l++;
        }
        else if (n[i] == '>')
            r++;
        else
        {
            if (r > 0)
            {
                cout << -1 << '\n';
                return;
            }

            if (p > 0)
            {
                cout << -1 << '\n';
                return;
            }
            p++;
        }
    }
    cout << max(l, r) + p << endl;
}

int main()
{
    fastio;
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}