#include <bits/stdc++.h>
using namespace std;

vector<long long> ryby;
vector<vector<long long > > wierzcholki;
vector<long long> wynik;
vector<bool> odwiedzone;

void DFS(long long n) {
    odwiedzone[n] = true;
    wynik[n] = ryby[n];

    for (int i=0;i<wierzcholki[n].size();++i) {
        long long sasiad = wierzcholki[n][i];
        if (!odwiedzone[sasiad]) {
            DFS(sasiad);
            wynik[n] = max(wynik[n], ryby[n] + wynik[sasiad]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    ryby.resize(n + 1);
    wierzcholki.resize(n + 1);
    wynik.resize(n + 1, 0);
    odwiedzone.resize(n + 1, false);

    for (long long i = 1; i <= n; ++i) {
        cin >> ryby[i];
    }

    for (long long i = 0; i < n - 1; ++i) {
        long long l, p;
        cin >> l >> p;
        wierzcholki[l].push_back(p);
        wierzcholki[p].push_back(l);
    }

    DFS(1);

    cout << wynik[1] << "\n";
    return 0;
}
