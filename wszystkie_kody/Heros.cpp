#include <bits/stdc++.h>
using namespace std;

vector<int> sortowanie_topologiczne(const vector<vector<int>>& ciag, const vector<int>& usuniete) {
    int n = ciag.size() - 1;
    vector<bool> is_removed(n + 1, false);
    for (int u : usuniete) {
        is_removed[u] = true;
    }
    vector<int> stopnie(n + 1, 0);
    queue<int> zerowe;
    for (int i = 1; i <= n; ++i) {
        if (is_removed[i]) continue;
        for (int j : ciag[i]) {
            if (!is_removed[j]) {
                stopnie[j]++;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!is_removed[i] && stopnie[i] == 0) {
            zerowe.push(i);
        }
    }
    vector<int> posortowane;
    while (!zerowe.empty()) {
        int front = zerowe.front();
        zerowe.pop();
        posortowane.push_back(front);
        for (int neigh : ciag[front]) {
            if (!is_removed[neigh]) {
                stopnie[neigh]--;
                if (stopnie[neigh] == 0) {
                    zerowe.push(neigh);
                }
            }
        }
    }
    return posortowane;
}

vector<int> najdluzsza_sciezka(const vector<vector<int>>& ciag, const vector<int>& usuniete) {
    int n = ciag.size() - 1;
    vector<bool> is_removed(n + 1, false);
    for (int u : usuniete) {
        is_removed[u] = true;
    }
    vector<pair<int, int>> sumy(n + 1, {0, 0});
    for (int i = 1; i <= n; ++i) {
        if (!is_removed[i]) {
            sumy[i] = {1, 0};
        }
    }
    vector<int> posortowane = sortowanie_topologiczne(ciag, usuniete);
    for (int idx : posortowane) {
        if (is_removed[idx]) continue;
        for (int to : ciag[idx]) {
            if (!is_removed[to] && sumy[to].first < sumy[idx].first + 1) {
                sumy[to].first = sumy[idx].first + 1;
                sumy[to].second = idx;
            }
        }
    }
    pair<int, int> maks = {0, 0};
    int index = 0;
    for (int i = 1; i <= n; ++i) {
        if (sumy[i].first > maks.first) {
            maks.first = sumy[i].first;
            index = i;
        }
    }
    vector<int> zwroc;
    zwroc.push_back(maks.first);
    int current = index;
    while (current != 0) {
        zwroc.push_back(current);
        current = sumy[current].second;
    }
    return zwroc;
}

vector<int> bez(const vector<int>& bez_tych, const vector<vector<int>>& ciag) {
    return najdluzsza_sciezka(ciag, bez_tych);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> ciag(n + 1);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        ciag[l].push_back(r);
    }
    set<vector<int>> seen;
    vector<pair<vector<int>, vector<int>>> poziom;
    vector<int> empty_removed;
    vector<int> initial_path = najdluzsza_sciezka(ciag, empty_removed);
    poziom.push_back({initial_path, empty_removed});
    int minn = initial_path[0];
    for (int iteracja = 0; iteracja < k; ++iteracja) {
        vector<pair<vector<int>, vector<int>>> nowy_poziom;
        for (auto& p : poziom) {
            for (size_t j = 1; j < p.first.size(); ++j) {
                vector<int> bezz = p.second;
                bezz.push_back(p.first[j]);
                vector<int> sorted_bezz = bezz;
                sort(sorted_bezz.begin(), sorted_bezz.end());
                if (seen.count(sorted_bezz)) continue;
                seen.insert(move(sorted_bezz));
                vector<int> dodaj = bez(bezz, ciag);
                minn = min(minn, dodaj[0]);
                nowy_poziom.push_back({dodaj, bezz});
            }
        }
        poziom = move(nowy_poziom);
        if (minn == 0) break;
    }
    cout << minn;
    return 0;
}