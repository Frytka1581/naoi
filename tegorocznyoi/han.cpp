#include <bits/stdc++.h>
using namespace std;

#define szybki_ios ios::sync_with_stdio(false); cin.tie(nullptr);

struct WezelTrie {
    unordered_map<char,int> dzieci;
    bool koniec;
    int maks_glebokosc;
    int licznik_odwiedzin;
    int rodzic;
    int poziom;

    WezelTrie(int r = -1, int p = 0) 
        : koniec(false), maks_glebokosc(1), licznik_odwiedzin(0), rodzic(r), poziom(p) {}
};

struct DrzewoTrie {
    vector<WezelTrie> wezly;
    vector<vector<pair<int,char>>> posortowane_krawedzie;

    DrzewoTrie() { wezly.emplace_back(); }

    void dodaj_slowo(int idx, string &slowo) {
        if (slowo.empty()) { wezly[idx].koniec = true; return; }
        char znak = slowo.back(); slowo.pop_back();
        if (!wezly[idx].dzieci.count(znak)) {
            int nastepny = wezly.size();
            wezly[idx].dzieci[znak] = nastepny;
            wezly.emplace_back(idx, wezly[idx].poziom + 1);
        }
        dodaj_slowo(wezly[idx].dzieci[znak], slowo);
    }

    void dfs() {
        vector<int> odwiedzone(wezly.size(), 0);
        stack<int> stos; stos.push(0);
        while (!stos.empty()) {
            int v = stos.top();
            if (!odwiedzone[v]) {
                odwiedzone[v] = 1;
                for (auto &[znak, u] : wezly[v].dzieci) stos.push(u);
            } else {
                wezly[v].maks_glebokosc = 1;
                for (auto &[znak, u] : wezly[v].dzieci)
                    wezly[v].maks_glebokosc = max(wezly[v].maks_glebokosc, wezly[u].maks_glebokosc + 1);
                stos.pop();
            }
        }
    }

    void odbuduj_sciezke(int idx, string &wynik) {
        if (idx == 0) return;
        int r = wezly[idx].rodzic;
        for (auto &[znak, u] : wezly[r].dzieci) {
            if (u == idx) { odbuduj_sciezke(r, wynik); wynik += znak; break; }
        }
    }

    string generuj_wynik(int n) {
        int rozmiar = wezly.size();
        posortowane_krawedzie.assign(rozmiar, {});
        for (int i = 0; i < rozmiar; ++i) {
            for (auto &[znak, u] : wezly[i].dzieci) posortowane_krawedzie[i].emplace_back(wezly[u].maks_glebokosc, znak);
            sort(posortowane_krawedzie[i].begin(), posortowane_krawedzie[i].end());
        }

        string wynik, bufor;
        vector<int> stos_poziom = {0};
        int poz = 0, licznik_enter = 0;

        while (licznik_enter < n) {
            if (wezly[poz].licznik_odwiedzin == 0 && posortowane_krawedzie[poz].size() > 1)
                stos_poziom.push_back(poz);

            if (wezly[poz].licznik_odwiedzin == (int)posortowane_krawedzie[poz].size()) {
                wynik += 'E'; ++licznik_enter;
                int poziom = wezly[poz].poziom;

                while (!stos_poziom.empty() && wezly[stos_poziom.back()].licznik_odwiedzin == posortowane_krawedzie[stos_poziom.back()].size())
                    stos_poziom.pop_back();
                if (stos_poziom.empty()) break;

                poz = stos_poziom.back(); bufor.clear();
                odbuduj_sciezke(poz, bufor);

                if (1 + poziom - wezly[poz].poziom < wezly[poz].poziom) {
                    wynik += 'T';
                    for (int i = 0; i < poziom - wezly[poz].poziom; ++i) wynik += 'B';
                } else wynik += bufor;

            } else {
                if (wezly[poz].koniec) {
                    wynik += "ET";
                    wezly[poz].koniec = false;
                }

                char nastepny = posortowane_krawedzie[poz][wezly[poz].licznik_odwiedzin].second;
                wynik += nastepny; bufor += nastepny;
                ++wezly[poz].licznik_odwiedzin;
                poz = wezly[poz].dzieci[nastepny];
            }
        }
        return wynik;
    }
};

int main() {
    szybki_ios;
    int n; cin >> n;
    DrzewoTrie drzewo;
    for (int i = 0; i < n; ++i) {
        string w; cin >> w;
        reverse(w.begin(), w.end());
        drzewo.dodaj_slowo(0, w);
    }

    drzewo.dfs();
    
    string wynik = drzewo.generuj_wynik(n);
    cout << wynik.size() << "\n";
    cout << wynik;
}
