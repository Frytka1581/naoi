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
vector<double> v;
double possible(double x)
{
    double sum = 0, multi = 1;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        sum += multi * v[i];
        multi *= x;
    }
    // cout << multi << endl;
    return sum;
}
void solve()
{
    ll n = 6;
    v.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }
    double l = -1e1, r = 1e1;
    // ..cout << fixed << setprecision(6) << possible(-1.41421) << endl;
    if (v[0] > 0)
    {
        while (l < r)
        {
            // cout << l << ' ' << r << endl;
            double sr = (l + r) / 2;
            double ans = possible(sr);
            if (ans == 0)
            {
                cout << fixed << setprecision(8) << sr;
                return;
            }
            else if (ans < 0)
            {
                l = sr + 0.00000001;
            }
            else
            {
                r = sr - 0.00000001;
            }
            // cout << l << ' ' << r << ' ' << sr << endl;
        }
    }
    else
    {
        while (l < r)
        {
            // cout << l << ' ' << r << endl;
            double sr = (l + r) / 2;
            double ans = possible(sr);
            if (ans == 0)
            {
                cout << fixed << setprecision(8) << sr;
                return;
            }
            else if (ans < 0)
            {
                r = sr - 0.00000001;
            }
            else
            {
                l = sr + 0.00000001;
            }
            // cout << l << ' ' << r << ' ' << sr << endl;
        }
    }
    cout << fixed << setprecision(8) << l << endl;
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