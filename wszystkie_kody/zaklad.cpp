#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n,k,l,p;
    vector<pair<long long,pair<long long,long long > > >pozytywne,negatywne;
    vector<long long>ciag;
    cin >> n >> k;
    for(int i=0;i<n;++i){
        cin >> l >> p;
        if(p<l)
            negatywne.push_back(make_pair(p,make_pair(l,i)));
        else
            pozytywne.push_back(make_pair(l,make_pair(p,i)));
            
    }
    sort(pozytywne.begin(),pozytywne.end());
    for(int i=0;i<pozytywne.size();++i){
        if(k<=pozytywne[i].first){
            cout << "NIE";
            return 0;
        }
        k+=(pozytywne[i].second.first-pozytywne[i].first);
        ciag.push_back(pozytywne[i].second.second+1);

    }
    sort(negatywne.begin(),negatywne.end());
    for(int i=negatywne.size()-1;i>=0;--i){
        if(k<=negatywne[i].second.first){
            cout << "NIE";
            return 0;
        }
        k-=negatywne[i].second.first;
        k+=negatywne[i].first;
        ciag.push_back(negatywne[i].second.second+1);
        
    }
    cout << "TAK" << endl;
    for(int i=0;i<ciag.size();++i){
        cout << ciag[i] << ' ';
    }
    return 0;
}
//g++ -o zaklad zaklad.cpp&& ./zaklad < test.in