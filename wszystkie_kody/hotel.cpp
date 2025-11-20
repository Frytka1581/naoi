#include <bits/stdc++.h>
using namespace std;
vector<int> sito(int n){
    vector<int>ktore(n+2,0);
    for(int i=2; i<n+2; ++i){
         if(ktore[i]==0){
            for(int j = i; j < n + 2; j += i)
                if(ktore[j]==0)
                    ktore[j] = i;
        }
    }
    return ktore;
}
vector<int>ciag;

int ile(int n){
    int s=1,pop=ciag[n],s2=1;

    while(n!=1){  
        n/=ciag[n];
        if(pop!=ciag[n]){
            s*=(s2+1);
            s2=0;
        }
        pop=ciag[n];
        s2++;
        
    }

    return s;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie();
    int n,l,p,k,s,maks=0;
    
    cin >> n;
    vector<int>ciag2;
    for(int i=0;i<n;++i){
        cin >> l >> p;
        k = __gcd(l,p);
        ciag2.push_back(k);
        maks=max(k,maks);
    }
    ciag=sito(maks);
    ciag[1]=1;
    for(int i=0;i<n;++i){
        cout << ile(ciag2[i]) << endl;
        
    }
    return 0;
}