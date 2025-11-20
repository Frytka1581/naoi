#include <bits/stdc++.h>
using namespace std;
vector<int>drzewo;
int BASE=1;
int n;
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
int licz(vector<int>ciag) {
    for(int i=0;i<n;++i) cin >> ciag[i];
    ciag=kompresja(ciag);
    BASE=1;
    drzewo = {};
    while(BASE<n) BASE*=2;
    drzewo.resize(BASE*2);
    int s=0;
    for(int i=n-1;i>=0;--i){
        aktualizuj(ciag[i]);
        s+=rec(1,{0,ciag[i]-2},{0,BASE-1});
    }
    return s;
}
int main() {
    
    
    cin >> n;
    vector<int> input(n);
    for(int i=0;i<n;++i){
        cin >> input[i];
    }
    vector<int> sorted = input;
    sort(sorted.begin(), sorted.end());
    int s=0;
    do {
        if (sorted <= input) {
            s+=  licz(sorted);
            
        }
    } while (next_permutation(sorted.begin(), sorted.end()));
    cout << s;
    return 0;
}