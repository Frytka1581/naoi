#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t,n,s1,s2,s3,s4;
    char k;
    cin >> t;
    
    for(int o=0;o<t;++o){
        cin >> n;
        s1=0,s2=0;
        for(int i=0;i<n;++i){
            cin >> k;
            if(i%2==0 && k == '1') s1--;
            else if(i%2==0 && k == '0') s1++;
            else if(i%2==1 && k == '1') s2--;
            else if(i%2==1 && k == '0') s2++;
        }
        for(int i=0;i<n;++i){
            cin >> k;
            if(i%2==0 && k == '1') s2--;
            else if(i%2==0 && k == '0') s2++;
            else if(i%2==1 && k == '1') s1--;
            else if(i%2==1 && k == '0') s1++;
        }
        if(s1>=0 && s2>=-1) cout << "YES" << endl;
        else cout <<"NO" << endl;
    }
    return 0;
}