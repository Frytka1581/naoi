#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll s[100000];
ll ize[100000];

ll find(ll v)
{
    if(s[v] == v){
        return v;
    }
    s[v] = find(s[v]);
    return s[v];
}
void my_union(ll a,ll b)
{
    a = find(a);
    b = find(b);

    if(a ==b) return;

    if(ize[a] < ize[b])
    {
        swap(a,b);
    }
    s[b] = a;
    ize[a] += ize[b];
}
ll main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    

    return 0;
}