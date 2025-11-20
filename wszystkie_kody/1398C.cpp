#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> dp;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, n;
    char znak;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        cin >> n;
        vector<int>p1(n),p2(n),p3(n);
        int wynik = 0;
        for (int i = 0; i < n; ++i)
        {
            cin >> znak;
            if(znak == '1') wynik++;
            p1[i] = (znak - '0');
        }
        for (int i = 0; i < n-1; ++i)
        {
            p2[i]=p1[i]+p1[i+1];
            if(p2[i]==2) wynik++;
        }
        for(int s=2;s<n;++s){
            for(int i=0;i<n-s;++i){
                p3[i] = p2[i]+p2[i+1]-p1[i+1];
                if(p3[i] == s+1) wynik++;
            }
            for(int i=0;i<n;++i){
                p1[i]=p2[i];
                p2[i]=p3[i];
            }
        }
        cout << wynik << '\n';
    }
    return 0;
}