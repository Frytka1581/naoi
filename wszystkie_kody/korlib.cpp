#include "korlib.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
vector<vector<int>> pre;
vector<vector<int>> suf;
vector<int> v;
/*int Pytaj(int a, int b) {
    return a + 2*(b/2);
}*/
void ustaw(int l, int r, vector<int>& A) {
    if (r - l < 2) return;
    int sr = (r + l) / 2;
    for (int i = sr + 1; i <= r; i++) {
        if (pre[sr + 1].size() == 0) pre[sr + 1].pb(A[i]);
        else pre[sr + 1].pb(Pytaj(pre[sr + 1].back(), A[i]));
    }
    for (int i = sr; i >= l; i--) {
        if (suf[sr].size() == 0) suf[sr].pb(A[i]);
        else suf[sr].pb(Pytaj(A[i], suf[sr].back()));
    }
    ustaw(l, sr - 1, A);
    ustaw(sr + 2, r, A);
}
int wynik(int lwyn, int rwyn, int l, int r) {
    int sr = (l + r) / 2;
    if (r < 0) return 0;
    //cout << lwyn << " " << rwyn << " " << l << " " << sr << " " << r << endl;
    if (lwyn > sr + 1) return wynik(lwyn, rwyn, sr + 2, r);
    if (sr > rwyn) return wynik(lwyn, rwyn, l, sr - 1);
    if (lwyn == sr + 1) return pre[lwyn][rwyn - lwyn];
    if (rwyn == sr) return suf[rwyn][rwyn - lwyn];
    return Pytaj(suf[sr][sr - lwyn], pre[sr + 1][rwyn - sr - 1]);
}
int Odpowiedz(int l, int r) {
    if (r - l == 1) return Pytaj(v[l], v[r]);
    if (r - l == 0) return v[l];
    int n = pre.size();
    return wynik(l, r, 0, n - 1);
}
void Zacznij(int n, vector<int> A) {
    pre.resize(n);
    suf.resize(n);
    v = A;
    ustaw(0, n - 1, A);
}

/*int main() {
    int n, r, l, z;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    Zacznij(n, A);
    cin >> z;
    cout << "pre" << endl;
    for (vector<int> v : pre) {
        for (int i : v) {
             cout << i << " ";
        }
        cout << endl;
    }
    cout << "suf" << endl;
    for (vector<int> v : suf) {
        for (int i : v) {
             cout << i << " ";
        }
        cout << endl;
    }
    cout << "odpowiedzi" << endl;
    while(z--) {
        cin >> l >> r;
        cout << Odpowiedz(l, r) << endl;
    }
}*/
