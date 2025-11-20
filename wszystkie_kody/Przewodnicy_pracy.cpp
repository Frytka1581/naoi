#include <bits/stdc++.h>
using namespace std;


vector<long long> generuj_liczby(const vector<long long>& pierwsze) {
    vector<long long> wyniki;
    const long long LIMIT = 1e18;

    function<void(int, long long)> rekurencja = [&](int indeks, long long aktualna) {
        if (aktualna > 1) {
            wyniki.push_back(aktualna);
        }

        for (int i = indeks; i < pierwsze.size(); ++i) {
            if (aktualna > LIMIT / pierwsze[i]) {
                continue;
            }
            rekurencja(i, aktualna * pierwsze[i]);
        }
    };

    rekurencja(0, 1);
    wyniki.push_back(1);
    sort(wyniki.begin(), wyniki.end());
    return wyniki;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, p;
    long long k;

    cin >> n >> p;
    vector<long long> lp(n), fc, sc;
    for (int i = 0; i < n; ++i)
    {
        cin >> lp[i];
    }
    sort(lp.begin(), lp.end());
    for (int i = 0; i < n; ++i)
    {
        if (i % 2)
            fc.push_back(lp[i]);
        else
            sc.push_back(lp[i]);
    }
    // fc.push_back(1);
    // sc.push_back(1);
    // vector<long long>wypisz=generate_numbers({2,3,5,7});
    // for(int i=0;i<wypisz.size();++i){
    //     cout << wypisz[i] << ' ';
    // }
    // cout << endl;
    // long long s = fc.size();
    // for (int i = 0; i < s; ++i)
    // {
    //     if (fc[i] <= 1) continue;
    //     k = fc[i];
    //     if (k <= 1e9 && k > 0) {
    //         k = k * k;
    //         while (k <= 1e18 && k > 0)
    //         {
    //             fc.push_back(k);
    //             if (k > 1e18 / fc[i]) break;
    //             k *= fc[i];
    //         }
    //     }
    // }
    // s = fc.size();
    // for (int i = 0; i < s; ++i)
    // {
    //     for (int j = i + 1; j < s; ++j)
    //     {
    //         if (fc[i] <= 1e18 / fc[j] && fc[i] * fc[j] > 0)
    //             fc.push_back(fc[i] * fc[j]);
    //     }
    // }
    // sort(fc.begin(), fc.end());
    // fc.erase(unique(fc.begin(), fc.end()), fc.end());
    // s = sc.size();
    // for (int i = 0; i < s; ++i)
    // {
    //     if (sc[i] <= 1) continue;
    //     k = sc[i];
    //     if (k <= 1e9 && k > 0) {
    //         k = k * k;
    //         while (k <= 1e18 && k > 0)
    //         {
    //             sc.push_back(k);
    //             if (k > 1e18 / sc[i]) break; 
    //             k *= sc[i];
    //         }
    //     }
    // }
    // s = sc.size();
    // for (int i = 0; i < s; ++i)
    // {
    //     for (int j = i + 1; j < s; ++j)
    //     {
    //         if (sc[i] <= 1e18 / sc[j] && sc[i] * sc[j] > 0)
    //             sc.push_back(sc[i] * sc[j]);
    //     }
    // }
    // sort(sc.begin(), sc.end());
    // sc.erase(unique(sc.begin(), sc.end()), sc.end());
    // for (int i = 0; i < fc.size(); ++i)
    // {
    //     if (fc[i] < 100)
    //         cout << fc[i] << ' ';
    // }
    // cout << endl;
    // for (int i = 0; i < sc.size(); ++i)
    // {
    //     if (sc[i] < 100)
    //         cout << sc[i] << ' ';
    // }
    // cout << endl;
    fc=generuj_liczby(fc);
    sc=generuj_liczby(sc);
    long long l = 0, r = 1e18, sr, li, ri, suma, maks = 0;
    while (l < r)
    {
        sr = (l + r + 1) / 2;
        li = 0;
        ri = sc.size() - 1;
        suma = 0;
        maks = 0;
        while (li < fc.size() && ri > -1)
        {
            if (fc[li] <= sr / sc[ri] && fc[li] * sc[ri] > 0) 
            {
                maks = max(maks, fc[li] * sc[ri]);
                suma += ri + 1;
                li++;
            }
            else
                ri--;
        }
        //cout << suma << " " << sr << endl;
        if (suma > p)
        {
            r = sr - 1;
        }
        else if (suma < p)
        {
            l = sr;
        }
        else
        {
            break;
        }
    }
    cout << maks;
    return 0;
}