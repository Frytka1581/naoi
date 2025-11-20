#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const ll MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    int maxN = 1000;
    vector<ll> fact(maxN+1, 1);
    for(int i = 1; i <= maxN; ++i){
        fact[i] = fact[i-1] * i % MOD;
    }

    while(t--){
        int n;
        cin >> n;
        if(n % 2 == 1){
            cout << 0 << "\n";
        } else {
            int half = n / 2;
            ll res = fact[half];
            res = (res * res) % MOD;
            cout << res << "\n";
        }
    }
    return 0;
}
