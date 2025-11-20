#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> kasa(n);
    for (int i = 0; i < n; ++i)
        cin >> kasa[i];

    const int INF = 1e9;
    vector<int> dp(k + 1, INF);
    dp[0] = 0; 

    for (int i=0;i<n;++i) {
        for (int j = kasa[i]; j <= k; ++j) {
            dp[j] = min(dp[j], dp[j - kasa[i]] + 1);
        }
    }

    if (dp[k] == INF)
        cout << "NIE" << endl;
    else
        cout << dp[k] << endl;

    return 0;
}
