#include <bits/stdc++.h>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string sigma;
    string gyat;
    cin >> gyat >> n;
    getline(cin,sigma);
    getline(cin,sigma);
    for(int i=0;i<sigma.length();++i){
        char znak=sigma[i];
        
        if(islower(znak) && gyat =="szyfruj"){
            cout << (char)((znak-97+n)%26+97);
            continue;
        }
        if(isupper(znak) && gyat =="szyfruj"){
            cout << (char)((znak-65+n)%26+65);
            continue;
        }  
        if(islower(znak) && gyat =="odszyfruj"){
            cout << (char)((znak-97-n+26)%26+97);
            continue;
        }
        if(isupper(znak) && gyat =="odszyfruj"){
            cout << (char)((znak-65-n+26)%26+65);
            continue;
        } 
        cout << znak;
    }
    return 0;
}