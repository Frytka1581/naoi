#include <bits/stdc++.h>
using namespace std;
string napis;
priority_queue<int>k1,k2,k3,k4;
int koszt1(int i1,int i2, char znak){
    int a=i1;
    i1++;
    if(znak == 'b'){
        while(k1.top()<i1) k1.pop();
        if(k1.empty()) return 1e8;
    }
    if(znak == 'a'){
        while(k1.top()<i1) k1.pop();
        if(k1.empty()) return 1e8;
    }
    while(i1 < i2 ){
        if(napis[i1]==znak) return abs(i1-a);
        i1++;
    }
    return 1e8;
}
int koszt2(int i1,int i2, char znak){
    int a=i2;
    i2--;
    
    while(i1 < i2 ){
        if(napis[i2]==znak) return abs(a-i2);
        i2--;
    }
    return 1e8;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> napis;
    if(count(napis.begin(),napis.end(),'a')%2==1 && count(napis.begin(),napis.end(),'b') %2==1 ) {
        cout << "-1"; return 0;
    }
    int i1=0,i2=napis.size()-1,a,b;
    char znak;
    int s=0;
    for(int i=0;i<napis.length();++i){
        if(napis[i]=='b')
            k1.push(i*-1);
            k2.push(i);
        else{
            k3.push(i*-1);
            k4.push(i);
        }
            
    }
    //w k1 najmniejsze wystapienie b
    //w k2 najwieksze wystapienie b

    while (i1<i2){
        if(napis[i1]!=napis[i2]){
            a=koszt1(i1,i2,napis[i2]);
            b=koszt2(i1,i2,napis[i1]);
            if(a<=b){
                znak=napis[i1];
                napis[i1]=napis[i2];
                napis[i1+a]=znak;
                s+=a;
            }
            else{
                znak=napis[i2];
                napis[i2]=napis[i1];
                napis[i2-b]=znak;
                s+=b;
            }
            
        }
        // cout << napis << endl;
        i1++; i2--;
    }
    cout << s << endl;
    return 0;
}