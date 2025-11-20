#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<long long>>ciag(1001,vector<long long>(1001));

    string a;
    for(int i=1;i<=n;++i){
        cin >> a;
        for(int j=1;j<=a.size();++j){
            ciag[i][j]=ciag[i-1][j]+ciag[i][j-1]-ciag[i-1][j-1]+(a[j-1]-'0');
        }
        
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cout << ciag[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}