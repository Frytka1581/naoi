#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, a,maks= INT64_MIN;
    cin >> n;
    
    vector<ll> ciag(1e5 + 7);
    vector<ll> dp(1e5 + 2);
    for (ll i = 0; i < n; ++i)
    {
        cin >> a;
        //cout << a << endl;
        ciag[a]++;
        // cout << ciag[a] << endl;
    }
    for (ll i = 2; i < 1e5 + 2; ++i)
    {
        dp[i] = max(dp[i - 2] + ciag[i - 2] * (i - 2), dp[i - 1]);
        maks=max(maks,dp[i]);
    }
    cout << maks;
    return 0;
}