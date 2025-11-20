#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    long long a=1,b=1,c=0;
    vector<long long>ciag;
    ciag.push_back(a);
    ciag.push_back(b);
    while(ciag.size()<n){
        c=a+b;
        b=a;
        a=c;
        ciag.push_back(c);
        
    }
    cout << ciag[n];
    return 0;
}