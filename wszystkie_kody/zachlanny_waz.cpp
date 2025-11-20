#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,k;
    cin >> n >> m;
    vector<vector<ll>>ciag(n+1,vector<ll>(m+1,0));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin >> k;
            if(i==1 && j==1)
                ciag[i][j]=k;
            else if(i==1)
                ciag[i][j]=ciag[i][j-1]+k;
            
            else if(j==1)
                ciag[i][j]=ciag[i-1][j]+k;
            
            else
            ciag[i][j]=max(ciag[i][j-1]+k,ciag[i-1][j]+k);
        }

    }
    cout << max(ciag[n][m],(ll)0) << endl;
    return 0;
}