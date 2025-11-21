#include <bits/stdc++.h>
using namespace std;

vector<int> ciag(26);
vector<vector<int>> trie(1, ciag);
vector<int> glebokosci;
void dodaj(string napis, int index)
{
    for (int i = 0; i < napis.size(); ++i)
    {
        int c = napis[i] - 'a';
        //cout << c << endl;
        if (trie[index][c] == 0 || trie[index][c] == -1)
        {
            trie.push_back(ciag);
            trie[index][c] = trie.size() - 1;
            index = trie.size() - 1;
        }
        else
            index = trie[index][c];
    }
    trie[index][napis[napis.size()-1]-'a']=-1;
}
int odczytaj(string napis,int index,int suma,int i){
    if(trie[index][napis[i]-'a']==0) return suma;
    else if(trie[index][napis[i]]==-1) return suma+1;
    else return odczytaj(napis,trie[index][napis[i]-'a'],suma+1,i+1);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string k;
    vector<string> ciag;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> k;
        cout << odczytaj(k,0,0,0) << endl;
        dodaj(k, 0);
        ciag.push_back(k);
    }
    glebokosci.resize(trie.size());
    for(int i=trie.size()-1;i>0;--i){
        for(int j=0;j<trie[i].size();++j){
            if(trie[i][j]!=0 && trie[i][j]!=-1) glebokosci[i]=max(glebokosci[i],glebokosci[trie[i][j]]+1);
        }
    }
    
    for(int i=1;i<glebokosci.size();++i){
        cout << glebokosci[i] << ' ';
    }
    return 0;
}