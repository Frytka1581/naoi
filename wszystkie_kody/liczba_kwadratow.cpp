#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

static int ciag[1002][1002];

inline int readInt()
{
    int x = 0, c = getchar_unlocked(), neg = 0;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            neg = 1;
        c = getchar_unlocked();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar_unlocked();
    }
    return neg ? -x : x;
}

int main()
{
    int n = readInt();
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int k = readInt();
            ciag[i][j] = ciag[i][j - 1] + ciag[i - 1][j] - ciag[i - 1][j - 1] + k;
        }
    }

    long long maks = 0,po=0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {

            for (int o = 0; o < min(i, j); ++o)
            {
                int sum = ciag[i][j] - ciag[i][j - o - 1] - ciag[i - o - 1][j] + ciag[i - o - 1][j - o - 1];
                if (sum == 0)
                {
                    po++;
                    //cout << maks << ' ' << i << ' ' << j << endl;
                }
                else
                {
                    break;
               ; }
            }
            maks+=po;
            po = 0;
            
        }
    }
    printf("%d\n", maks);
    return 0;
}
