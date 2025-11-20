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
vector<int> v;
int maxi;
bool possible(int k)
{
    int s = 0, last = -INF;
    for (int i = 0; i < v.size(); i++)
    {
        if (last < v[i] - k)
        {
            last = v[i] + k;
            s++;
        }
    }
    if (s <= maxi)
        return true;
    else
        return false;
}
void solve()
{
    int n;
    cin >> maxi >> n;
    v.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
        v[i] *= 10;
    }
    sort(v);
    int l = 0, r = 1e7;
    //cout << possible(1) << endl;
    while (l < r )
    {
        int mid = (l + r) / 2;
        if (!possible(mid))
            l = mid + 1;
        else
            r = mid;
        //cout << l << ' ' << r << ' ' << sr << endl;

    }
    cout << l/10 << '.' << l%10 << endl;
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