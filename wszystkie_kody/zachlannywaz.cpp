#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<long long>> TAB(n, vector<long long>(m));
    vector<long long> kolumny(m, 0);
    vector<long long> wiersze(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> TAB[i][j];
            wiersze[i] += TAB[i][j];
            kolumny[j] += TAB[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << wiersze[i] << ' ';
    }

    cout << endl;
    for (int j = 0; j < m; ++j) {
        cout << kolumny[j] << ' ';
    }

    return 0;
}
