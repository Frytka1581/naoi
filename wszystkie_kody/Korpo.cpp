#include <bits/stdc++.h>
//#include "korlib.h"
using namespace std;

vector<pair<vector<int>, vector<int>>> precomp;
vector<int> srodki;

int Pytaj(int X, int Y)
{
    return X+Y;
}

void podziel(vector<int> ciag, int index,int o)
{
    int mid = (ciag.size() + 1) / 2;
    vector<int> lewy, prawy, l1, p1;
    if(ciag.size()>=1){
        // for(int i=0;i<ciag.size();++i){
        //     cout << ciag[i] << ' ';
        // }
        // cout << endl;
        lewy.push_back(ciag[mid-1]);
        if(ciag.size()>=2) prawy.push_back(ciag[mid]);
    }
    if (ciag.size() < 2)
    {
        return;
    }

    
    if (mid >= 2)
    {
        int wynik = Pytaj(ciag[mid - 2], ciag[mid - 1]);
        lewy.push_back(wynik);
        l1.push_back(ciag[mid - 1]);
        l1.push_back(ciag[mid - 2]);
        
        for (int i = mid - 3; i >= 0; --i)
        {
            wynik = Pytaj(ciag[i], wynik);
            lewy.push_back(wynik);
            l1.push_back(ciag[i]);
        }
        reverse(l1.begin(), l1.end());
    }

    if (ciag.size() - mid >= 1)
    {
        int wynik = ciag[mid];
        p1.push_back(ciag[mid]);
        for (int i = mid + 1; i < ciag.size(); ++i)
        {
            wynik = Pytaj(wynik, ciag[i]);
            prawy.push_back(wynik);
            p1.push_back(ciag[i]);
        }
    }

    precomp[index] = {lewy, prawy};
    srodki[index] = mid+o;

    if (l1.size() >= 1)
    {
        podziel(l1, index * 2,o);
    }
    if (p1.size() >= 1)
    {
        podziel(p1, index * 2 + 1,o+mid);
    }
}

void Zacznij(int N, vector<int> A)
{
    int k = 1;
    while (k < N)
        k *= 2;
    precomp.resize(2 * k);
    srodki.resize(2 * k);
    podziel(A, 1,0);
}
int Znajdz(int index,int l,int r){
    if(srodki[index]<=r && srodki[index]>=l) return index;
    if(srodki[index]>=r) return Znajdz(index*2,l,r);
    if(srodki[index]<=l) return Znajdz(index*2+1,l,r);
}
int Odpowiedz(int L, int R)
{
    int index = Znajdz(1,L,R);
    pair<vector<int>, vector<int>>koniec=precomp[index];
    int nl=srodki[index]-L+1;
    int np=R-srodki[index];
    // cout << "LEWY: ";
    // for(int i=0;i<koniec.first.size();++i){
    //     cout << koniec.first[i] << ' ';
    // }
    // cout <<"PRAWY: ";
    // for(int i=0;i<koniec.second.size();++i){
    //     cout << koniec.second[i] << ' ';
    // }
    // cout << endl;
    if(nl>0 && np>0){
        return Pytaj(koniec.first[nl-1],koniec.second[np-1]);
    }
    if(nl>0) return koniec.first[nl-1];
    if(np>0) return koniec.second[np-1];
    
    return 0;
}

int main()
{
    int n, q, x, y;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    cin >> q;
    Zacznij(n, a);
    for (int i = 0; i < q; ++i)
    {
        cin >> x >> y;
        cout << Odpowiedz(x, y) << endl;
    }

    // for (int i = 1; i < precomp.size(); ++i)
    // {
    //     cout << "Index " << i << ": ";
    //     cout << "Lewy: ";
    //     for (int j : precomp[i].first)
    //     {
    //         cout << j << ' ';
    //     }
    //     cout << "| Prawy: ";
    //     for (int j : precomp[i].second)
    //     {
    //         cout << j << ' ';
    //     }
    //     cout << "| Srodek: " << srodki[i];
    //     cout << endl;
    // }
    return 0;
}