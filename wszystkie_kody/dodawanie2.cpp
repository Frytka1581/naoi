#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string a,b;
    
    cin >> a >> b;
    //cout <<a << '.' << b << endl;
    if(a[0]=='-' && b[0]!='-')
        swap(a,b);
    if(a[0]!='-' && b[0]=='-'){
    
    bool czy=false;
    if(b.length()-1>a.length()){
        czy=true;
    }
    else if(b.length()-1==a.length()){
        for(int i=0;i<a.length();++i){
            if(b[i+1]>a[i]){
                czy = true;
                break;
            }
            else if(a[i]>b[i+1]) break;
        }
    }
    reverse(b.begin(),b.end());

    b[b.length()-1]='0';
    while(b.length()<a.length()){
        b+='0';
    }
    
    //reverse(b.begin(),b.end());
    reverse(a.begin(),a.end());
    //cout << a << ' ' << b << endl;
    while(a.length()<b.length()-1){
        a+='_';
    }
    //reverse(a.begin(),a.end());
    //cout << a << '\n' << b << '\n' << czy;
    int index;
    //cout << a << ' ' << b << endl;
    //cout << czy;
    if(czy==false){
        //cout << 121441324;
    for(int i=0;i<a.length();++i){
        if(a[i]=='_') break;
        a[i]-=b[i]-48;
        //cout << a << endl;
        if(a[i]<'0'){
            index=i+1;
            while(index!=a.length() && a[index]<'1') index++;
            
            if(index == a.length() || a[index]=='_') break;
            a[index]--;
            index--;
            while(index!=i){
                
                a[index]='9';
                index--;
            }
            a[index]+=10;
        }
    }
    }
    else{
        for(int i=0;i<b.length();++i){
            
            if(a[i]=='_') break;
            b[i]-=a[i]-48;
            
            if(b[i]<'0'){
                index=i+1;
                while(index!=b.length() && b[index]<'1') index++;
                
                if(index == b.length() || b[index]=='_') break;
                b[index]--;
                index--;
                while(index!=i){
                    
                    b[index]='9';
                    index--;
                }
                b[index]+=10;
            }
            }
        
    }

    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    if(czy==false){
        
        index = 0;
        while(a[index]=='0') index ++;
        for(int i=index;i<a.length();++i){
            cout << a[i]; 
        }
        if(index==a.length()) cout << 0;
    }
    else{
        cout << '-';
        index = 0;
        while(b[index]<='0' || b[index]>'9') index++;
        for(int i=index;i<b.length();++i){
            cout << b[i]; 
        }
    }
    }
    else if(a[0]=='-' && b[0]=='-') {
        string c,o;
        for(int i=1;i<a.length();++i){
            c+=a[i];
        }
        o=b;
        b="";
        a="0";
        for(int i=1;i<o.length();++i){
            b+=o[i];
        }
        
        if(c.length()<b.length())
        swap(c,b);
        a+=c;
    
    int index;
    int suma=0;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    for(int i=0;i<b.length();++i){
        a[i]+=b[i]-48;
        index =i;
        while(a[index]>'9'){
            suma=(a[index]-48)/10;
            a[index+1]+=suma;
            a[index]-=suma*10;
            index++;
        }
    }
    reverse(a.begin(),a.end());
    if(a[0]!='0'){
        cout << '-' << a;
    }
    else{
        cout << '-';
        for(int i=1;i<a.length();++i)
            cout << a[i];
    }
    }
    else{
        string c,o;
        for(int i=0;i<a.length();++i){
            c+=a[i];
        }
        o=b;
        b="";
        a="0";
        for(int i=0;i<o.length();++i){
            b+=o[i];
        }
        
        if(c.length()<b.length())
        swap(c,b);
        a+=c;
    
    int index;
    int suma=0;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    for(int i=0;i<b.length();++i){
        a[i]+=b[i]-48;
        index =i;
        while(a[index]>'9'){
            suma=(a[index]-48)/10;
            a[index+1]+=suma;
            a[index]-=suma*10;
            index++;
        }
    }
    reverse(a.begin(),a.end());
    if(a[0]!='0'){
        cout << a;
    }
    else{
        //cout << '-';
        for(int i=1;i<a.length();++i)
            cout << a[i];
    }
    }
    return 0;
} 