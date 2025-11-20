#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 998244353;
ll x;
vector<ll>ciag;
vector<pair<ll,pair<ll,ll>>>pierwiastki;

void dodaj(ll l, ll r,ll b,ll c){
    for(int i=l;i<r;++i){
        if(i%x==0 && i+x<r){
            pierwiastki[i/x].first*=b;
            pierwiastki[i/x].first%=MOD;
            pierwiastki[i/x].first+=c*x;
            pierwiastki[i/x].first%=MOD;
            pierwiastki[i/x].second.first*=b;
            pierwiastki[i/x].second.first%=MOD;
            pierwiastki[i/x].second.second*=b;
            pierwiastki[i/x].second.first%=MOD;
            pierwiastki[i/x].second.second+=c;
            pierwiastki[i/x].second.second%=MOD;
            i+=x-1;
        }
        else{
            pierwiastki[i/x].first+=MOD;
            pierwiastki[i/x].first-=ciag[i];
            ciag[i]*=b;
            ciag[i]%=MOD;
            ciag[i]+=c;
            ciag[i]%=MOD;
            pierwiastki[i/x].first+=ciag[i];
            pierwiastki[i/x].first%=MOD;
        }
    }
}
ll suma(ll l, ll r){
    ll s=0;
    for(int i=l;i<r;++i){
        if(i%x==0 && i+x<r){
            s+=pierwiastki[i/x].first;
            s%=MOD;
            i+=x-1;
        }
        else{
            s+=ciag[i]*pierwiastki[i/x].second.first;
            s%=MOD;
            s+=pierwiastki[i/x].second.second;
            s%=MOD;
        }
    }
    return s;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,q,l,r,b,c;
    bool operacja;
    cin >> n >> q;
    x=ceil(sqrt(n));
    ciag.resize(n);
    pierwiastki.resize(x,{0,{1,0}});
    for(int i=0;i<n;++i){
        cin >> ciag[i];
        pierwiastki[i/x].first+=ciag[i];
    }
    for(int i=0;i<q;++i){
        cin >> operacja;
        if(operacja){
            cin >> l >> r;
            cout << suma(l,r) << '\n';
            // for(int j=0;j<n;++j){
            //     cout << ciag[j] << ' ';
            // }
            // cout << endl;
            // for(int j=0;j<x;++j){
            //     cout << pierwiastki[j].first << ' ' << pierwiastki[j].second.first << ' ' << pierwiastki[j].second.second  << endl;
            // }
        }
        else{
            cin >> l >> r >> b >> c;
            dodaj(l,r,b,c);
            // for(int j=0;j<n;++j){
            //     cout << ciag[j] << ' ';
            // }
            // cout << endl;
            // for(int j=0;j<x;++j){
            //     cout << pierwiastki[j].first << ' ' << pierwiastki[j].second.first << ' ' << pierwiastki[j].second.second  << endl;
            // }

        }
    }
    return 0;
}