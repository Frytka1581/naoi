#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define lld long double
using namespace std;
vector<int> wiel, grupa;
int gr(int a) {
    if (a == grupa[a]) return a;
    int g = gr(grupa[a]);
    grupa[a] = g;
    return g;
}
void uni(int a, int b) {
    a = gr(a), b = gr(b);
    if (a == b) return;
    if (wiel[b] > wiel[a]) swap(a, b);
    wiel[a] += wiel[b];
    grupa[b] = a;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q, a, b, g;
    cin >> n >> q;
    wiel.resize(n + 1);
    grupa.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        wiel[i] = 1;
        grupa[i] = i;
    }
    while (q--) {
        cin >> a >> b;
        uni(a, b);
        g = gr(1);
        cout << wiel[g] << endl;
    }
}
