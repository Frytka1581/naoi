#include <bits/stdc++.h>
using namespace std;
int plecak(vector<int> ciag,int u){
    vector<vector<bool>>bag(ciag.size()+1,vector<bool>(u+1));
    for(int i=1;i<=ciag.size();++i){
        bag[i][ciag[i-1]]=1;
        for(int j=0;j<=ciag[i-1];++j){
            bag[i][j]=max(bag[i-1][j],bag[i][j]);
        }
        for(int j=ciag[i-1]+1;j<=u;++j){
            if(bag[i-1][j-ciag[i-1]]==1) bag[i][j] = 1;
        }
    }
    int wynik = 0;
    for(int j=0;j<=u;++j){
        if(bag[bag.size()-1][j]) wynik++;
    }
    
    return wynik;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    vector<int>ciag(n);
    vector<int>komb;
    int maks  = 0;
    pair<int,int>wynik={0,0};
    for(int i=0;i<n;++i) cin >> ciag[i];
    int maa = 0;
    for(int i=0;i<ciag.size();++i){
        maa = max(maa,ciag[i]);
    }
    maa+=20;
    for(int i=0;i<ciag.size();++i){
        for(int j=1;j<maa;++j){
            komb = ciag;
            komb[i] = j;
            sort(komb.begin(),komb.end());
            int x = plecak(komb,maa);
            if(maks<x){
                wynik = {ciag[i],j};
                maks = x;
            }
            
        }
    }
    cout << wynik.first << ' ' << wynik.second;
    return 0;
}