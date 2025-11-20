#include <bits/stdc++.h>
using namespace std;

void mnoz(vector<vector<int>>& macierz1, vector<vector<int>>& macierz2) {
    int x = macierz1[0][0] * macierz2[0][0] + macierz1[0][1] * macierz2[1][0];
    int y = macierz1[0][0] * macierz2[0][1] + macierz1[0][1] * macierz2[1][1];
    int z = macierz1[1][0] * macierz2[0][0] + macierz1[1][1] * macierz2[1][0];
    int w = macierz1[1][0] * macierz2[0][1] + macierz1[1][1] * macierz2[1][1];

    macierz1[0][0] = x;
    macierz1[0][1] = y;
    macierz1[1][0] = z;
    macierz1[1][1] = w;
}

void potegujMacierz(vector<vector<int>>& macierz1, int n) {
    if (n == 0 || n == 1) return;

    vector<vector<int>> macierz2 = {{1, 1}, {1, 0}};
    
    potegujMacierz(macierz1, n / 2);
    mnoz(macierz1, macierz1);

    if (n % 2 != 0) {
        mnoz(macierz1, macierz2);
    }
}

int ntyFibonacci(int n) {
    if (n <= 1) return n;
    
    vector<vector<int>> macierz1 = {{1, 1}, {1, 0}};
        
    potegujMacierz(macierz1, n - 1);
    
    return macierz1[0][0];
}

int main() {
    int n;
    cin >> n;
    int wynik = ntyFibonacci(n);
    cout << wynik << endl;
    
    return 0;
}
