#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define s(x) x.size()
#define sort(x) sort(x.begin(),x.end())
#define rsort(x) sort(x.rbegin(),x.rend())
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;

void solve() {
    ll x, y, k; cin >> x >> y >> k;
    ll initial = 1000000000000LL;
    if (y == 1) {
        if (x > 0) {
            cout << -1 << endl;
        } else {
            cout << k << endl;
        }
        return;
    }
    ll l = initial;
    ll tt = x;
    while (tt > 0) {
        ll d = l / y;
        if (d == 0) break;
        ll r = l % y;
        ll s = r / d;
        s = min(s, tt);
        l -= s * d;
        tt -= s;
        if (tt > 0) {
            l -= d;
            tt--;
        }
    }
    if (l < k) {
        cout << -1 << endl;
        return;
    }
    ll m = y - 1;
    ll pos = k;
    tt = x;
    while (tt > 0) {
        ll d = (pos - 1) / m;
        if (d == 0) break;
        ll max_p = (d + 1) * m + 1;
        ll distance = max_p - pos;
        ll s = (distance - 1) / d;
        s = min(s, tt);
        pos += s * d;
        tt -= s;
        if (tt > 0) {
            pos += d;
            tt--;
        }
        if (pos > initial) {
            cout << -1 << endl;
            return;
        }
    }
    cout << pos << endl;
}

int main() {
    fastio;
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}