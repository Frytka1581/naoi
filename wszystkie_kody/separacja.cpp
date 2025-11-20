#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
long long n, k;
vector<long long> ciag(100007);
bool dasie(long long suma)
{
    long long ilosc = 0, suma_liczb = 0;
    for (long long i = 0; i < n; ++i)
    {
        if (ciag[i] > suma)
            return 0;
        if (suma_liczb + ciag[i] > suma)
        {
            ilosc++;
            suma_liczb = 0;
        }
        suma_liczb += ciag[i];
    }
    if (suma_liczb > 0)
        ilosc++;
    if (ilosc > k) return 0;
    return 1;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long suma = 0;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        cin >> ciag[i];
        suma += ciag[i];
    }
    long long l = 1, p = suma + 1, sr;
    while (l < p)
    {
        sr = (l + p) / 2;
        if (dasie(sr))
            p = sr;
        else
            l = sr+1;
        //cout << l << ' ' << p << ' ' << sr << endl;
    }
    
    /*for(int i=1;i<=p;++i){
        cout << dasie(i) << ' ';
    }
    */

    
    cout << p << "\n";
    return 0;
}