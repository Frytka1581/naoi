#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>
#include <functional>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define st first
#define nd second
#define pb push_back
const ll inf = 1e9;
const ll infl = 1e18;

ll mod = 1e9 + 7;

vector<ll> kmp(string s) {
    ll n = s.length();
    vector<ll> pi(n);
    for (ll i = 1; i < n; i++) {
        ll j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    vector<ll> wynik;
    ll p = pi[n-1];
    while(p != 0){
        wynik.push_back(n-p);
        p = pi[p-1];
    }
    wynik.push_back(n);

    return wynik;
}


ll dp[1000007];


ll main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string slowo;
    ll n, k;
    cin >> n >> k;
    cin >> slowo;
    vector<ll> boundy = kmp(slowo);


    
    dp[n] = 1;
    for(ll i = n; i < k; i++){
        for(ll j : boundy){
            if(i + j <= k){
                dp[i+j]+=dp[i];
                dp[i+j] = dp[i+j] % mod;
            }
    
        }
        
    }

    cout << dp[k] << "\n";

    return 0;
}




