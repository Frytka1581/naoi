#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,l,p,suma=0;
    cin >> n;
    vector<pair<int,int> >ciag(n);
    int pozycja_gwozdzia=-1;
    for(int i=0;i<n;++i){
        cin >> l >> p;
        ciag[i]=make_pair(p,l);
    }
    sort(ciag.begin(),ciag.end());

    for(int i=0;i<n;++i){
        if(pozycja_gwozdzia<ciag[i].second){
            suma++;
            pozycja_gwozdzia=ciag[i].first;
        }
    }
    cout << suma;
    return 0;
}