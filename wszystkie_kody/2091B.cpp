#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t,n,x,a;
    cin >> t;
    for(int j=0;j<t;++j){
        cin >> n >> x;
        int minn=INT32_MAX,s = 0,wynik=0;
        vector<int>ciag;
        for(int i=0;i<n;++i){
            cin >> a;
            ciag.push_back(a);
        }
        sort(ciag.begin(),ciag.end(),greater<int>());
        
        minn = ciag[0];
        if(minn>=x) wynik++;
        else s = 1;
        for(int i=1;i<n;++i){
            minn = ciag[i];
            s++;
            if(minn*s>=x){
                wynik++;
                s=0;
            }
        }
        cout << wynik << endl;
    }
    return 0;
}