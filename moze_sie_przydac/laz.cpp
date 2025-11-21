#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define s(x) x.size()
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 1e9
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;

int n, m;

void rozwiaz() {
    cin >> n >> m;
    int k = gcd(n, m);
    if (k == 1) {
        cout << "DP\n";
        return;
    }

    bool znalezione = false;
    int lewe = 0, prawe = 0;

    for (int i = 1; i < k; ++i) {
        if (gcd(n, i) == 1 && gcd(m, k - i) == 1) {
            lewe = i;
            prawe = k - i;
            znalezione = true;
            break;
        }
    }

    if (znalezione) {
        //cout << k << "\n";
        if ((n / k) % 2 == 0) {
            for (int j = 0; j < prawe; ++j) cout << 'P';
            for (int j = 0; j < lewe; ++j) cout << 'D';
        } else {
            for (int j = 0; j < lewe; ++j) cout << 'D';
            for (int j = 0; j < prawe; ++j) cout << 'P';
        }
        cout << "\n";
    } else {
        if (k < 5) {
            //cout << (k + 1) << "\n";
            if ((n / k) % 2 == 0) {
                for (int i = 0; i < k; i++) cout << 'P';
                cout << 'D';
            } else {
                for (int j = 0; j < k; ++j) cout << 'D';
                cout << 'P';
            }
            cout << "\n";
        } else {
            bool gl_r = ((n / k) % 2 != 0);
            char gl_znak, plus_m, minus_m;

            if (gl_r) {
                gl_znak = 'D';
                plus_m = 'P';
                minus_m = 'L';
            } else {
                gl_znak = 'P';
                plus_m = 'D';
                minus_m = 'G';
            }

            int tyl = 1;
            int a = k - 3;
            int ile_gl = a - 2 * tyl;
            string s = "";

            for (int j = 0; j < ile_gl; ++j) s += gl_znak;
            s += plus_m;
            s += gl_znak;
            s += minus_m;
            s += gl_znak;
            s += plus_m;

            cout << s << "\n";
        }
    }
}

int main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) rozwiaz();
    return 0;
}
