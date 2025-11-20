#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << "Zrobione" << endl;

    /*
    #include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
using ll = long long;

void solve() {
    int h, w, k;
    cin >> h >> w >> k;

    vector<vector<ll>> d(h + 2, vector<ll>(w + 2, 1LL << 60));
    vector<vector<int>> cnt(h + 2, vector<int>(w + 2, 0));

    priority_queue<tuple<ll,int,int>, vector<tuple<ll,int,int>>, greater<>> pq;

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        d[x][y] = 0;
        pq.push({0, x, y});
    }

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    while (!pq.empty()) {
        auto [dist, x, y] = pq.top(); pq.pop();
        if (dist > d[x][y]) continue;

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 1 || nx > h || ny < 1 || ny > w) continue;
            if (d[nx][ny] == (1LL << 60)) {
                cnt[nx][ny]++;
                if (cnt[nx][ny] >= 2) {
                    ll nd = dist + 1;
                    d[nx][ny] = nd;
                    pq.push({nd, nx, ny});
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            if (d[i][j] < (1LL << 60))
                ans += d[i][j];

    cout << ans << "\n";
}

int main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

*/

    return 0;
}