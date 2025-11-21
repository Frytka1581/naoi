#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
int wie, n;
vector<vector<int>> trie(1, vector<int>(26, -1));
vector<int> glpd, gl, wzorzec(26, -1), slowo(1, 0), ojc, ktory;
vector<vector<pair<int, int>>> graf;

void dodaj(int w, string& s) {
    if (s.size() == 0) {
        slowo[w] = 1;
        return;
    }
    int nw = s.back() - 'a';
    s.pop_back();
    if (trie[w][nw] != -1) {
        dodaj(trie[w][nw], s);
    }
    else {
        trie[w][nw] = trie.size();
        trie.pb(wzorzec);
        slowo.pb(0);
        dodaj(trie.size() - 1, s);
    }
}
void dfs(int w) {
    glpd[w] = 1;
    if (w != 0) gl[w] = gl[ojc[w]] + 1;
    for (int i : trie[w]) {
        if (i != -1) {
            ojc[i] = w;
            dfs(i);
            if (glpd[i] + 1 > glpd[w]) glpd[w] = glpd[i] + 1;
        }
    }
}
void co(int w, string& s) {
    if (w == 0) return;
    int o = ojc[w];
    for (int i = 0; i < 26; i++) {
        if (trie[o][i] == w) {
            co(o, s);
            s += i + 'a';
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // wczytywanie
    cin >> n;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        reverse(s.begin(), s.end());
        dodaj(0, s);
    }

    // precomputeing
    int wie = trie.size();
    graf.resize(wie);
    ojc.resize(wie);
    gl.resize(wie);
    ktory.resize(wie);
    glpd.resize(wie); // g³êbokoœæ poddrzewa
    ojc[0] = -1;
    gl[0] = 0;
    dfs(0);
    for (int i = 0; i < wie; i++) {
        for (int j = 0; j < 26; j++) {
            if (trie[i][j] != -1) graf[i].pb({glpd[trie[i][j]], j});
        }
        sort(graf[i].begin(), graf[i].end());
    }

    /*cout << "trie" << endl;
    for (int i = 0; i < wie; i++) {
        cout << i << " " << gl[i] << endl;
        for (int j = 0; j < 26; j++) {
            cout << char(j + 'a') << " " << trie[i][j] << endl;
        }
        cout << endl;
    }*/

    // solve
    int enters = 0, w = 0;
    vector<int> roz = {0};
    string wyn, ak;
    while (enters < n) {
        if (ktory[w] == 0 and graf[w].size() > 1) roz.pb(w);
        if (ktory[w] == graf[w].size()) {
            wyn += 'E';
            enters++;
            int g = gl[w];
            while (roz.size() > 0 and ktory[roz.back()] == graf[roz.back()].size()) roz.pop_back();
            if (roz.size() == 0) break;
            w = roz.back();
            ak = "";
            co(w, ak);
            if (1 + g - gl[w] < gl[w]) {
                wyn += 'T';
                for (int i = 0; i < g - gl[w]; i++) wyn += 'B';
            }
            else {
                wyn += ak;
            }
        }
        else {
            if (slowo[w] == 1) {
                wyn += 'E';
                wyn += 'T';
                slowo[w] = 0;
            }
            char next = graf[w][ktory[w]].se + 'a';
            wyn += next;
            ak += next;
            ktory[w]++;
            w = trie[w][next - 'a'];
        }
    }
    cout << wyn.size() << endl;
    cout << wyn << endl;
}

