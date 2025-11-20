#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll podziel(ll k, ll dzielnik)
{
    ll podstawowy = k / dzielnik;
    ll pozostaly = k % dzielnik;
    ll wynik = 0;
    for (int i = 0; i < dzielnik - pozostaly; ++i)
    {
        wynik += podstawowy * podstawowy;
    }
    for (int i = 0; i < pozostaly; ++i)
    {
        wynik += (podstawowy + 1) * (podstawowy + 1);
    }
    return wynik;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k,sigma=0;
    cin >> n >> k;
    vector<ll> ciag(n);
    priority_queue<ll>kolejka;
    for (int i = 0; i < n; ++i)
    {
        
        cin >> ciag[i];
        sigma += ciag[i]*ciag[i];
    }
    for(int i=0;i<n;++i){
        ll poczatkowy = ciag[i]*ciag[i];
        ll dzielnik = 2;
        ll kolejny = 0;
        while(dzielnik<=ciag[i]){
            kolejny = podziel(ciag[i],dzielnik);
            poczatkowy-=kolejny;
            //kolejny = poczatkowy;
            //cout << poczatkowy << endl;
            if(k-n==0) break;
            else if(kolejka.size()==k-n && poczatkowy*-1>=kolejka.top()) break;
            else if(kolejka.size()==k-n && poczatkowy*-1<=kolejka.top()){
                kolejka.pop();
                kolejka.push(poczatkowy*-1);
            }
            else{
                kolejka.push(poczatkowy*-1);
            }
            dzielnik++;
            poczatkowy = kolejny;
        }
        //cout << "----------" << endl;
    }
    ll suma=0;
    while(!kolejka.empty()){
        suma +=kolejka.top()*-1;
        // cout << kolejka.top()*-1 << ' ';
        kolejka.pop();
    }
    cout << abs(sigma-suma);
    return 0;
}
