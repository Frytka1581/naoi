#include <bits/stdc++.h>
using namespace std;
vector<int>drzewo;
int BASE=1;
vector<int>kompresja(vector<int>ciag){
    vector<int>dup=ciag;
    sort(dup.begin(),dup.end());
    map<int,int>mapa;
    vector<int>wynik;
    for(int i=0;i<dup.size();++i){
        mapa[dup[i]]=i+1;
    }
    for(int i=0;i<dup.size();++i){
        wynik.push_back(mapa[ciag[i]]);
    }
    return wynik;
}
void aktualizuj(int n){
    int index=n+BASE-1;
    while(index!=1){
        drzewo[index]++;
        index/=2;
    }
    drzewo[index]++;
}
int rec(int id,pair<int,int>przedzial,pair<int,int>myrange){
    if (przedzial.second < myrange.first || przedzial.first > myrange.second)
        return 0;
    if (przedzial.first <= myrange.first && przedzial.second >= myrange.second)
        return drzewo[id];
    int mid = (myrange.first + myrange.second) / 2;
    return rec(id*2,przedzial,{myrange.first,mid}) + rec(id*2+1,przedzial,{mid+1,myrange.second});
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int>ciag(n);
    for(int i=0;i<n;++i) cin >> ciag[i];
    ciag=kompresja(ciag);

    
    while(BASE<n) BASE*=2;
    drzewo.resize(BASE*2);
    int s=0;
    for(int i=n-1;i>=0;--i){
        aktualizuj(ciag[i]);
        s+=rec(1,{0,ciag[i]-2},{0,BASE-1});
    }
    cout << s;
    return 0;
}