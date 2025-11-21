#include <bits/stdc++.h>
using namespace std;

bool sa_wzglednie_pierwsze(int n, int m)
{
    return __gcd(n, m) == 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k = 1, l = 0, r = 0;
    cin >> n >> m;
    k = __gcd(n, m);

    if (n == m)
    {
        cout << n << endl;
        cout << "P";
        for (int i = 0; i < n - 1; ++i)
        {
            cout << "D";
        }
        cout << endl;
        return 0;
    }
    if (k == 1)
    {
        cout << 2 << endl
             << "DP" << endl;
        return 0;
    }

    for (int i = 1; i < k; ++i)
    {
        if (sa_wzglednie_pierwsze(n, i) && sa_wzglednie_pierwsze(k - i, m))
        {
            l = i;
            r = k - i;
            break;
        }
    }

    cout << k << endl;
    if (l != 0 && r != 0)
    {
        for (int i = 0; i < l; ++i)
        {
            cout << "D";
        }
        for (int i = 0; i < r; ++i)
        {
            cout << "P";
        }
    }
    else
    {
        if (n < m)
        {
            if (n % (k - 1) != 0)
            {
                for (int i = 0; i < k - 1; ++i)
                {
                    cout << "D";
                }
                cout << "P";
            }
            else
            {
                for (int i = 0; i < k - 1; ++i)
                {
                    cout << "P";
                }
                cout << "D";
            }
        }
        else
        {
            if (m % (k - 1) != 0)
            {
                for (int i = 0; i < k - 1; ++i)
                {
                    cout << "P";
                }
                cout << "D";
            }
            else
            {
                for (int i = 0; i < k - 1; ++i)
                {
                    cout << "D";
                }
                cout << "P";
            }
        }
    }
    cout << endl;
    return 0;
}