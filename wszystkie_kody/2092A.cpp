#include <bits/stdc++.h>
using namespace std;

int max_przyjemnosc(vector<int>& a) {
    int n = a.size();
    sort(a.begin(), a.end());
    int wynik = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            wynik = max(wynik, gcd(a[j] - a[0], a[i] - a[0]));
        }
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        cout << max_przyjemnosc(a) << "\n";
    }
    return 0;
}
