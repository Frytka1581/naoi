#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    char znak;
    cin >> n >> k;
    vector<bool>ciag(n);
    for(int i=0;i<n;++i){
        cin >> znak;
        if(znak=='o') ciag[i]=1;
    }
    
    return 0;
}