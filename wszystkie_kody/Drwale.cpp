#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, maks = 0;
    cin >> n;
    vector<int> ciag(n);
    vector<int> sumy(5e6 + 1);
    int suma = 0, suma2 = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> ciag[i];
        suma2 += ciag[i];
        suma += ciag[i];
        maks = max(maks, ciag[i]);
        sumy[ciag[i]]++;
    }
    // for(int i=0;i<10;++i){
    //     cout << sumy[i] << ' ';
    // }
    // cout << endl;
    suma -= maks;
    suma2-=maks;
    sumy[maks]--;
    for (int i = 0; i < sumy.size(); ++i)
    {
        int dodaj;
        if (sumy[i] >= 3)
        {
            dodaj = (sumy[i] - 1) / 2;
            sumy[i] -= dodaj * 2;
            sumy[i * 2] += dodaj;
        }
    }
    // for(int i=0;i<10;++i){
    //     cout << sumy[i] << ' ';
    // }
    const int N = 5000000 + 1;
    //const int K = 10 + 1;
    bitset<N> maska;
    maska[0] = 1;
    for (int i = 0; i < sumy.size(); ++i)
    {
        while (sumy[i] > 0)
        {
            bitset<N> maskaor = (maska << i);
            maska = (maska | maskaor);
            sumy[i]--;
        }
    }
    suma++;
    suma /= 2;
    // cout << maska << endl;
    // cout << suma << endl;
    while (maska[suma] != 1){
        suma++;
    }
       
    cout << suma2 - suma + maks;
    return 0;
}