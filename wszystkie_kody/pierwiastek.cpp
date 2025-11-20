#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n;
bool dasie(ll p){
    if(p*p>n) return true;
    return false;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    ll k = 1e9+1,p=0,sr;
    while(p<k){
        sr = (k+p)/2;
        if(dasie(sr)) k=sr;
        else p=sr+1;
        //cout << p << ' ' << k << endl;
    }
    cout << p;
    return 0;
}