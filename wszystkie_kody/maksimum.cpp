#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector<long long>range_tree(1<<20);
void zmiana(long long n,long long k, long long podloga){
    range_tree[(1<<podloga)+n-1]=k;
    long long i=(1<<podloga)+n-1; 
    i/=2;
    podloga--;
    while(podloga>=0){
        range_tree[i]=max(range_tree[i*2],range_tree[i*2+1]);
        i/=2;
        podloga--;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n,q,k;
    cin >> n >> q;
    vector<long long>ciag;
    long long poziom=ceil(log2(n));
    for(int i=0;i<n;++i){
        cin >> range_tree[i+(1<<(poziom))];
    }
    for(int i=poziom-1;i>=0;--i){
        for(int j=(1<<i);j<(1<<(i+1));++j){
            range_tree[j]=max(range_tree[j*2],range_tree[j*2+1]);
        }
    }
    long long l,p;
    cout << range_tree[1] << endl;
    for(int i=0;i<q;++i){
        cin >> l >> p;
        zmiana(l,p,poziom);
        cout << range_tree[1] << endl;
    }
    /*for(int i=0;i<(1<<(poziom+1));++i){
        cout << range_tree[i] << ' ' << i << endl;
    }
    */
    return 0;
}