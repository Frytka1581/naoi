#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define s(x) x.size()
#define sort(x) sort(x.begin(),x.end())
#define rsort(x) sort(x.rbegin(),x.rend())
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;

int get_log(int len) {
    return 31 - __builtin_clz(len);
}

void solve() {
    int n;
    cin >> n;
    vector<int> P(n + 1);
    for (int i = 1; i <= n; i++) cin >> P[i];
    string xs;
    cin >> xs;
    string X(n + 1, ' ');
    for (int i = 1; i <= n; i++) X[i] = xs[i - 1];
    if (X[1] == '1' || X[n] == '1') {
        cout << -1 << '\n';
        return;
    }
    int pos_one = 0, pos_N = 0;
    for (int i = 1; i <= n; i++) {
        if (P[i] == 1) pos_one = i;
        if (P[i] == n) pos_N = i;
    }
    if ((2 <= pos_one && pos_one <= n - 1 && X[pos_one] == '1') ||
        (2 <= pos_N && pos_N <= n - 1 && X[pos_N] == '1')) {
        cout << -1 << '\n';
        return;
    }
    vector<int> req;
    for (int i = 2; i <= n - 1; i++) {
        if (X[i] == '1') req.pb(i);
    }
    int m = s(req);
    if (m == 0) {
        cout << 0 << '\n';
        return;
    }
    vector<int> val(m);
    for (int i = 0; i < m; i++) val[i] = P[req[i]];
    const int LOG = 18;
    vector<vector<int>> spmin(LOG, vector<int>(m));
    vector<vector<int>> spmax(LOG, vector<int>(m));
    for (int i = 0; i < m; i++) {
        spmin[0][i] = val[i];
        spmax[0][i] = val[i];
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i + (1 << j) <= m; i++) {
            spmin[j][i] = min(spmin[j - 1][i], spmin[j - 1][i + (1 << (j - 1))]);
            spmax[j][i] = max(spmax[j - 1][i], spmax[j - 1][i + (1 << (j - 1))]);
        }
    }
    auto get_min = [&](int L, int R) -> int {
        int len = R - L + 1;
        int k = get_log(len);
        return min(spmin[k][L], spmin[k][R - (1 << k) + 1]);
    };
    auto get_max = [&](int L, int R) -> int {
        int len = R - L + 1;
        int k = get_log(len);
        return max(spmax[k][L], spmax[k][R - (1 << k) + 1]);
    };
    vector<int> pre_min(n + 1, INF);
    vector<int> pre_max(n + 1, -INF);
    vector<int> pre_min_pos(n + 1, 0);
    vector<int> pre_max_pos(n + 1, 0);
    pre_min[1] = P[1];
    pre_max[1] = P[1];
    pre_min_pos[1] = 1;
    pre_max_pos[1] = 1;
    for (int i = 2; i <= n; i++) {
        pre_min[i] = min(pre_min[i - 1], P[i]);
        pre_max[i] = max(pre_max[i - 1], P[i]);
        pre_min_pos[i] = (P[i] < pre_min[i - 1] ? i : pre_min_pos[i - 1]);
        pre_max_pos[i] = (P[i] > pre_max[i - 1] ? i : pre_max_pos[i - 1]);
    }
    vector<int> suf_min(n + 2, INF);
    vector<int> suf_max(n + 2, -INF);
    vector<int> suf_min_pos(n + 2, 0);
    vector<int> suf_max_pos(n + 2, 0);
    suf_min[n] = P[n];
    suf_max[n] = P[n];
    suf_min_pos[n] = n;
    suf_max_pos[n] = n;
    for (int i = n - 1; i >= 1; i--) {
        suf_min[i] = min(suf_min[i + 1], P[i]);
        suf_max[i] = max(suf_max[i + 1], P[i]);
        suf_min_pos[i] = (P[i] < suf_min[i + 1] ? i : suf_min_pos[i + 1]);
        suf_max_pos[i] = (P[i] > suf_max[i + 1] ? i : suf_max_pos[i + 1]);
    }
    vector<pii> operations;
    int cur = 0;
    while (cur < m) {
        int lo = cur, hi = m - 1;
        int best = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int ming = get_min(cur, mid);
            int maxg = get_max(cur, mid);
            int first_pos = req[cur];
            int last_pos = req[mid];
            int l_end = first_pos - 1;
            int r_start = last_pos + 1;
            int m_l = pre_min[l_end];
            int M_l = pre_max[l_end];
            int m_r = (r_start <= n ? suf_min[r_start] : INF);
            int M_r = (r_start <= n ? suf_max[r_start] : -INF);
            bool c1 = (m_l < ming && M_r > maxg);
            bool c2 = (M_l > maxg && m_r < ming);
            if (c1 || c2) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (best == -1) {
            cout << -1 << '\n';
            return;
        }
        int ming_ = get_min(cur, best);
        int maxg_ = get_max(cur, best);
        int f_pos = req[cur];
        int la_pos = req[best];
        int le = f_pos - 1;
        int rs = la_pos + 1;
        int ml_ = pre_min[le];
        int Ml_ = pre_max[le];
        int mr_ = (rs <= n ? suf_min[rs] : INF);
        int Mr_ = (rs <= n ? suf_max[rs] : -INF);
        int ch_l, ch_r;
        if (ml_ < ming_ && Mr_ > maxg_) {
            ch_l = pre_min_pos[le];
            ch_r = suf_max_pos[rs];
        } else {
            ch_l = pre_max_pos[le];
            ch_r = suf_min_pos[rs];
        }
        operations.emplace_back(ch_l, ch_r);
        cur = best + 1;
    }
    if (s(operations) > 5) {
        cout << -1 << '\n';
    } else {
        cout << s(operations) << '\n';
        for (auto [l, r] : operations) {
            cout << l << ' ' << r << '\n';
        }
    }
}

int main() {
    fastio;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}