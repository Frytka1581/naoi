#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,a,b;
    cin >> n;
    vector<pair<int,int>>ciag;
    for(int i=0;i<n;++i){
        cin >> a >> b;
        ciag.push_back({a-b,(b+a)*-1});
    }
    sort(ciag.begin(),ciag.end());
    int s = 1, pomoc = 0;
    a = ciag[0].first , b = ciag[0].second * -1;
    for(int i=1;i<n;++i){
        if(ciag[i].second*-1 > b){
            s++;
            a = ciag[i].first;
            pomoc = i;
            b = ciag[i].second*-1;
        }
        /*else if(pomoc + a < i){
            cout << pomoc << ' ' << a << endl;
            s++;
            a = ciag[i].first;
            pomoc = i;
            b = ciag[i].second*-1;
        }*/
    }
    cout << s ;
    return 0;
}