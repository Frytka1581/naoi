#include <bits/stdc++.h>
using namespace std;
int n, k, a, b, c;

vector<int> ciag;
vector<int> dp;
vector<int> wypad;
void zmien(int index, int przedzial, int sq)
{
    while (index % sq != 0)
    {
        if (dp[index] > przedzial * sq)
            wypad[index] = 1;
        else
            wypad[index] = wypad[dp[index] - 1] + 1;
        index--;
    }
    if (dp[index] > przedzial * sq)
        wypad[index] = 1;
    else
        wypad[index] = wypad[dp[index] - 1] + 1;
}
int wypisz(int index){
        
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int sq;
    cin >> n >> k;
    dp.resize(n);
    wypad.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a;
        ciag.push_back(a);
    }
    for (int i = 0; i < n; ++i)
    {
        dp[i] = i + 1 + ciag[i];
    }
    sq = ceil(sqrt(n));
    int i1 = sq - 1, i2 = 1;
    while (i1 < n + sq)
    {
        zmien(min(i1, n - 1), i2, sq);
        i1 += sq;
        i2++;
    }
    
    for (int i = 0; i < k; ++i)
    {
        cin >> a;

        if (a == 0)
        {
            cin >> b >> c;
            dp[b - 1] = b + c;
            zmien(b - 1, ceil(b / sq), sq);
            
        }
        if (a == 1)
            cin >> b;
    }
    return 0;
}