#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t,n;
    cin >> t;
    for(int test=0;test<t;++test){
        cin >> n;
        int czy = 0;
        for(int i=0;i<n;++i){
            for(int j=i+1;j<n;++j){
                cout << i+1 << ' ' << j+1 << endl;
                cout.flush();
                cin >> czy;
                if(czy>0) break;
            }
            if(czy>0) break;
        }
    }
    return 0;
}