#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int MAXN = 100000 * 61 + 5;
int trie[MAXN][2];
int nodes = 1;

void dodaj(long long x) {
    int v = 0;
    for (int i = 60; i >= 0; --i) {
        int bit = (x >> i) & 1;
        if (!trie[v][bit]) trie[v][bit] = nodes++;
        v = trie[v][bit];
    }
}

long long zwroc(long long x) {
    int v = 0;
    long long res = 0;
    for (int i = 60; i >= 0; --i) {
        int bit = (x >> i) & 1;
        int want = bit ^ 1;
        if (trie[v][want]) {
            res |= (1LL << i);
            v = trie[v][want];
        } else {
            v = trie[v][bit];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<i64> ap(1, 0);

    i64 maks = 0;
    dodaj(0);

    for (int i = 0; i < n; ++i) {
        long long k;
        cin >> k;
        ap.push_back(ap.back() ^ k);
        maks = max(maks, zwroc(ap.back()));
        dodaj(ap.back());
    }

    cout << maks << "\n";
    return 0;
}
