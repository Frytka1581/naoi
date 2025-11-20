#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,essa=0;
    cin >> n >> m;
    vector<int>c1(n),c2(m);
    vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int i=0;i<n;++i){
        cin >> c1[i];
        essa+=c1[i];
    }
    for(int i=0;i<m;++i){
        cin >> c2[i];
        essa+=c2[i];
    }

    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            if(i!=0 || j!=0){
                int sigma = 1e9 * -1;
                if(i > 0)
                    sigma = max(c1[i-1]-dp[i-1][j],sigma); 
                if(j>0)
                    sigma = max(c2[j-1]-dp[i][j-1],sigma);
                dp[i][j] = sigma;
            }
        }
    }
    cout << (dp[n][m]+essa)/2;
    return 0;
}