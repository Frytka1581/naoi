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
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == 'p') pref[i] = pref[i - 1] + 1;
        else pref[i] = pref[i - 1] - 1;
    }

    vector<int> niz(n + 1, n + 1);
    stack<int> st;

    for (int i = n; i >= 0; i--) {
        while (!st.empty() && pref[st.top()] >= pref[i]) st.pop();
        if (!st.empty()) niz[i] = st.top();
        st.push(i);
    }

    int SH = n;
    vector<vector<int> > poz(2 * n + 1);

    for (int i = 0; i <= n; i++) {
        int v = pref[i] + SH;
        poz[v].push_back(i);
    }

    vector<int> row(n + 1, n + 1);

    for (int v = 0; v <= 2 * n; v++) {
        vector<int> &p = poz[v];
        for (int k = 0; k + 1 < (int)p.size(); k++) {
            row[p[k]] = p[k + 1];
        }
    }

    vector<int> kon(n + 1);
    kon[n] = n;

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'j') {
            kon[i] = i;
        } else {
            if (row[i] == n + 1) {
                kon[i] = kon[i + 1];
            } else {
                int a = kon[i + 1];
                int b = kon[row[i]];

                if (pref[a] > pref[b]) kon[i] = a;
                else if (pref[a] < pref[b]) kon[i] = b;
                else {
                    if (a > b) kon[i] = a;
                    else kon[i] = b;
                }
            }
        }
    }

    int wyn = 0;
    for (int i = 0; i < n; i++) {
        int dl = kon[i] - i;
        if (dl > wyn) wyn = dl;
    }

    cout << wyn << "\n";
}


int main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}