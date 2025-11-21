#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lld long double
#define pb push_back
#define fi first
#define se second
ll pot(ll a, ll b, ll mod) {
    a %= mod;
    if (b == 1) return a;
    if (b == 0) return 1;
    ll pol = pot(a, b / 2);
    if (b % 2 == 0) return pol * pol % mod;
    return pol * pol % mod * a % mod;
}
ll nwd(ll a, ll b) {
    if (a == 0) return b;
    return nwd(b%a, a);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<int> p(1e6 + 1, 1);
    p[0] = p[1] = 0;
    for (ll i = 2; i <= 1e6; i++) {
        if (p[i]) {
            for (ll j = i * i; j <= 1e6; j += i) {
                if (p[j] == 1) p[j] = i;
            }
        }
    }
}


