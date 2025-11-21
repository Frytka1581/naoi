#include <bits/stdc++.h>

using namespace std;
int n, k;
vector<vector<int>> plansza;
vector<vector<int>> plansza_docelowa;
map<int, pair<int, int>> pozycje;
map<int, pair<int, int>> pozycje_docelowe;
pair<int,int>puste_pole;
vector<tuple<int, int, int>> ruchy;
pair<int,int>znajdz_puste(){
    for(int i=0;i<n/2*2;i+=2){
        for(int j=0;j<n/2*2;j+=2){
            if(plansza[i][j]==0 && plansza[i][j+1]==0 && plansza[i+1][j]==0 && plansza[i+1][j+1]==0 ) return {i,j};
        }
    }
    return {-1,-1};
}
bool czy_wolne_gora(int k){
    if(pozycje[k].first > 1){
        if(pozycje[k].second > 0){
            if(plansza[pozycje[k].first-2][pozycje[k].second-1]!=0) return false;
        }
        if(plansza[pozycje[k].first-2][pozycje[k].second]!=0) return false;
        if(pozycje[k].second < n-1){
            if(plansza[pozycje[k].first-2][pozycje[k].second+1]!=0) return false;
        }
        return true;
    }
    if(pozycje[k].first==1) return true;
    return false;
}
bool czy_wolne_lewo(int k){
    if(pozycje[k].second > 1){
        if(pozycje[k].first > 0){
            if(plansza[pozycje[k].first-1][pozycje[k].second-2]!=0) return false;
        }
        if(plansza[pozycje[k].first][pozycje[k].second-2]!=0) return false;
        if(pozycje[k].first < n-1){
            if(plansza[pozycje[k].first+1][pozycje[k].second-2]!=0) return false;
        }
        return true;
    }
    if(pozycje[k].second==1) return true;
    return false;
}
// l1 p1 to nie pusty 
void zamien(int l1, int p1,int l2,int p2, int k){
    if(l1-2 == l2 && p1-2 == p2){
        plansza[l1][p1]=0;
        plansza[l1-2][p1-2]=k;
        pozycje[k]={l1-2,p1-2};
        ruchy.push_back({k,l1-1,p1-1});
        ruchy.push_back({k,l1-2,p1-2});
        puste_pole.first+=2;
        puste_pole.second+=2;
    }
    if(l1 == l2 && p1-2 == p2){
        plansza[l1][p1]=0;
        plansza[l1][p1-2]=k;
        pozycje[k]={l1,p1-2};
        ruchy.push_back({k,l1,p1-1});
        ruchy.push_back({k,l1,p1-2});
        //puste_pole.first+=2;
        puste_pole.second+=2;
    }
    if(l1+2 == l2 && p1-2 == p2){
        plansza[l1][p1]=0;
        plansza[l1+2][p1-2]=k;
        pozycje[k]={l1+2,p1-2};
        ruchy.push_back({k,l1+1,p1-1});
        ruchy.push_back({k,l1+2,p1-2});
        puste_pole.first-=2;
        puste_pole.second+=2;
    }
    if(l1-2 == l2 && p1 == p2){
        plansza[l1][p1]=0;
        plansza[l1-2][p1]=k;
        pozycje[k]={l1-2,p1};
        ruchy.push_back({k,l1-1,p1});
        ruchy.push_back({k,l1-2,p1});
        puste_pole.first+=2;
        //puste_pole.second+=2;
    }
    if(l1+2 == l2 && p1 == p2){
        //cout << 123 << endl;
        plansza[l1][p1]=0;
        plansza[l1+2][p1]=k;
        pozycje[k]={l1+2,p1};
        ruchy.push_back({k,l1+1,p1});
        ruchy.push_back({k,l1+2,p1});
        puste_pole.first-=2;
        //puste_pole.second+=2;
    }
    if(l1-2 == l2 && p1+2 == p2){
        plansza[l1][p1]=0;
        plansza[l1-2][p1+2]=k;
        pozycje[k]={l1-2,p1+2};
        ruchy.push_back({k,l1-1,p1+1});
        ruchy.push_back({k,l1-2,p1+2});
        puste_pole.first+=2;
        puste_pole.second-=2;
    }
    if(l1 == l2 && p1+2 == p2){
        //cout << 123 << endl;
        plansza[l1][p1]=0;
        plansza[l1][p1+2]=k;
        pozycje[k]={l1,p1+2};
        ruchy.push_back({k,l1,p1+1});
        ruchy.push_back({k,l1,p1+2});
        //puste_pole.first+=2;
        puste_pole.second-=2;
    }
    if(l1+2 == l2 && p1+2 == p2){
        plansza[l1][p1]=0;
        plansza[l1+2][p1+2]=k;
        pozycje[k]={l1+2,p1+2};
        ruchy.push_back({k,l1+1,p1+1});
        ruchy.push_back({k,l1+2,p1+2});
        puste_pole.first-=2;
        puste_pole.second-=2;
    }
}
vector<pair<int,int>>generuj_droge(pair<int,int> poczatek, pair<int,int> cel){
    vector<pair<int,int>>trasa;
    pair<int,int>kolejny_cel = poczatek;
    if(poczatek.first<=cel.first && poczatek.second <=cel.second){
        while(cel.first-poczatek.first!=cel.second-poczatek.second){
            if(cel.first-poczatek.first > cel.second-poczatek.second)
                poczatek.first+=2;
            else
                poczatek.second+=2;
            trasa.push_back({poczatek.first,poczatek.second});
        }
        while(poczatek.first<cel.first && poczatek.second < cel.second){
            poczatek.first+=2; poczatek.second+=2;
            trasa.push_back({poczatek.first,poczatek.second});

        }
        while(poczatek.first-kolejny_cel.first!=poczatek.second-kolejny_cel.second){
            if(poczatek.first-kolejny_cel.first > poczatek.second-kolejny_cel.second)
                poczatek.first-=2;
            else
                poczatek.second-=2;
            trasa.push_back({poczatek.first,poczatek.second});
        }
        while(poczatek.first>kolejny_cel.first && poczatek.second > kolejny_cel.second){
            poczatek.first-=2; poczatek.second-=2;
            trasa.push_back({poczatek.first,poczatek.second});

        }
    }
    return trasa;
}
int main() {

    cin >> n >> k;
    plansza.resize(n, vector<int>(n));
    plansza_docelowa.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> plansza[i][j];
            if (plansza[i][j] > 0) {
                pozycje[plansza[i][j]] = {i, j};
            }
        }
    }
    for(int i=1;i<=k;++i){
        while(czy_wolne_gora(i)){
            //cout << czy_wolne_gora(i) << ' ' << i << endl;
            plansza[pozycje[i].first][pozycje[i].second]=0;
            pozycje[i].first--;
            plansza[pozycje[i].first][pozycje[i].second]=i;
            ruchy.push_back({i,pozycje[i].first+1,pozycje[i].second+1});
        }
    }
    for(int i=1;i<=k;++i){
        while(czy_wolne_lewo(i)){
            //cout << czy_wolne_gora(i) << ' ' << i << endl;
            plansza[pozycje[i].first][pozycje[i].second]=0;
            pozycje[i].second--;
            plansza[pozycje[i].first][pozycje[i].second]=i;
            ruchy.push_back({i,pozycje[i].first+1,pozycje[i].second+1});
        }
    }
    puste_pole = znajdz_puste();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> plansza_docelowa[i][j];
            if (plansza_docelowa[i][j] > 0) {
                pozycje_docelowe[plansza_docelowa[i][j]] = {i, j};
            }
        }
    }
    if(puste_pole.first==-1) cout << "NIE";
    else cout << "TAK";
    // stack<int>klocki;
    // for(int i=0;i<n;++i){
    //     for(int j=0;j<n;++j){
    //         if(plansza_docelowa[i][j]>0) klocki.push(plansza_docelowa[i][j]);
    //     }
    // }
    
    // while(!klocki.empty()){
    //     cout << klocki.top() << endl;
    //     klocki.pop();
    // }
    //cout << czy_wolne_gora(3) << endl;
    // cout << "Generowanie drogi: " << endl;
    // vector<pair<int,int>>droga = generuj_droge({0,0},{0,8});
    // for(int i=0;i<droga.size();++i){
    //     cout << droga[i].first << ' ' << droga[i].second << endl;
    // }
    // cout << "----------------" << endl;
    // cout << "Puste pola: " << endl;
    // cout << puste_pole.first << ' ' << puste_pole.second << endl;
    // zamien(0,2,puste_pole.first,puste_pole.second,2);
    // cout << puste_pole.first << ' ' << puste_pole.second << endl;
    // cout << "----------------" << endl;
    // cout << "Ruchy: ";
    // cout << ruchy.size() << endl;
    // for (auto [klocek, i, j] : ruchy) {
    //     cout << klocek << " " << i << " " << j << endl;
    // }

    // for (int i = 0; i < plansza.size(); ++i) {
    //     for (int j = 0; j < plansza[i].size(); ++j) {
    //         cout << plansza[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // cout << "Docelowe pozycje klockow:" << endl;
    // for (int i = 1; i <= k; i++) {
    //     auto [i_pos, j_pos] = pozycje_docelowe[i];
    //     cout << "Klocek " << i << ": (" << i_pos + 1 << ", " << j_pos + 1 << ")" << endl;
    // }

    

    return 0;
}