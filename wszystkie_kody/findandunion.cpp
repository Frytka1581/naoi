#include <bits/stdc++.h>
using namespace std;

vector<long long> ciag;
vector<pair<long long, long long > > iq(1000001, make_pair(INT64_MAX, INT64_MIN));
vector<long long> masa(1000001);

long long find(long long a) {
    if (a == ciag[a]) return a;
    return ciag[a] = find(ciag[a]);
}

void onion(long long a, long long b) {
    long long x = find(a);
    long long y = find(b);
    if (x != y) {
        ciag[y] = x;
        iq[x] = make_pair(min(iq[x].first, iq[y].first), max(iq[x].second, iq[y].second));
        masa[x] += masa[y];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, p, o;
    cin >> n;
    for (int i = 0; i <= 1000000; ++i) {
        ciag.push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        cin >> p >> o;
        iq[i + 1] = make_pair(min(iq[i + 1].first, o), max(iq[i + 1].second, o));
        masa[i + 1] = max(masa[i + 1], p);
    }
    string znak;
    while (cin >> znak) {
        if (znak == "JOIN") {
            cin >> p >> o;
            onion(p, o);
        } else if (znak == "IQ_MIN") {
            cin >> p;
            cout << iq[find(p)].first << endl;
        } else if (znak == "IQ_MAX") {
            cin >> p;
            cout << iq[find(p)].second << endl;
        } else {
            cin >> p;
            cout << masa[find(p)] << endl;
        }
    }
    return 0;
}
