#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll t,n,m,q;

    cin >> t;
    for(int sigma=0;sigma<t;++sigma){
        cin >> n >> m >> q;
        vector<ll>c1(n),c2(m);
        for(int i=0;i<n;++i){
            cin >> c1[i];
        }
        for(int i=0;i<m;++i){
            cin >> c2[i];
        }
        sort(c1.rbegin(),c1.rend());
        sort(c2.rbegin(),c2.rend());
        vector<ll>s1(n+1),s2(m+1);
        for(int i=0;i<c1.size();++i){
            s1[i+1] = s1[i]+c1[i];
        }
        for(int i=0;i<c2.size();++i){
            s2[i+1] = s2[i]+c2[i];
        }
        ll x,y,z;
        long long wynik = 0;
        for(int i=0;i<q;++i){
            cin >> x >> y >> z;
            ll index = 1,index2=0;
            wynik = 0;
            while(index<=x){
                index2=z-index;
                if(index2<=y){
                    wynik = max(wynik,(long long)s1[index]+s2[index2]);
                }
                index++;
            }
            cout << wynik << endl;
        }
    }
    return 0;
}