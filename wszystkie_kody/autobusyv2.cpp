#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m;
    vector<int> bilety(n), trasy(m), dp(1 << n), gdzie(1 << n), as(1);
    for (int i = 0; i < n; ++i)
    {
        cin >> bilety[i];
    }
    for (int i = 0; i < m; ++i)
    {
        cin >> trasy[i];
        as.push_back(as[i] + trasy[i]);
    }
    for (int i = 0; i < (1 << n); ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if ((i & (1 << j)) == 0)
            {
                auto it = lower_bound(as.begin(), as.end(), as[dp[i]] + bilety[i]);
                if (as[it - as.begin()] != as[dp[i]] + bilety[i])
                    it--;
                int s = (it - as.begin());
                // cout << s << endl;
                dp[i + (1 << j)] = max(s, dp[i + (1 << j)]);
                gdzie[i + (1 << j)]++;
            }
        }
        //
    }
    int minn = INT32_MAX;
    for (int i = 0; i < (1 << n); ++i)
    {
        if (dp[i] == m)
        {
            long long s = 0;
            for (int j = 0; j < n; ++j)
            {
                if ((i & (1 << j)) == 1)
                {
                    s += bilety[j];
                }
            }
            cout << s << endl;
        }
        cout << 123 << endl;
       
    }
    for (int i = 0; i < (1 << n); ++i)
    {
        cout << dp[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < (1 << n); ++i)
    {
        cout << i << ' ';
    }
    return 0;
}