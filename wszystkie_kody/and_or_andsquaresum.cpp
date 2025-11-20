#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,a;
    cin >> n;
    vector<ll>ciag(20);
    for(int i=0;i<n;++i){
        cin >> a;
        for(int bit=0;bit<20;++bit){
            if(((1<<bit)&a))
                ciag[bit]+=1;
        }
    }
    ll suma = 0;
    while(count(ciag.begin(),ciag.end(),0)<20){
        ll wartosc = 0;
        for(int i=0;i<20;++i){
            if(ciag[i]>0){
                wartosc+=(1<<i);
                ciag[i]--;
            }
        }
        suma += wartosc*wartosc;
        // for(int i=0;i<ciag.size();++i){
        //     cout << ciag[i] << ' ';
        // }
        // cout << endl;
    }
    cout << suma << endl;
    return 0;
}
