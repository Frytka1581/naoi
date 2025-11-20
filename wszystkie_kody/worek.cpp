#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,p;
    i64 k;
    map<i64,int> ciag;
    cin >> n;
    for(int i=0;i<n;++i){
       cin >> k;
       ciag[k]++; 
    }
    cin >> p;
    for(int i=0;i<p;++i){
        cin >> k;
        cout << ciag[k] << '\n';
    }
    return 0;
}