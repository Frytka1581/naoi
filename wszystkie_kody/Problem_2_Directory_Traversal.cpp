#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100005;
vector<int> dzieci[MAX_N];
string nazwy[MAX_N];
int dlugosc_nazwy[MAX_N];
bool czy_plik[MAX_N];
int liczba_plikow[MAX_N];
ll suma_dlugosci_poddrzewa[MAX_N];
ll calkowity_koszt[MAX_N];
ll minimum = 1e18;
int calkowita_liczba_plikow;

void dfs_poddrzewa(int u) {
    liczba_plikow[u] = (czy_plik[u] ? 1 : 0);
    suma_dlugosci_poddrzewa[u] = 0;
    for (int v : dzieci[u]) {
        dfs_poddrzewa(v);
        liczba_plikow[u] += liczba_plikow[v];
        suma_dlugosci_poddrzewa[u] += suma_dlugosci_poddrzewa[v] + (ll)liczba_plikow[v] * (dlugosc_nazwy[v] + (czy_plik[v] ? 0 : 1));
    }
}

void dfs_rerooting(int u, ll koszt_gora) {
    calkowity_koszt[u] = koszt_gora + suma_dlugosci_poddrzewa[u];
    minimum = min(minimum, calkowity_koszt[u]);
    
    ll pelna_suma_poddrzewa = 0;
    for (int v : dzieci[u]) {
        pelna_suma_poddrzewa += suma_dlugosci_poddrzewa[v] + (ll)liczba_plikow[v] * (dlugosc_nazwy[v] + (czy_plik[v] ? 0 : 1));
    }
    
    for (int v : dzieci[u]) {
        ll wklad_v = suma_dlugosci_poddrzewa[v] + (ll)liczba_plikow[v] * (dlugosc_nazwy[v] + (czy_plik[v] ? 0 : 1));
        ll nowy_koszt_gora = koszt_gora + pelna_suma_poddrzewa - wklad_v + 3LL * (calkowita_liczba_plikow - liczba_plikow[v]);
        dfs_rerooting(v, nowy_koszt_gora);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("dirtraverse.in", "r", stdin);
    freopen("dirtraverse.out", "w", stdout);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s;
        int m;
        cin >> s >> m;
        nazwy[i] = s;
        dlugosc_nazwy[i] = s.length();
        czy_plik[i] = (m == 0);
        for (int j = 0; j < m; ++j) {
            int a;
            cin >> a;
            dzieci[i].push_back(a);
        }
    }
    
    dfs_poddrzewa(1);
    calkowita_liczba_plikow = liczba_plikow[1];
    dfs_rerooting(1, 0);
    
    cout << minimum << endl;
    return 0;
}