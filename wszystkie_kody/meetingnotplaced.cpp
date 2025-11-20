#include <bits/stdc++.h>
#include <iostream>
using namespace std;
double czas = 1;
bool dasie(double n, vector<int> kordy, vector<int> szybkosc)
{
    vector<pair<double, double > > ciag;
    double l=INT_MIN,r=INT_MAX;
    for (int i = 0; i < kordy.size(); ++i)
    {
        l=max(l,kordy[i] - szybkosc[i] * n);
        r=min(r,kordy[i] + szybkosc[i] * n);
        //ciag.push_back(make_pair(kordy[i] + szybkosc[i] * n, kordy[i] - szybkosc[i] * n));
    }
    //cout << l << ' ' << r << '\n';
    if(l>r) return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> kordy(n);
    vector<int> szybkosc(n);
    double l = 0, p=0;

    for (int i = 0; i < n; ++i){
        cin >> kordy[i];
        p=max(kordy[i],(int)p);
    }
    for (int i = 0; i < n; ++i)
        cin >> szybkosc[i];

    double sr = (double)(l + p) / 2;
    int k = 0;
    setprecision(12);
    double koncowka = 0.000000000001;
    //dasie(3, kordy, szybkosc);
    while (l < p)
    {
        sr = (double)(l + p)/ 2 + koncowka;
        if (dasie(sr, kordy, szybkosc))
        {
            p = sr - koncowka;
        }
        else
            l = sr;
        k++;
        //cout << fixed << setprecision(12) << ((double)(l + p)) << ' ' << sr  << endl;
        if( ((double)(l + p)) / 2 == p) break;
    }
    cout << fixed << setprecision(12) << p<< endl;
    
    return 0;
}