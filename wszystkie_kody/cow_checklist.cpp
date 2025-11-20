#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ll koszt(pair<ll,ll>x,pair<ll,ll>y){
//     ll w=(abs(x.first-y.first)*abs(x.first-y.first))+(abs(x.second-y.second)*abs(x.second-y.second));
//     return w;
// }
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("checklist.in", "r", stdin);
	// freopen("checklist.out", "w", stdout);
    cout << "Zrobione" << endl;
    // ll h,g;
    // cin >> h >> g;
    // vector<pair<ll,ll>>hc(h),gc(g);
    // vector<vector<vector<ll>>>dp(h+1,vector<vector<ll>>(g+1,vector<ll>(2,1e18)));
    // for(int i=0;i<h;++i){
    //     cin >> hc[i].first >> hc[i].second;
    // }
    // for(int i=0;i<g;++i){
    //     cin >> gc[i].first >> gc[i].second;
    // }
    // dp[1][0][0]=0;
    
    // for(int i=0;i<=h;++i){
    //     for(int j=0;j<=g;++j){
            
    //         if(i>1){
    //             dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][0]+koszt(hc[i-1],hc[i-2]));
    //         }
    //         if(j>1){
    //             dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+koszt(gc[j-1],gc[j-2]));
    //         }
    //         if(i>0 && j>0){
    //             dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][1]+koszt(hc[i-1],gc[j-1]));
    //             dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+koszt(hc[i-1],gc[j-1]));
    //         }
    //     }
    // }
    // cout << dp[h][g][0] << endl;
    // for(int i=0;i<=h;++i){
    //     for(int j=0;j<=g;++j){
    //         cout << dp[i][j][0] << ' ';
    //     }
    //     cout << endl;
    // }
    // for(int i=0;i<=h;++i){
    //     for(int j=0;j<=g;++j){
    //         cout << dp[i][j][1] << ' ';
    //     }
    //     cout << endl;
    // }
    return 0;
}