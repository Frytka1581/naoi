#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long s=1;
    for(int i=1;i<10;++i){
        s*=i;
    }
    cout << s;
    return 0;
}