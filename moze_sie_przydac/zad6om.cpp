#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long seed;
    cin >> seed;
    mt19937 mt(seed);
    uniform_int_distribution<> dist(1, 2);
    return 0;
}