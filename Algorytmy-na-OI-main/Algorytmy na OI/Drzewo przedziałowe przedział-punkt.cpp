#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define st first
#define nd second
#define pb push_back
#define lld long double
int n, wie;

int tree_size() {
    int wynik = 1;
    while (wynik < n) wynik *= 2;
    return wynik * 2;
}
void update(vector<int>& tree, int index, int value) {
    index += wie / 2;
    tree[index] = value;
    while (index > 1) {
        index /= 2;
        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
}
int query(vector<int>& tree, int left, int right) {
    left += wie / 2;
    right += wie / 2;
    int res = 0;
    while (left <= right) {
        if (left % 2 == 1) res += tree[left++];
        if (right % 2 == 0) res += tree[right--];
        left /= 2;
        right /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
}

