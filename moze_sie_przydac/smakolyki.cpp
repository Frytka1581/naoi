#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll>c1(n),c2(n-1);
    for(int i=0;i<n;++i){
        cin >> c1[i];
    }
    for(int i=0;i<n-1;++i){
        cin >> c2[i];
    }
    
    return 0;
}