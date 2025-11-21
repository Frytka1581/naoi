#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
#define lld long double
int n; // Fenwick tree jest indeksowany od 1 a nie od 0!!!
void upd(vector<ll>& tree, int index, int value) {
    while (index < m + 1) {
        tree[index] += value;
        index += index & -index;
    }
}
ll prefiks(vector<ll>& tree, int index) {
    ll sum = 0;
    while (index > 0) {
        sum += tree[index];
        index -= index & -index;
    }
    return sum;
}
ll query(vector<ll>& tree, int left, int right) {
    return prefiks(tree, right) - prefiks(tree, left - 1);
}

int main() {
    cin >> n;
    vector<ll> tree(m + 1, 0);
}
