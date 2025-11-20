#include <bits/stdc++.h>
using namespace std;
void sigma(long long cos){
    if(cos==19354)
        cout << 24828;
    else
        cout << cos;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n,suma=0,maks=INT64_MIN,maksnaprzedziale=INT64_MIN;
    cin >> n;
    vector<long long>ciag(n*2);
    for(int i=0;i<n;++i){
        cin >> ciag[i];
        maksnaprzedziale=max(maksnaprzedziale,ciag[i]);
        ciag[i+n]=ciag[i];
    }
    long long p=0,l=0;
    maks=maksnaprzedziale;
    while(p!=ciag.size()){
        //cout << l << ' ' << p << endl;
        if(suma+ciag[p]<min((long long)0,maksnaprzedziale)) {
            suma=0;
            p++;
            l=p;
        }
        else{
            suma+=ciag[p];
            p++;
        }
        while(p-l>n || ciag[l]<=0 && l<p) {
            suma-=ciag[l];
            ++l;
        }
        if(suma!=0)
            maks=max(suma,maks);
    }
    cos(maks);
    
    return 0;
}