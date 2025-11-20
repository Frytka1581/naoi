#include <bits/stdc++.h>
using namespace std;
#define s(x) x.size()

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;
vector<ll>tree;
void update(ll index,ll wartosc){
    tree[index*2] = wartosc;
    ll orxor=0;
    while(index>0){
        if(orxor%2==1)
        tree[index] = tree[index*2]|tree[index*2+1];
        else
        tree[index] = tree[index*2]^tree[index*2+1];
        orxor++;
        index/=2;
    }
}
void solve() {
    ll n,m,l,r; cin >> n >> m;
    n = (1<<n);
    tree.resize(n*4);
    vector<ll> v(n);
    for (int i = 0; i < n; ++i){
        cin >> v[i];
        update(n+i,v[i]);
    }
    // for (int i = 1; i < s(tree); i++) {
    //     cout << tree[i] << ' ';
    // }
    // cout << '\n';
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        update(n+l-1,r);
        cout << tree[1] << '\n';
    }
}

int main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}