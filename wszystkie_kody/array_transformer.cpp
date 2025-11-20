#include <bits/stdc++.h>
using namespace std;
int k, u;
vector<vector<int>> przedzialy;
vector<int> ciag;
int policz(int l, int r, int v)
{
    int s = 0;
    for (int i = l - 1; i < r; ++i)
    {
        if (i % k == 0 && i + przedzialy[i].size() <= r)
        {
            auto it = lower_bound(przedzialy[i / k].begin(), przedzialy[i / k].end(), v);
            s += it - przedzialy[i / k].begin();
            i += k - 1;
        }
        else
        {
            if (ciag[i] < v)
                s++;
        }
    }
    return s;
}
void zmien(int l, int r,int v,int p){
    int wynik = policz(l,r,v);
    int poprzedni = ciag[p-1];
    ciag[p-1] = (wynik*u)/(r-l+1);
    vector<int>nowa_lista;
    bool czy1=false,czy2=false;
    int ktory = (p-1)/k;
    for(int i=0;i<przedzialy[ktory].size();++i){
        if(przedzialy[ktory][i] == poprzedni && czy1 == false){
            czy1 = true;
        }
        else if((i ==przedzialy[ktory].size()-1 || (przedzialy[ktory][i]<=wynik && przedzialy[ktory][i+1] >= wynik)) && czy2 == false){
            czy2 = true;
            nowa_lista.push_back(wynik);
        }
        else{
            nowa_lista.push_back(przedzialy[ktory][i]);
        }
    }
    przedzialy[ktory] = nowa_lista;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, l, r, v, p;
    cin >> n >> m >> u;
    ciag.resize(n);
    k = ceil(sqrt(n));
    przedzialy.resize(k);
    for (int i = 0; i < n; ++i)
    {
        cin >> ciag[i];
        przedzialy[i / k].push_back(ciag[i]);
    }
    for (int i = 0; i < przedzialy.size(); ++i)
    {
        sort(przedzialy[i].begin(), przedzialy[i].end());
    }
    //cout << policz(1, 10, 10) << endl;
    for(int i=0;i<m;++i){
        cin >> l >> r >> v >> p;
        zmien(l,r,v,p);
    }
    for(int i=0;i<ciag.size();++i){
        cout << ciag[i] << endl;
    }
    // for (int i = 0; i < przedzialy.size(); ++i)
    // {
    //     for (int j = 0; j < przedzialy[i].size(); ++j)
    //     {
    //         cout << przedzialy[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    return 0;
}
// 0 1 2 3 4
// 1 2 3 4