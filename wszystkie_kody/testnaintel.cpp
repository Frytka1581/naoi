#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,k,l;
    cin >> n;
    vector<vector<int>>ciag(1e6+1);
    for(int i=0;i<n;++i){
        cin >> k;
        ciag[k].push_back(i);
    }
    cin >> m;
    for(int i=0;i<m;++i){
        cin >> l;
        int ostatni = 0;
        bool czy = false;
        for(int j=0;j<l;++j){
            cin >> k;
            if(czy == true) continue;
            auto it = lower_bound(ciag[k].begin(),ciag[k].end(),ostatni);
            if(it==ciag[k].end()){
                cout << "NIE" << '\n';
                czy = true;
            }
            if(czy == true) continue;
            ostatni = *it + 1;
        }
        //cout << czy ;
        if(czy == false)
            cout << "TAK" << '\n';
    }
    return 0;
}