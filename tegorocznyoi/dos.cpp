#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> plansza;
vector<vector<long long>> w_drzewie;
vector<long long> kolejne_drzewo;
vector<vector<long long>> odleglosci;
vector<tuple<long long, long long, pair<long long, long long>>> ciag;
vector<long long> drzewo_przedzialowe;
vector<long long> opoznienia;
long long n, q, k, m;
long long NEG = - (1LL << 60);

void bfs() {
    queue<pair<long long, long long>> que;
    que.push({0, 0});
    odleglosci[0][0] = 0;
    while (!que.empty()) {
        auto [i, j] = que.front();
        que.pop();
        long long s = odleglosci[i][j] + 1;
        vector<pair<long long, long long>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto [di, dj] : dirs) {
            long long ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < n && nj >= 0 && nj < n && plansza[ni][nj] != '#' && odleglosci[ni][nj] == 1000000000) {
                odleglosci[ni][nj] = s;
                que.push({ni, nj});
            }
        }
    }
}

void zmien(long long index) {
    long long delta = (kolejne_drzewo[index] == 0) ? 1 : -1;
    while (index > 0) {
        kolejne_drzewo[index] += delta;
        index /= 2;
    }
}

long long zwroc(long long l, long long r, long long lq, long long rq, long long index) {
    if (lq <= l && r <= rq) {
        return kolejne_drzewo[index];
    } else if (r < lq || rq < l) {
        return 0;
    } else {
        long long sr = (l + r + 1) / 2;
        return zwroc(l, sr - 1, lq, rq, index * 2) + zwroc(sr, r, lq, rq, index * 2 + 1);
    }
}

void przesun_opoznienia(long long index, long long l, long long r) {
    if (opoznienia[index] != 0) {
        drzewo_przedzialowe[index] += opoznienia[index];
        if (l != r) {
            opoznienia[index * 2] += opoznienia[index];
            opoznienia[index * 2 + 1] += opoznienia[index];
        }
        opoznienia[index] = 0;
    }
}

void aktualizuj_przedzial(long long l, long long r, long long lq, long long rq, long long val, long long index) {
    przesun_opoznienia(index, l, r);
    if (r < lq || l > rq) return;
    if (lq <= l && r <= rq) {
        opoznienia[index] += val;
        przesun_opoznienia(index, l, r);
        return;
    }
    long long sr = (l + r + 1) / 2;
    aktualizuj_przedzial(l, sr - 1, lq, rq, val, index * 2);
    aktualizuj_przedzial(sr, r, lq, rq, val, index * 2 + 1);
    drzewo_przedzialowe[index] = max(drzewo_przedzialowe[index * 2] + opoznienia[index * 2], drzewo_przedzialowe[index * 2 + 1] + opoznienia[index * 2 + 1]);
}

void ustaw_punkt(long long ql, long long nowa_wartosc) {
    long long add = 0;
    long long index = 1;
    long long L = 1;
    long long R = k;
    while (L != R) {
        add += opoznienia[index];
        long long sr = (L + R + 1) / 2;
        if (ql < sr) {
            index = 2 * index;
            R = sr - 1;
        } else {
            index = 2 * index + 1;
            L = sr;
        }
    }
    add += opoznienia[index];
    drzewo_przedzialowe[index] = nowa_wartosc - add;
    index /= 2;
    while (index >= 1) {
        drzewo_przedzialowe[index] = max(drzewo_przedzialowe[index * 2] + opoznienia[index * 2], drzewo_przedzialowe[index * 2 + 1] + opoznienia[index * 2 + 1]);
        index /= 2;
    }
}

long long maksimum_przedzialu(long long l, long long r, long long lq, long long rq, long long index) {
    przesun_opoznienia(index, l, r);
    if (r < lq || l > rq) return NEG;
    if (lq <= l && r <= rq) return drzewo_przedzialowe[index];
    long long sr = (l + r + 1) / 2;
    long long left = maksimum_przedzialu(l, sr - 1, lq, rq, index * 2);
    long long right = maksimum_przedzialu(sr, r, lq, rq, index * 2 + 1);
    return max(left, right);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    char znak;
    cin >> n >> q;
    plansza.resize(n);
    odleglosci.resize(n, vector<long long>(n, 1000000000));
    w_drzewie.resize(n, vector<long long>(n, 1000000000));
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            cin >> znak;
            plansza[i].push_back(znak);
        }
    }
    bfs();
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            if (odleglosci[i][j] != 1000000000 && plansza[i][j] != 'Z') {
                long long isf = (plansza[i][j] == 'F') ? 1 : 0;
                ciag.push_back({odleglosci[i][j], isf, {i, j}});
            }
        }
    }
    sort(ciag.rbegin(), ciag.rend());
    m = ciag.size();
    k = 1;
    while (k < m) k <<= 1;
    drzewo_przedzialowe.resize(2 * k, 0);
    opoznienia.resize(2 * k, 0);
    kolejne_drzewo.resize(2 * k, 0);
    long long dodanie = 0;
    for (long long i = 0; i < m; ++i) {
        auto [dd, isf, pos] = ciag[i];
        w_drzewie[pos.first][pos.second] = i;
        long long ql = i + 1;
        if (isf == 1) {
            ustaw_punkt(ql, dd + dodanie);
            dodanie++;
            zmien(k + i);
        } else {
            ustaw_punkt(ql, NEG);
        }
    }
    long long essa = maksimum_przedzialu(1, k, 1, m, 1);
    if(essa<0)cout << 0 << endl;
    else cout << essa << endl;
    long long l,r;
    for (long long i = 0; i < q; ++i) {
        cin >> l >> r;
        l--;
        r--;
        long long wd = w_drzewie[l][r];
        long long leaf = k + wd;
        long long ql = wd + 1;
        if (plansza[l][r] == 'F') {
            zmien(leaf);
            ustaw_punkt(ql, NEG);
            if (wd + 2 <= m) {
                aktualizuj_przedzial(1, k, wd + 2, m, -1, 1);
            }
            plansza[l][r] = '.';
        } else if (plansza[l][r] == '.') {
            long long s = zwroc(1, k, 1, wd, 1);
            zmien(leaf);
            ustaw_punkt(ql, s + odleglosci[l][r]);
            if (wd + 2 <= m) {
                aktualizuj_przedzial(1, k, wd + 2, m, 1, 1);
            }
            plansza[l][r] = 'F';
        }
        long long wynik = maksimum_przedzialu(1, k, 1, m, 1);
        if(wynik<0) cout << 0 << endl;
        else cout << wynik << endl;
    }
    return 0;
}