#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<pair<ll,ll>>ciag(n);
    for(int i=0;i<n;++i){
        cin >> ciag[i].second >> ciag[i].first;
    }
    sort(ciag.begin(),ciag.end());
    ll aktualny = -1e10,suma = 0;
    for(int i=0;i<ciag.size();++i){
        if(ciag[i].second>=aktualny){
            aktualny = ciag[i].first;
            suma++;
        }
    }
    cout << suma;
    return 0;
}