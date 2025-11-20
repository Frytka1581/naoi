#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    vector<int>c1(n),c2(n);
    for(int i=0;i<n;++i){
        cin >> c1[i];
    }
    for(int i=0;i<n;++i){
        cin >> c2[i];
    }
    vector<pair<int,int>>c3;
    for (int i = 0; i < (1<<(n+1)); i++) {
        int s1=0,s2=0;
        for (int j = 0; j < n; j++) {
            if ((1<<j)&i) s1+=c1[j];
            else s2+=c2[j];
        }
        c3.push_back({s2,s1});
    }
    sort(c3.begin(),c3.end());
    reverse(c3.begin(),c3.end());
    pair<int,int> wynik={1e9,1e9};
    pair<int,int>poprzedni=c3[0];
    for(int i=0;i<c3.size();++i){
        if(c3[i].second<=poprzedni.second) continue;
        if(wynik.first+wynik.second>poprzedni.second+c3[i].first) wynik={c3[i].first,poprzedni.second};
        poprzedni=c3[i]; 
        
    }
    cout << wynik.second+1 << ' ' << wynik.first+1;
    return 0;
}