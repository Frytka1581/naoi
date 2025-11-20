#include <bits/stdc++.h>
using namespace std;
vector<int> tree;
using ll = long long;
void dodaj(int k, int index)
{
    while (index > 0)
    {
        if (tree[index] == 0)
            tree[index] = k;
        else
            tree[index] = gcd(tree[index], k);
        index /= 2;
    }
}
int zwracanie = 0;
void zwroc(int l, int r, int lq, int rq, int index)
{
    if (rq < l || r < lq)
        return;
    else if (lq <= l && r <= rq)
    {
        if (zwracanie == 0)
            zwracanie = tree[index];
        else
            zwracanie = gcd(zwracanie, tree[index]);
    }
    else
    {
        int sr = (l + r + 1) / 2;
        zwroc(l, sr - 1, lq, rq, index * 2);
        zwroc(sr, r, lq, rq, index * 2 + 1);
    }
}
ll nww(ll a, ll b){
    return a*b/gcd(a,b);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k = 1, index = 1;
    cin >> n;
    vector<int> ciag(n);
    while (index < n)
        index *= 2;
    while (k <= n)
        k *= 2;
    tree.resize(k * 2);
    for (int i = 0; i < n; ++i)
    {
        cin >> ciag[i];
        dodaj(ciag[i], index + i);
    }
    ll sigma=1;
    for(int i=0;i<n;++i){
        zwracanie=0;
        //if(i!=0)
        if(i!=0)
            zwroc(1,index,1,i,1);
        if(i!=n-1)
            zwroc(1,index,i+2,index,1);
        sigma = nww(sigma,zwracanie);
        //cout << zwracanie << endl;
    }
    cout << sigma << endl;
    return 0;
}