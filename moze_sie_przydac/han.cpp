#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,k,l;
    cin >> n >> m;
    vector<int>wartosci(n+1);
    vector<vector<int>>stosy(m);
    bool czy=false; int index=0;
    vector<int>p1(1e6+5,1e6+5);
    vector<int>essa;
    for(int i=0;i<m;++i){
        cin >> l;
        if(l==0) {czy=true; index=i;}
        for(int j=0;j<l;++j){
            cin >> k;
            wartosci[k]=i;
            stosy[i].push_back(k);
        }
        if(stosy[i].size()!=0){
            p1[stosy[i][stosy[i].size()-1]]=i;
            
        }
    }
    vector<pair<int,int>>wypisz;
    for(int i=1;i<p1.size();++i){
        p1[i]=min(p1[i],p1[i-1]);
    }
    // for(int i=0;i<10;++i){
    //     cout << p1[i] << ' ';
    // }
    // cout << endl;
    int minn=1e6+5,index_minn=-1,skad=-1;
    
    //cout << index_minn << ' ' << skad << endl;
    for(int i=1;i<=stosy[wartosci[1]].size();++i){
        essa.push_back(i);
    }
    
    if(essa==stosy[wartosci[1]]){
        for(int i=2;i<=n;++i){
            if(wartosci[i]!=wartosci[1])
                wypisz.push_back({wartosci[i]+1,wartosci[1]+1});
        }
    }
    else{
        if(czy==false && wypisz.size()==0){
        for(int i=0;i<stosy.size();++i){

            if(stosy[i].size()!=0 && p1[stosy[i][0]-1]!=1e6+5){
                if(minn>stosy[i].size()){
                    minn=stosy[i].size();
                    index_minn=p1[stosy[i][0]-1];
                    skad=i;
                }
            }
        }
        }
        if(minn!=1e6+5){
            for(int i=0;i<stosy[skad].size();++i){
                wartosci[stosy[skad][i]]=index_minn;
                wypisz.push_back({skad+1,index_minn+1});
            }
            index=skad;
            czy=true;
        }
        if(!czy){
            cout << -1;
            return 0;
        }
        if(czy){
            int wielkosc=0;
            int cos = wartosci[1];
            while(essa[wielkosc]==stosy[cos][wielkosc]){
                wartosci[stosy[cos][wielkosc]]=index;
                wypisz.push_back({cos+1,index+1});
                wielkosc++;
            }
            for(int i=1;i<=n;++i){
                if(wartosci[i]!=index)
                    wypisz.push_back({wartosci[i]+1,index+1});
            }   
        }
        
    }
    cout << wypisz.size() << endl;
    for(int i=0;i<wypisz.size();++i){
        cout << wypisz[i].first << ' ' << wypisz[i].second << endl;
    }
    return 0;
}