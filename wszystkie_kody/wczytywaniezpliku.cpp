#include <bits/stdc++.h>
#include <fstream>
using namespace std;
vector<int> sito(int n){
    vector<int>ktore(n+2,1);
    for(int i=2; i<n+2; ++i){
         if(ktore[i] == 1){
             for(int j = i * 2; j < n + 2; j += i)
            	if(ktore[j]==1) ktore[j] = i;
    }
}
return ktore;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin;
    ofstream outputFile("wynik3.txt");
    int e=0,r=0,f=0;
    cin.open("liczby.txt");
    int a,b;
    //outputFile << "Zadanie 3.2." << ' ';
    int suma=0;
    int cos=0;
    vector<int>ciag2;
    vector<int>ciag3;
    const vector<int>ktore=sito(2000000);
    while(cin >> a ){
        int sigma=sqrt(a);
        set<int>gyat;
        if(sigma*sigma==a) {
            suma++;
            if(cos==0) 
                cos=a;
        }
        int k=a;
        while(ktore[k]!=1){
			gyat.insert(ktore[k]);
			k/=ktore[k];
		}
		if(k!=1) gyat.insert(ktore[k]);
		if(gyat.size()>=5)
            ciag3.push_back(a);


        vector<int>ciag;
        int t=a,u=0,p=0,mn=1;
        while(t!=0){
            ciag.push_back(t%10);
            
            t/=10;
        }
        sort(ciag.begin(),ciag.end());
        for(int i=0;i<ciag.size();++i){
            u+=ciag[i]*mn;
            mn*=10;
        }
        mn = 1;
        for(int i=ciag.size()-1;i>=0;--i){
            p+=ciag[i]*mn;
            mn*=10;
        }
        
        
        if(a>u-p) e++;
        else if(a<u-p) r++;
        else{
            f++;
            ciag2.push_back(a);
        }
        
            
    }
    outputFile  <<"Zadanie 3.1." << ' ';
    outputFile <<suma  << ' ' << cos<< endl;
    outputFile << "Zadanie 3.2. ";
    for(int i=0;i<ciag3.size();++i){
        outputFile << ciag3[i] << ' ';
    }
    outputFile << endl;
    outputFile << "Zadanie 3.3. " << e << ' ' << r << ' ' << f << ' '; 
    for(int i=0;i<ciag2.size();++i){
        cout << ciag2[i] << ' ';
    }
    return 0;
}