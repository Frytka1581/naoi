#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int minn = 1e9;
    for (int i = 1; i <= n; ++i)
    {
        if (n % i == 0)
        {
            minn = min(minn, i * 2 + (n / i) * 2);
            //cout << i << endl;
        }
    }
    cout << minn;
    return 0;
}