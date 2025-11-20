#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t,n,k,lewy,prawy;
    cin >> t;
    for(int o=0;o<t;++o){
        cin >> n >> k >> lewy >> prawy;
        vector<int>ciag(n);
        for(int i=0;i<n;++i){
            cin >> ciag[i];
        }
        set<int>c2;
        int l=0,p=0,suma=0;
        while(p<n){
            c2.insert(ciag[p]);
            
            if(p-l+1<lewy){
                p++;
                continue;
            } 
            while(p-l+1>prawy){
                c2.erase(ciag[l]);
                l++;
            }
            if(c2.size()==k){
                suma+=1;
                //cout << l << ' ' << p << endl;
                auto it = c2.begin();
                while(it!=c2.end()){
                    cout << *it << ' ';
                    it++;
                }
                cout << endl;
            }
            p++;
        }
        cout << suma << endl;
        cout << "-------------" << endl;
    }
    return 0;
}