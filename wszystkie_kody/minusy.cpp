#include <bits/stdc++.h>
using namespace std;

int main()
{
    string n;
    int k = 0, maks = 0, s=0,s2;
    vector<pair<int,int>> ciag;
    cin >> n;
    for (int i = 0; i < n.length(); ++i)
    {
        if(n[i]=='+') 
            s++;
        else{
            s2=0;
            for(int j=i;j<n.length();++j){
                if(n[j]=='-') {
                    s2++;
                    i=j;
                }
                else break;
            }
            
            if(s2%2==0)
                s+=s2/2;
            else{
                if(s>0)
                    ciag.push_back({s,1});
                ciag.push_back({s2/2,-1});
                s=0;
            }

        }
        
    }
    if(s!=0)
        ciag.push_back({s,1});
    int cos;
    for(int i=0;i<ciag.size();++i){
        //cout << ciag[i].first << ' ' << ciag[i].second << endl;
        if(ciag[i].second==1){
            cos=ciag[i].first;
            if(i>0)
                cos+=ciag[i-1].first;
            if(i<ciag.size()-1)
                cos+=ciag[i+1].first;
            maks=max(cos,maks);
            //cout << cos << endl;
        }

    }
    for(int i=0;i<ciag.size();++i){
        //cout << ciag[i].first << ' ' << ciag[i].second << endl;
        if(ciag[i].second==-1){
            maks=max(ciag[i].first,maks);
        }

    }
    cout << maks;
    return 0;
}