#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n=1000;
    long long suma=0;
    for(int i=0;i<n;++i){
        suma+=(i*(i+1)/2)*n;
        //cout << suma << endl;
    }
    cout << suma;
    return 0;
}