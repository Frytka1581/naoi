#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 998244353;
ll x;
vector<ll>ciag;
vector<pair<ll,pair<ll,ll>>>pierwiastki;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,q,l,r,b,c;
    bool operacja;
    cin >> n >> q;
    ciag.resize(n);

    for(int i=0;i<n;++i){
        cin >> ciag[i];
    }
    for(int i=0;i<q;++i){
        cin >> operacja;
    }
    return 0;
}