#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

vector<int> maksymalizujParzyste(vector<int>& wektor) {
    int n = wektor.size();
    sort(wektor.begin(),wektor.end(),greater<int>());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (wektor[i] % 2 == 0 && wektor[j] % 2 != 0) {
                
                wektor[i]--;
                wektor[j]++;
            }
        }
    }
for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (wektor[i] % 2 == 0 && wektor[j] % 2 != 0) {
                
                wektor[i]--;
                wektor[j]++;
            }
        }
    }
    return wektor;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, n, k, s, s1, s2, s3,s4;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        cin >> n;
        vector<int> c(n);
        s1 = 0;
        s2 = 0;
        s3 = 0;
        s4=0;
        for (int i = 0; i < n; ++i)
        {
            cin >> c[i];
            if (c[i] % 2 == 0)
                s1++;
            else
                s2++;
        }
        c = maksymalizujParzyste(c);
        for(int i=0;i<n;++i){
            cout << c[i] << ' ';
        }
        cout << endl;
        bool czy = false;
        if (s1 != 0 && s2 != 0)
            czy = true;
        k = c[0];
        s = k;

        for (int i = 0; i < n - 1; ++i)
        {
            k = c[i + 1];
            if (czy != true)
                s = max(s, k);
            if (s % 2 == k % 2 && czy == true)
            {
                s += k - 1;
                if(k%2 == 1)
                    s3++;
                else 
                    s4++;
            }
            else if (s % 2 != k % 2 && czy == true)
                s += k;
        }
        cout << s + min(s3,s4)*2 << endl;
    }
    return 0;
}