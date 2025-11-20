#include <bits/stdc++.h>
#include "korlib.h"
using namespace std;

vector<pair<vector<int>, vector<int>>> precomp;
vector<int> srodki;
vector<int> v;

void podziel(vector<int> ciag, int index, int o) {
    int mid = (ciag.size() + 1) / 2;
    vector<int> lewy, prawy, l1, p1;
    
    if (ciag.size() < 2) {
        if (ciag.size() == 1) {
            lewy.push_back(ciag[0]);
        }
        precomp[index] = {lewy, prawy};
        srodki[index] = mid + o;
        return;
    }

    if (mid >= 1) {
        lewy.push_back(ciag[mid - 1]);
        for (int i = mid - 2; i >= 0; i--) {
            lewy.push_back(Pytaj(ciag[i], lewy.back()));
        }
        for (int i = 0; i < mid; i++) {
            l1.push_back(ciag[i]);
        }
    }

    if (ciag.size() - mid >= 1) {
        prawy.push_back(ciag[mid]);
        for (int i = mid + 1; i < ciag.size(); i++) {
            prawy.push_back(Pytaj(prawy.back(), ciag[i]));
        }
        for (int i = mid; i < ciag.size(); i++) {
            p1.push_back(ciag[i]);
        }
    }

    precomp[index] = {lewy, prawy};
    srodki[index] = mid + o;

    if (l1.size() >= 1) {
        podziel(l1, index * 2, o);
    }
    if (p1.size() >= 1) {
        podziel(p1, index * 2 + 1, o + mid);
    }
}

void Zacznij(int N, vector<int> A) {
    int k = 1;
    while (k < N) k *= 2;
    precomp.resize(2 * k);
    srodki.resize(2 * k);
    v = A;
    podziel(A, 1, 0);
}

int Znajdz(int index, int l, int r, int left, int right) {
    if (index >= precomp.size() || srodki[index] == 0) return 0;
    int sr = srodki[index] - 1;
    if (r < left || l > right) return 0;
    if (l > sr + 1) return Znajdz(index * 2 + 1, l, r, sr + 2, right);
    if (sr > r) return Znajdz(index * 2, l, r, left, sr - 1);
    return index;
}

int Odpowiedz(int L, int R) {
    if (R - L == 1) return Pytaj(v[L], v[R]);
    if (R - L == 0) return v[L];
    int n = v.size();
    int index = Znajdz(1, L, R, 0, n - 1);
    if (index == 0) return 0;
    int sr = srodki[index] - 1;
    if (L == sr + 1) return precomp[index].second[R - L];
    if (R == sr) return precomp[index].first[sr - L];
    return Pytaj(precomp[index].first[sr - L], precomp[index].second[R - sr - 1]);
}