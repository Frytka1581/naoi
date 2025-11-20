#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n,m,q,a1,b1,a2,b2,k;
    cin >> n >> m;
    vector<vector<long long>>ciag(1001,vector<long long>(1001));
    for(int i=1;i<n+1;++i){
        for(int j=1;j<m+1;++j){
            cin >> k;
            ciag[i][j]=ciag[i-1][j]+ciag[i][j-1]+k-ciag[i-1][j-1];
        }
    }
    cin >> q;
    for(int i=0;i<q;++i){
        cin >> a1 >> b1 >> a2 >> b2;
        cout << ciag[a2][b2]-ciag[a1-1][b2]-ciag[a2][b1-1]+ciag[a1-1][b1-1] << endl;
    }
    return 0;
}