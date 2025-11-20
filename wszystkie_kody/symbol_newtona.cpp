#include <bits/stdc++.h>
using namespace std;
const long long MOD=10e9+7;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,k;
    cin >> n;
    for(int i=0;i<n;++i){
        cin >> m >> k;
        cout << (3<<k) << '\n';
    }
    return 0;
}