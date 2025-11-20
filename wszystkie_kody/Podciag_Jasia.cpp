#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n,k;
    cin >> n;
    vector<long long>dp(n+2);
    for(int i=2;i<n+2;++i){
        cin >> k;
        dp[i]=max(dp[i-2]+k,dp[i-1]);
    }
    
    cout << dp[n+2-1];
    return 0;
}