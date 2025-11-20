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

void solve() {
    int n,k;
    cin >> n >> k;
    vector<pii>ciag(n);
    for (int i = 0; i < n; i++) {
        cin >> ciag[i].first >> ciag[i].second;
    }
    sort(ciag);
    vector<vector<int>>backpack(1001,vector<int>(1001));
    for (int i = ciag[0].first; i < backpack[0].size(); i++) {
        backpack[0][i]=ciag[0].second;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            backpack[i][j]=backpack[i-1][j];
            if(j>=ciag[i].first)
                backpack[i][j] = max(backpack[i][j],backpack[i-1][j-ciag[i].first]+ciag[i].second);
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j <= k; j++) {
    //         cout << backpack[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    int maks = 0;
    for (int i = 0; i <= k; i++) {
        maks = max(maks, backpack[n-1][i]);
    }
    cout << maks;
}

int main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}