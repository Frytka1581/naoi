#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>
#include <functional>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define st first
#define nd second
#define pb push_back
const int inf = 1e9;
const ll infl = 1e18;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> s(m);
    vector<int> pos(n + 1, -1);
    int baza = -1;

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        s[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> s[i][j];
            pos[s[i][j]] = i;
            if (s[i][j] == 1) {
                baza = i;
            }
        }
    }

    int len = 0;
    if (baza != -1) {
        for (int j = 0; j < s[baza].size(); j++) {
            if (s[baza][j] == j + 1) {
                len = len + 1;
            } else {
                break;
            }
        }
    }

    vector<pair<int, int>> ruchy;
    int cel = baza;

    if (baza != -1 && len < s[baza].size()) {
        int pusty = -1;
        for (int i = 0; i < m; i++) {
            if (s[i].empty()) {
                pusty = i;
                break;
            }
        }

        if (pusty != -1) {
            for (int i = 0; i < len; i++) {
                int klocek = i + 1;
                ruchy.push_back({baza + 1, pusty + 1});
                pos[klocek] = pusty;
            }
            cel = pusty;
        } else {
            vector<pair<int, int>> candidates;
            for (int i = 0; i < m; i++) {
                if (i != baza && !s[i].empty()) {
                    candidates.push_back({(int)s[i].size(), i});
                }
            }
            sort(candidates.begin(), candidates.end());

            bool found = false;
            int c = -1;

            for (auto& cand : candidates) {
                int najm = cand.nd;
                multiset<pair<int, int>> mad;
                for (int ii = 0; ii < m; ii++) {
                    if (ii != najm && !s[ii].empty()) {
                        mad.insert({s[ii].back(), ii});
                    }
                }
                bool ok = true;
                for (int j = 0; j < s[najm].size(); j++) {
                    int klocek = s[najm][j];
                    auto it = mad.lower_bound({klocek, -1});
                    if (it == mad.begin()) {
                        ok = false;
                        break;
                    }
                    it--;
                    int docel = it->nd;
                    mad.erase(it);
                    mad.insert({klocek, docel});
                }
                if (ok) {
                    found = true;
                    c = najm;
                    break;
                }
            }

            if (!found) {
                cout << -1 << endl;
                return 0;
            }

            multiset<pair<int, int>> mad;
            for (int ii = 0; ii < m; ii++) {
                if (ii != c && !s[ii].empty()) {
                    mad.insert({s[ii].back(), ii});
                }
            }

            for (int j = 0; j < s[c].size(); j++) {
                int klocek = s[c][j];
                auto it = mad.lower_bound({klocek, -1});
                it--;
                int docel = it->nd;
                ruchy.push_back({c + 1, docel + 1});
                pos[klocek] = docel;
                mad.erase(it);
                mad.insert({klocek, docel});
            }

            for (int i = 0; i < len; i++) {
                int klocek = i + 1;
                ruchy.push_back({baza + 1, c + 1});
                pos[klocek] = c;
            }
            cel = c;
        }
    }

    for (int k = len + 1; k <= n; k++) {
        int z = pos[k];
        ruchy.push_back({z + 1, cel + 1});
    }

    cout << ruchy.size() << endl;

    for (int i = 0; i < ruchy.size(); i++) {
        cout << ruchy[i].st << " " << ruchy[i].nd << endl;
    }
    return 0;
}