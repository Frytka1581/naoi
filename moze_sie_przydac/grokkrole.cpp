#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

int n, m, R, C;
vector<vector<int>> start_plansza, cel_plansza, plansza;
map<int,set<pii>> pozycje_start, pozycje_cel;
vector<tuple<int,int,int>> ruchy;

int dr[8] = {-1,-1,-1,0,0,1,1,1};
int dc[8] = {-1,0,1,-1,1,-1,0,1};

vector<vector<int>> wczytaj_plansze() {
    vector<vector<int>> p(R);
    string linia;
    for(int i=0;i<R;i++){
        getline(cin, linia);
        stringstream ss(linia);
        int v;
        while(ss>>v) p[i].push_back(v);
    }
    return p;
}

bool poprawne_rozmiary(vector<vector<int>> &p) {
    if(p.empty() || p[0].empty()) return false;
    for(auto &r:p) if((int)r.size()!=C) return false;
    return true;
}

bool poprawna_plansza(vector<vector<int>> &p) {
    for(int r=0;r<R;r++)
        for(int c=0;c<C;c++)
            if(p[r][c]>0)
                for(int d=0;d<8;d++){
                    int nr=r+dr[d], nc=c+dc[d];
                    if(nr>=0&&nr<R&&nc>=0&&nc<C&&p[nr][nc]>0)
                        return false;
                }
    return true;
}

vector<pii> znajdz_sciezke(pii s, pii t, const vector<vector<char>> &blok) {
    if(s==t) return {};
    vector<vector<char>> vis(R, vector<char>(C,0));
    vector<vector<pii>> prev(R, vector<pii>(C,{-1,-1}));
    queue<pii> q;
    q.push(s);
    vis[s.first][s.second]=1;
    bool ok=false;

    while(!q.empty()&&!ok){
        auto [r,c]=q.front(); q.pop();
        for(int d=0;d<8;d++){
            int nr=r+dr[d], nc=c+dc[d];
            if(nr>=0&&nr<R&&nc>=0&&nc<C&&!vis[nr][nc]&&plansza[nr][nc]==0&&!blok[nr][nc]){
                vis[nr][nc]=1;
                prev[nr][nc]={r,c};
                q.push({nr,nc});
                if(pii(nr,nc)==t){ ok=true; break; }
            }
        }
    }
    if(!ok) return {};
    vector<pii> sc;
    pii p=t;
    while(p!=s){
        sc.push_back(p);
        p=prev[p.first][p.second];
    }
    reverse(sc.begin(), sc.end());
    return sc;
}

bool te_same_etykiety() {
    map<int,int> a,b;
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++){
            a[start_plansza[i][j]]++;
            b[cel_plansza[i][j]]++;
        }
    return a==b;
}

bool zrob_blokade(vector<vector<char>> &blok, pii pom, int v) {
    for(int r=0;r<R;r++)
        for(int c=0;c<C;c++)
            if(plansza[r][c]>0 && !(r==pom.first && c==pom.second))
                for(int dr2=-1;dr2<=1;dr2++)
                    for(int dc2=-1;dc2<=1;dc2++){
                        int nr=r+dr2,nc=c+dc2;
                        if(nr>=0&&nr<R&&nc>=0&&nc<C)
                            blok[nr][nc]=1;
                    }
    return true;
}

bool wszystko_ok() {
    for(auto &p:pozycje_cel)
        if(pozycje_start[p.first]!=p.second)
            return false;
    return true;
}

void wykonaj_ruch(int v, vector<pii> sciezka) {
    pii cur = *pozycje_start[v].begin();
    for(auto next : sciezka){
        plansza[cur.first][cur.second]=0;
        plansza[next.first][next.second]=v;
        pozycje_start[v].erase(cur);
        pozycje_start[v].insert(next);
        ruchy.push_back({v,next.first+1,next.second+1});
        cur=next;
    }
}

bool znajdz_i_rusz() {
    for(auto &p:pozycje_cel){
        int v=p.first;
        auto &cel=p.second;
        auto &obecne=pozycje_start[v];
        if(cel==obecne) continue;

        for(auto t:cel){
            if(plansza[t.first][t.second]!=0) continue;
            for(auto s:obecne){
                if(cel.count(s)) continue;
                vector<vector<char>> blok(R,vector<char>(C,0));
                zrob_blokade(blok,s,v);
                if(blok[t.first][t.second]) continue;
                auto sc=znajdz_sciezke(s,t,blok);
                if(!sc.empty()||s==t){
                    wykonaj_ruch(v,sc);
                    return true;
                }
            }
        }
    }
    return false;
}

bool przenies_na_puste() {
    pii skad={-1,-1};
    int v=-1;
    for(auto &p:pozycje_cel){
        auto &cel=p.second;
        for(auto s:pozycje_start[p.first])
            if(!cel.count(s)){
                skad=s; v=p.first; break;
            }
        if(v!=-1) break;
    }
    if(v==-1) return false;

    vector<vector<char>> blok(R,vector<char>(C,0));
    zrob_blokade(blok,skad,v);

    pii dokad={-1,-1};
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            if(plansza[i][j]==0 && cel_plansza[i][j]==0 && !blok[i][j])
                dokad={i,j};

    if(dokad.first==-1)
        for(int i=0;i<R;i++)
            for(int j=0;j<C;j++)
                if(plansza[i][j]==0 && !blok[i][j])
                    dokad={i,j};

    if(dokad.first==-1) return false;
    auto sc=znajdz_sciezke(skad,dokad,blok);
    if(sc.empty() && skad!=dokad) return false;
    wykonaj_ruch(v,sc);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>m;
    string linia; getline(cin,linia);
    R=n; C=n;

    start_plansza = wczytaj_plansze();
    cel_plansza = wczytaj_plansze();
    if(!poprawne_rozmiary(start_plansza)||!poprawne_rozmiary(cel_plansza)){
        cout<<"NIE\n"; return 0;
    }
    if(!poprawna_plansza(start_plansza)||!poprawna_plansza(cel_plansza)){
        cout<<"NIE\n"; return 0;
    }
    if(!te_same_etykiety()){
        cout<<"NIE\n"; return 0;
    }

    plansza=start_plansza;
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++){
            int v=plansza[i][j];
            if(v>0) pozycje_start[v].insert({i,j});
            v=cel_plansza[i][j];
            if(v>0) pozycje_cel[v].insert({i,j});
        }

    while(true){
        if(wszystko_ok()) break;
        if(znajdz_i_rusz()) continue;
        if(!przenies_na_puste()){
            cout<<"NIE\n"; return 0;
        }
    }

    cout<<"TAK\n";
    cout<<ruchy.size()<<"\n";
    for(auto [v,r,c]:ruchy)
        cout<<v<<" "<<r<<" "<<c<<"\n";
}
