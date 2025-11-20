#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,a;
    cin >> n;

    for(int i=0;i<n;++i){
        cin >> a;
        if(a%2==0){ cout << -1 << endl; continue; }
        for(int j=0;j<a;++j){
            cout << (j*2)%a+1 << ' ';

        }
        cout << endl;
    }
    return 0;
}