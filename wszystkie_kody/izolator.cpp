#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,k,suma=0;
    cin >> n;
    vector<ll>ciag;
    for(int i=0;i<n;++i){
        cin >> k;
        ciag.push_back(k);
        suma+=k;
    
        //cout << maks << ' ' << minn << endl;
    }
    sort(ciag.begin(),ciag.end());
    for(int i=0;i<ciag.size()/2;++i){
        suma+=abs(ciag[ciag.size()-i-1]-ciag[i]);
        //cout << ciag[i] << ' ' << ciag[ciag.size()-i-1] << endl;
    }
    //cout << suma << endl;
    cout << suma;
    return 0;
}