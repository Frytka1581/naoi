#include <bits/stdc++.h>
using namespace std;
#define ll long long

mt19937 mt;

ll los(ll a, ll b)
{
    return a + (mt() % (b-a+1));
}

int main()
{
    int z;
    cin >> z;
    mt.seed(z);
    int a = los(1,10);
    int b = los(1,10);
    cout << a << " " << b << "\n";
}