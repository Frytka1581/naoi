#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q,m,maks,suma;
    char c;
    string napis;
    cin >> n >> napis >> q;
    for(int i=0;i<q;++i){
        cin >> m >> c;
        
        int l=0,p=0;
        //cout << n << endl;
        suma = 0;
        maks = 0;
        while(p<n){
            if(napis[p]!=c) suma++;
            while(suma>m){
                if(napis[l]!=c) suma--;
                l++;
            }
            maks = max(maks,p-l+1);
            //cout << l << ' ' << p << ' ' << m << endl;
            p++;
            
        }
        cout << maks << endl;
    }
    return 0;
}