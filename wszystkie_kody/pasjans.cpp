#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int LIS(vector<int>& karty, bool czy) {
    vector<int> stosy; 
    vector<int>::iterator it;
    for (int i=0;i<karty.size();i++) {
        int karta = karty[i];
        it = upper_bound(stosy.begin(), stosy.end(), karta);
        
        if (it != stosy.end()) {
            if(czy)
            cout << 2 << ' ' << it-stosy.begin()+1 << endl;
            *it = karta;
        } else {
            stosy.push_back(karta);
            if(czy)
            cout << 1 << endl;
        }
    }
    return stosy.size();
}

int main() {
    int n;
    cin >> n;
    vector<int> karty(n);
    for(int i=0;i<n;++i){
        cin >> karty[i];
    }
    int wynik = LIS(karty,0);
    cout << wynik << endl;
    LIS(karty,1);
    return 0;
}
