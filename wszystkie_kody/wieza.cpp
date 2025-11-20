#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,k;    
    cin >> n >> m;
    vector<int>ciag(n+1);
    for(int i=1;i<=n;++i){
        cin >> ciag[i];
        ciag[i]=max(ciag[i],ciag[i-1]);
    }
    for(int i=0;i<m;++i){
        cin >> k;
        auto it = upper_bound(ciag.begin(),ciag.end(),k-1);
        cout << it-ciag.begin()-1 << ' ';
    }
    return 0;
}