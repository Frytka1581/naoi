#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, wydac;
    cin >> n;

    vector<int> nominaly(n), ilosc(n);
    for (int i = 0; i < n; ++i) {
        cin >> nominaly[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> ilosc[i];
    }

    cin >> wydac;

    const int makss = 1e9;
    vector<int> dp(wydac + 1, makss);
    vector<int> ostatni(wydac + 1, -1);

    dp[0] = 0;
    vector<int> suma(wydac + 1, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < ilosc[i]; ++j) {
            for (int k = wydac; k >= nominaly[i]; --k) { 
                if (dp[k - nominaly[i]] + 1 < dp[k]) {
                    dp[k] = dp[k - nominaly[i]] + 1;
                    ostatni[k] = nominaly[i];
                }
            }
        }
    }
    for(int i=0;i<wydac+1;++i){
        cout << dp[i] << ' ';  
    }
    cout << endl;
    for(int i=0;i<ostatni.size();++i){
        cout << ostatni[i] << ' ';
    }
    vector<int> wynik(20000+1, 0);
    int kwota = wydac;
    while (kwota > 0) {
        int index = ostatni[kwota];
        wynik[index]++;
        kwota -= ostatni[kwota];
    }
    
    /*for (int i = 1; i <= 20000; ++i) {
        if(wynik[i]>0)
        cout << wynik[i] << " ";
    }
    */
    return 0;
}
