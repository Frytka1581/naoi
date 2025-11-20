#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll t, k;
    cin >> t >> k;

    vector<ll> dp(1e5 + 1, 0);
    vector<ll> sp(1e5 + 1, 0);

    dp[0] = 1;
    for (int i = 1; i <= 1e5; ++i) {
        dp[i] = dp[i - 1];  
        if (i >= k) {
            dp[i] = (dp[i] + dp[i - k]) % MOD;
        }
    }

    for (int i = 1; i <= 1e5; ++i) {
        sp[i] = (sp[i - 1] + dp[i]) % MOD;
    }

    for (int i = 0; i < t; ++i) {
        ll l, p;
        cin >> l >> p;
        ll result = (sp[p] - sp[l - 1] + MOD) % MOD;  
        cout << result << "\n";
    }

    return 0;
}
