#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, n, k;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        cin >> n;
        int minn = 1e9;
        vector<int> ciag(n);
        for (int j = 0; j < n; ++j)
        {
            cin >> ciag[j];
        }
        sort(ciag.begin(), ciag.end());
        for (int i = 0; i < ciag.size() - 1; ++i)
        {
            minn = min(abs(ciag[i] - ciag[i + 1]), minn);
        }
        cout << minn << endl;
    }
    return 0;
}