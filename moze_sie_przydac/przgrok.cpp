#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> strings(n);
    long long sum_len = 0;
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
        sum_len += strings[i].size();
    }
    // build trie
    vector<vector<int>> trie(1, vector<int>(26, 0));
    vector<int> depth(1, 0);
    vector<bool> is_end(1, false);
    vector<int> end_id(1, -1);
    vector<int> num_leaves(1, 0);
    vector<int> min_len_trie(1, INT_MAX / 2);
    int node_cnt = 1;
    for (int i = 0; i < n; i++) {
        string s = strings[i];
        int idx = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (trie[idx][c] == 0) {
                trie.push_back(vector<int>(26, 0));
                depth.push_back(depth[idx] + 1);
                is_end.push_back(false);
                end_id.push_back(-1);
                num_leaves.push_back(0);
                min_len_trie.push_back(INT_MAX / 2);
                trie[idx][c] = node_cnt++;
            }
            idx = trie[idx][c];
        }
        is_end[idx] = true;
        end_id[idx] = i;
    }
    // compute num_leaves and min_len_trie
    function<void(int)> dfs_compute = [&](int u){
        num_leaves[u] = is_end[u] ? 1 : 0;
        min_len_trie[u] = is_end[u] ? depth[u] : INT_MAX / 2;
        for (int c = 0; c < 26; c++) {
            int w = trie[u][c];
            if (w != 0) {
                dfs_compute(w);
                num_leaves[u] += num_leaves[w];
                min_len_trie[u] = min(min_len_trie[u], min_len_trie[w]);
            }
        }
    };
    dfs_compute(0);
    // compute total saving
    function<long long(int)> compute_saving = [&](int u) -> long long {
        vector<long long> child_s;
        long long internals = 0;
        if (is_end[u]) child_s.push_back(max(0LL, 2LL * depth[u] - depth[u] - 1));
        for (int c = 0; c < 26; c++) {
            int w = trie[u][c];
            if (w != 0) {
                internals += compute_saving(w);
                long long ss = max(0LL, 2LL * depth[u] - min_len_trie[w] - 1);
                child_s.push_back(ss);
            }
        }
        long long between = 0;
        if (child_s.size() >= 2) {
            long long sum_s = 0;
            long long min_ss = LLONG_MAX;
            for (long long ss : child_s) {
                sum_s += ss;
                min_ss = min(min_ss, ss);
            }
            between = sum_s - min_ss;
        }
        return internals + between;
    };
    long long total_saving = compute_saving(0);
    long long k = sum_len + n - total_saving;
    // now build order
    vector<int> order;
    function<void(int)> build_order = [&](int u) {
        vector<pair<long long, int>> groups;
        if (is_end[u]) {
            long long ss = max(0LL, 2LL * depth[u] - depth[u] - 1);
            groups.emplace_back(ss, -1);
        }
        for (int c = 0; c < 26; c++) {
            int w = trie[u][c];
            if (w != 0) {
                long long ss = max(0LL, 2LL * depth[u] - min_len_trie[w] - 1);
                groups.emplace_back(ss, c);
            }
        }
        sort(groups.rbegin(), groups.rend());
        for (auto& p : groups) {
            int c = p.second;
            if (c == -1) {
                order.push_back(end_id[u]);
            } else {
                build_order(trie[u][c]);
            }
        }
    };
    build_order(0);
    // now build res
    string res = "";
    if (!order.empty()) {
        int prev_id = order[0];
        string curr_str = strings[prev_id];
        res += curr_str + 'E';
        for (size_t ii = 1; ii < order.size(); ++ii) {
            int cur_id = order[ii];
            string next_str = strings[cur_id];
            int lv = 0;
            int min_lv = min((int)curr_str.size(), (int)next_str.size());
            while (lv < min_lv && curr_str[lv] == next_str[lv]) ++lv;
            long long modify_cost = 1LL + (curr_str.size() - lv) + (next_str.size() - lv);
            long long scratch_cost = next_str.size();
            if (modify_cost < scratch_cost) {
                res += 'T';
                for (size_t jj = 0; jj < curr_str.size() - lv; ++jj) res += 'B';
                res += next_str.substr(lv);
            } else {
                res += next_str;
            }
            res += 'E';
            curr_str = next_str;
        }
    }
    cout << res.size() << endl;
    cout << res << endl;
    return 0;
}