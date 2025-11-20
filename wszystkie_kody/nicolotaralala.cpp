#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n,p,q;
int czy(ll wartosc){
    if(wartosc*wartosc*wartosc+p*wartosc>q) return 0;
    if(wartosc*wartosc*wartosc+p*wartosc==q) return 1;
    if(wartosc*wartosc*wartosc+p*wartosc<q) return 2;
    return 0;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    ll b,e,sr,pop;
    for(int i=0;i<n;++i){
        cin >> p >> q;
        b=1;
        e=1e6;
        bool czyjest=true;
        while(b<e){
            sr=(b+e)/2;
            if(czy(sr) == 1){
                cout << sr << endl;
                czyjest = false;
                break;
            }
            if(czy(sr) == 0){
                e=sr;
            }
            if(czy(sr) == 2 ){
                b=sr+1;
            }
        }
        if(czyjest) 
            cout << "NIE" << endl;
    }
    return 0;
}