#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string napis;
    cin >> napis;
    vector<int>ciag(256,-1);
    vector<int>dp(napis.length()+1,1);
    for(int i=0;i<napis.length();++i){
        char znak = napis[i];
        if(ciag[znak]!=-1){
            dp[i+1]=max(dp[ciag[znak]]+1,dp[i+1]);
        }
        if(ciag[znak-1]!=-1){
            dp[i+1]=max(dp[ciag[znak-1]]+1,dp[i+1]);
        }
        /*if(ciag[znak]==-1){
            dp[i+1]=max(dp[i],dp[i+1]);
        }
        */
        ciag[znak]=i+1;
    }
    int maks=0;
    for(int i=0;i<dp.size();++i){
        //cout << dp[i] << ' ';
        maks=max(dp[i],maks);
    }
    cout  << maks;
    return 0;
}