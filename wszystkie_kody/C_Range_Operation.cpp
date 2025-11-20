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
    int n; cin >> n;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<ll> prefix(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i-1] + a[i];
    }
    ll original = prefix[n];
    ll max_gain = 0;
    ll max_val = -INFL;
    for (int r = 1; r <= n; ++r) {
        ll this_l = prefix[r-1] - (ll)r * (r-1);
        max_val = max(max_val, this_l);
        ll temp = (ll)r * (r + 1) - prefix[r] + max_val;
        max_gain = max(max_gain, temp);
    }
    cout << original + max_gain << endl;
}

int main() {
    fastio;
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}