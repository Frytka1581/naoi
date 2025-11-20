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
bool possible(double value)
{
    double previous = -INF;
    // cout << value << endl;
    for (int i = 0; i < v.size(); i++)
    {
        if(v[i]+value<previous) return false;
        else if (v[i] - value >= previous)
            previous = v[i] - value;
        
    }
    return true;
}
void solve()
{
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }
    double l = 0, r = 1e6, s = 0;
    while (l < r && s < 100)
    {
        double sr = (l + r) / 2;
        sr = round(sr*1000)/1000;
        if (!possible(sr))
            l = sr + 0.001;
        else
            r = sr;
        //cout << l << ' ' << r << endl;
        l = round(l * 1000) / 1000;
        r = round(r * 1000) / 1000;
        if(possible(l)) break;
        else l+=0.001;
        s++;
    }
    //cout << "ODP: ";
    cout << fixed << setprecision(3) << l << endl;
    double previous = -INF;
    for (int i = 0; i < n; i++) {
        if(v[i]-l>=previous){
            cout << fixed << setprecision(3) << v[i]-l << endl;
            previous = v[i]-l;
        }
        else cout << fixed << setprecision(3) << previous << endl;
        
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