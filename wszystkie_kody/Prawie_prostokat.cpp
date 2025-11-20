#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

inline int readInt() {
    int x = 0, c = getchar_unlocked();
    while (c < '0' || c > '9') c = getchar_unlocked();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar_unlocked();
    }
    return x;
}

int ciag[1001][1001];

int main() {
    int n = readInt();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            ciag[i][j] = readInt();
            ciag[i][j] += ciag[i-1][j] + ciag[i][j-1] - ciag[i-1][j-1];
        }
    }

    int maks = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int l = 0, s = 0;
            for (int r = 0; r < n; ++r) {
                s = ciag[j][r+1] - ciag[i-1][r+1] - ciag[j][l] + ciag[i-1][l];
                while (s > 1 && l <= r) {
                    l++;
                    s = ciag[j][r+1] - ciag[i-1][r+1] - ciag[j][l] + ciag[i-1][l];
                }
                maks = max(maks, (r - l + 1) * (j - i + 1));
            }
        }
    }
    printf("%d\n", maks);
    return 0;
}