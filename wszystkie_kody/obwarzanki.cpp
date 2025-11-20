#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k,s1=0,s2=0;
    cin >> n >> k;
    vector<int>ciag1(n),ciag2(n);
    for(int i=0;i<n;++i){
        cin >> ciag1[i];
        cin >> ciag2[i];
    }
    int l = ciag1[k-1],p = ciag2[k-1];
    for(int i=k;i<n;++i){
        if(ciag2[i]>l && ciag1[i]<p){
            s1++;
            l=min(ciag1[i],l);
            p=max(ciag2[i],p);
        }
    }
    l = ciag1[k-1];p = ciag2[k-1];
    for(int i=k-2;i>=0;--i){
        if(ciag2[i]>l && ciag1[i]<p){
            s2++;
        l=min(ciag1[i],l);
        p=max(ciag2[i],p);
        }
    }
    cout << min(s1,s2);
    return 0;
}