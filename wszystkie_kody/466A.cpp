#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b, minn = INT32_MAX;
    cin >> n >> m >> a >> b;

    for (int i = 0; i <= n; ++i)
    {
        int i2 = ceil((float)(n - i) / m);
        minn = min(minn, i2 * b + i * a);
        //cout << i2 << endl;
    }
   
    cout << minn;
    return 0;
}