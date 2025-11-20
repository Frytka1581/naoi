#include <bits/stdc++.h>
using namespace std;

struct Paint {
    int time;
    int color;
    Paint() : time(0), color(0) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<Paint> rows(n);
    vector<Paint> cols(m);
    
    int timestamp = 0;
    for (int op = 0; op < k; ++op) {
        ++timestamp;
        int type;
        cin >> type;
        if (type == 1) {
            int r, a;
            cin >> r >> a;
            --r;
            rows[r].time = timestamp;
            rows[r].color = a;
        } else {
            int c, a;
            cin >> c >> a;
            --c;
            cols[c].time = timestamp;
            cols[c].color = a;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) cout << ' ';
            cout << (rows[i].time > cols[j].time ? rows[i].color : cols[j].color);
        }
        cout << '\n';
    }
    
    return 0;
}