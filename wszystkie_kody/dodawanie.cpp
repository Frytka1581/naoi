#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
string dodaj(string c, string b){
    string a = "0";

    //cin >> c >> b;
    if (c.length() < b.length())
        swap(c, b);
    a += c;

    int index;
    int suma = 0;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < b.length(); ++i)
    {
        a[i] += b[i] - 48;
        index = i;
        while (a[index] > '9')
        {
            suma = (a[index] - 48) / 10;
            a[index + 1] += suma;
            a[index] -= suma * 10;
            index++;
        }
    }
    reverse(a.begin(), a.end());
    if (a[0] != '0')
        return a;
    else{
        string o="";
        for (int i = 1; i < a.length(); ++i)
            o+=a[i];
        return o;
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    string x="1",y="1",z="1";
    for(int i=0;i<n-2;++i){
        z=x;
        x=dodaj(x,y);
        y=z;
    }
    cout << x;
    return 0;
}