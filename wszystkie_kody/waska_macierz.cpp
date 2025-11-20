#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,a,b,c;
    cin >> n;
    vector<tuple<ll,ll,ll>>ciag(n);
    vector<tuple<ll,ll,ll>>dp(n+1);
    for(int i=0;i<n;++i){
        cin >> a >> b >> c;
        ciag[i]={a,b,c}; 
    }
    for(int i=1;i<=n;++i){
        dp[i]={max(get<1>(dp[i-1]),get<2>(dp[i-1]))+get<0>(ciag[i-1]),max(get<0>(dp[i-1]),get<2>(dp[i-1]))+get<1>(ciag[i-1]),max(get<0>(dp[i-1]),get<1>(dp[i-1]))+get<2>(ciag[i-1])};
        //cout << get<0>(dp[i]) << ' ' << get<1>(dp[i]) << ' ' <<  get<2>(dp[i]) << endl;
    }
    cout << max(get<0>(dp[n]),max(get<1>(dp[n]),get<2>(dp[n]))) << endl;
    return 0;
}