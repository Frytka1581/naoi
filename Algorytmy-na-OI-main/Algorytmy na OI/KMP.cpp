#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define lld long double
using namespace std;
string wzorzec, slowo, s;
vector<int> kmp() {
    int n = s.size();
    vector<int> vec(s.size(), 0);
    vec[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = vec[i - 1];
        while (j > 0 and s[i] != s[j]) {
            j = vec[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        vec[i] = j;
    }
    return vec;
}
int main() {
    int n, m;
    cin >> n >> m;
    cin >> wzorzec >> slowo;
    s = wzorzec + '#' + slowo;
    vector<int> v = kmp();
}
