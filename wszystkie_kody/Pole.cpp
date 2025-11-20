#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, k, maks = 0;
    cin >> n;
    vector<long long> poprzedni(n, 0);
    stack<pair<long long, long long>> ciag;
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> k;
            if (!k)
                poprzedni[j]++;
            else
                poprzedni[j] = 0;
        }
        
        ciag = {};
        for (int j = 0; j <= n; ++j)
        {
            long long wys = (j < n) ? poprzedni[j] : 0;
            long long start = j;
            while (!ciag.empty() && ciag.top().second > wys)
            {
                auto topp = ciag.top();
                ciag.pop();
                long long pole = topp.second * (j - topp.first);
                maks = max(maks, pole);
                start = topp.first;
            }
            if (ciag.empty() || ciag.top().second < wys)
                ciag.push({start, wys});
        }
    }
    
    cout << maks << '\n';
    return 0;
}