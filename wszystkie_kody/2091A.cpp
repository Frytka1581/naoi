#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t,n,a;
    cin >> t;
    for(int j=0;j<t;++j){
        cin >> n;
        int zero=0,dwa=0,piec=0,trzy=0,jeden=0;
        bool czyjest = false;
        for(int i=0;i<n;++i){
            cin >> a;
            if(a == 0) zero++;
            if(a == 1) jeden++;
            if(a == 2) dwa++;
            if(a == 3) trzy++;
            if(a == 5) piec++;
            if(zero > 2 && jeden > 0 && trzy > 0 && dwa > 1 && piec > 0 && czyjest== false){
                czyjest = true;
                cout << i+1 << endl;
            }
        }
        if(czyjest == false)
            cout << 0 << endl;
    }
    return 0;
}