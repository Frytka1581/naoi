#include <bits/stdc++.h>
using namespace std;
using i64 = int;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    i64 n, m, h, w, l;
    i64 minn = 1e8;
    cin >> n >> m;
    vector<pair<i64, pair<i64, i64>>> ciag;
    for (int i = 0; i < n; ++i)
    {
        cin >> l >> w >> h;
        ciag.push_back({w, {h, l}});
    }
    sort(ciag.rbegin(), ciag.rend());
    vector<i64> dp(minn + 5);
    i64 maxi = 0;
    i64 wp = 1e8, suma = 0;
    for (int i = 0; i < n; ++i)
    {
        w = ciag[i].first;
        
        for (int j = w + 1; j < min(w * 2, minn); ++j)
        {
            dp[j - w] = min(max(dp[j - w], dp[j] + ciag[i].second.first),minn);
        }
        for (int j = min(2 * wp, minn); j >= 2 * w; --j)
        {
            maxi = min(max(dp[j], maxi),minn);
        }
        dp[w] = min(minn,max(maxi+ciag[i].second.first, dp[w]));
        wp = w;
        if (maxi + ciag[i].second.second > m) suma++;
        else {
            for(int j=w+1;j<min(2*w,minn);++j){
                if (minn,dp[j] + ciag[i].second.second > m){
                    suma++;
                    //cout << dp[j] << endl;
                    break;
                }
            }
        }
        // for(int i=0;i<11;++i){
        //     cout << dp[i]<<' ';
        // }
        // cout << endl;
        
    }
    cout << n-suma;
    return 0;
}