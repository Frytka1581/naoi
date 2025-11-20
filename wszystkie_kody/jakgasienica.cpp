#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,y,maks=0;
    cin >> n >> y;
    vector<int>ciag(n);
    for(int i=0;i<n;++i){
        cin >> ciag[i];
    }
    int p=0,k=0,s=0,w1,w2;
    while(k!=ciag.size()){
        s+=ciag[k];
        while(s>y){
            s-=ciag[p];
            p++;
        }
        if(s>maks){
            maks=s;
            w1=p;w2=k;
        }
        k++;
    }
    cout << w1+1<< ' ' << w2+1;
    return 0;
}
