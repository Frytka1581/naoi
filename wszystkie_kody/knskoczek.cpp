#include <bits/stdc++.h>
using namespace std;

long long dziel[1000007];
vector<long long> primes;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long m, a;
    cin >> m;
    cout,dziel[2]<<" ";
    for (int i = 2; i < 1000007; i++)
    {
        if (dziel[i] == 0)
        {
            dziel[i] == i;
            primes.push_back(i);
        }
        for (int j = 0; primes[j] < dziel[i]; j++)
        {
            dziel[i * primes[j]] = primes[j];
        }
        dziel[i * dziel[i]] = dziel[i];
    }
cout<<dziel[2];
return 0;
    for (int i = 0; i < m; ++i)
    {
        cin >> a;
        while (a != 1)
        {
            cout << dziel[a] << " ";
            a /= dziel[a];
        }
        cout << "\n";
    }

    return 0;
}
