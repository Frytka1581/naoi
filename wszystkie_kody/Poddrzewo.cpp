#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n;
    vector<int>ciag(10e6+7);
    for(int i=0;i<n;++i){
        cin >> k;
        ciag[k]++;
        //cin >> ciag[i];
    }
    if(ciag[1]==0){
        cout << 2 << endl << 2 << endl << 1 << ' ' << 2;
    }
    else if(ciag[1]==1)
        cout << 1 << endl << 2 << endl << 1 << ' ' << 2;
    else
        cout << 0 << endl << 2 << endl << 1 << ' ' << 2;
    return 0;
}