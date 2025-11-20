#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,k;
    cin >> n >> m >> k;
    vector<ll>c1(n),c2(m);
    for(int i=0;i<n;++i){
        cin >> c1[i];
    }
    for(int i=0;i<m;++i){
        cin >> c2[i];
    }
    sort(c1.begin(),c1.end());
    sort(c2.begin(),c2.end());
    ll i1=0,i2=0,wynik=0;
    while (i1<n && i2<m)
    {
        if(abs(c1[i1]-c2[i2])<=k){
            wynik++;
            i1++;
            i2++;
        }
        else if(c1[i1]<c2[i2]){
            i1++;
        }
        else{
            i2++;
        }
    }
    cout << wynik;
    return 0;
}