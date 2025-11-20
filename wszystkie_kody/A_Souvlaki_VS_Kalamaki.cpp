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
    vector<int> v(n);
    for (int i = 0; i < n; ++i){
        cin >> v[i];
    }
    sort(v);
    for (int i = 1; i < n-1; i+=2) {
        if(v[i]!=v[i+1]){
            cout << "NO" << '\n';
            return ;
        }
    }
    cout << "YES" << '\n';
}

int main() {
    fastio;
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}