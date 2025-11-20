#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,p,k;
    cin >> n;
    vector<int>ciag(n);
    vector<pair<int,int>>c2;
    for(int i=0;i<n;++i){
        cin >> p >> k;
        c2.push_back({k,p});
    }
    sort(c2.begin(),c2.end());
    int pozycja=-1,s=0;
    for(int i=0;i<c2.size();++i){
        if(pozycja<c2[i].second){
            s++;
            pozycja= c2[i].first;
        }
    }
    cout << s;
    return 0;
}