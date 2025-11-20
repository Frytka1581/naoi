#include <bits/stdc++.h>
using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, k,minus=0,wynik;
    vector<long long>dostawy(1);
    priority_queue<long long>klienci;
    cin >> n;
    for(int i=0;i<n;++i){
        cin >> k;
        dostawy.push_back(dostawy[i]+k);
    }
    for(int i=0;i<n;++i){
        cin >> k;
        if(dostawy[i+1]-minus-k>=0){
            minus+=k;
            klienci.push(k);
        }
        else{
            if(klienci.size()>0 && klienci.top()>k){
                minus-=klienci.top();
                klienci.pop();
                klienci.push(k);
                minus+=k;
            }
        }
    }
    cout << klienci.size() << endl;
    return 0;
}