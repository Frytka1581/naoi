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
}

