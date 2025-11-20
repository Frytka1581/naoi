#include <vector>
#include <iostream>
using namespace std;
vector<vector<pair<int,int>>>dp;
void polacz(int i, int j){
    int k = i;
    while(k!=j){
        //cout << k << ' ' << j << endl;
        dp[i][j] = min(dp[i][j],{dp[i][k].first + dp[k+1][j].first, dp[i][k].first + dp[k+1][j].first + dp[i][k].second + dp[k+1][j].second});
        k++;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n;
    dp.resize(n,vector<pair<int,int>>(n,{INT32_MAX,INT32_MAX}));
    for(int i=0;i<n;++i){
        cin >> k;
        dp[i][i] = {k,0};
    }

    for(int i=1;i<n;++i){
        for(int j=0;j<n-i;++j){
            polacz(j,j+i);
        }
    }
    cout << dp[0][n-1].second << endl;
    
    return 0;
}