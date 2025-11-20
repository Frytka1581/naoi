#include <bits/stdc++.h>
using namespace std;
vector<pair<pair<int,int>,pair<int,int>>>trie(1,{{0,0},{0,0}});
void insert(int k){
    int index = 0;
    for(int bit=29;bit>=0;--bit){
        if(((1<<bit)&k)){
            trie[index].second.second++;
            if(trie[index].second.first == 0){
                trie[index].second.first = trie.size();
                index = trie.size();
                trie.push_back({{0,0},{0,0}});
            }
            else{
                index = trie[index].second.first;
            }
        }
        else{
            trie[index].first.second++;
            if(trie[index].first.first == 0){
                trie[index].first.first = trie.size();
                index = trie.size();
                trie.push_back({{0,0},{0,0}});
            }
            else{
                index = trie[index].first.first;
            }
        }
    }
    if((1&k)) trie[index].second.second++;
    else trie[index].first.second++;
    
}
void usun(int k){
    int index = 0;
    for(int bit=29;bit>=0;--bit){
        if(((1<<bit)&k)){
            trie[index].second.second--;
            if(trie[index].second.second == 0){
                trie[index].second.first = 0;
                break;
            }
            else{
                index = trie[index].second.first;
            }
        }
        else{
            trie[index].first.second--;
            if(trie[index].first.second == 0){
                trie[index].first.first = 0;
                break;
            }
            else{
                index = trie[index].first.first;
            }
        }
    }
    
}
int zwroc(int k){
    int wynik = k;
    int index = 0;
    for(int bit=29;bit>=0;--bit){
        if(((1<<bit)&k)){
            if(trie[index].second.second>0){
                wynik^=(1<<bit);
                index = trie[index].second.first;
            }
            else{
                //wynik^=(1<<bit);
                index = trie[index].first.first;
            }
        }
        else{
            if(trie[index].first.second>0){
                //wynik^=(1<<bit);
                index = trie[index].first.first;
            }
            else{
                wynik^=(1<<bit);
                index = trie[index].second.first;
            }
        }
    }
    return wynik;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,l,r,poprzedni;
    set<int>ciag;
    cin >> n;
    // for(int i=0;i<trie.size();++i){
    //     cout << trie[i].first.first << ' ' << trie[i].first.second << ' ' << trie[i].second.first << ' ' << trie[i].second.second << endl;
    // }
    for(int i=0;i<n;++i){
        cin >> l >> r;
        if(l==0){ 
            poprzedni = ciag.size();
            ciag.insert(r);
            if(poprzedni!=ciag.size()) insert(r);
        }
        else if(l==1) {
            poprzedni = ciag.size();
            ciag.erase(r);
            if(poprzedni!=ciag.size()) usun(r);
        }
        else{
            cout << zwroc(r) << endl;
        }
        
    }
    return 0;
}