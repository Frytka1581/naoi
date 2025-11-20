#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,op,x,y;
    cin >> n;
    set<pair<int,int>>
    vector<pair<ll,ll>>kont;

    for(int i=0;i<n;++i){
        cin >> op >> x >> y;
        if(op==1){
            kont.push_back({x,y});
            maks=max(maks,{x*x+2*x*y,y*y});
        }
    }
    cout << maks.first << ' ' << maks.second << endl;
    return 0;
}