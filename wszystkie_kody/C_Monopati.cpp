#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define s(x) x.size()
#define rsort(x) sort(x.rbegin(),x.rend())
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n;
    cin >> n;
    vector<int> A(n + 1), B(n + 1);
    for (int i = 1; i <= n; ++i) cin >> A[i];
    for (int i = 1; i <= n; ++i) cin >> B[i];
    vector<int> pmaxA(n + 1), pminA(n + 1);
    vector<int> smaxB(n + 1), sminB(n + 1);
    pmaxA[1] = A[1];
    pminA[1] = A[1];
    for (int k = 2; k <= n; ++k) {
        pmaxA[k] = max(pmaxA[k - 1], A[k]);
        pminA[k] = min(pminA[k - 1], A[k]);
    }
    smaxB[n] = B[n];
    sminB[n] = B[n];
    for (int k = n - 1; k >= 1; --k) {
        smaxB[k] = max(smaxB[k + 1], B[k]);
        sminB[k] = min(sminB[k + 1], B[k]);
    }
    vector<pii> ivs;
    for (int k = 1; k <= n; ++k) {
        int M = min(pminA[k], sminB[k]);
        int m = max(pmaxA[k], smaxB[k]);
        ivs.emplace_back(M, m);
    }
    sort(ivs.begin(), ivs.end(), [](const pii& a, const pii& b) {
        return a.second < b.second;
    });
    int N = 2 * n;
    ll ans = 0;
    int ptr = 0;
    int cur_maxL = 0;
    int mm = ivs.size();
    for (int r = 1; r <= N; ++r) {
        while (ptr < mm && ivs[ptr].second <= r) {
            cur_maxL = max(cur_maxL, ivs[ptr].first);
            ++ptr;
        }
        int good = min(r, cur_maxL);
        ans += good;
    }
    cout << ans << '\n';
}

int main() {
    fastio;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}