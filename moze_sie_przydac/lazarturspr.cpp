#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <numeric> 
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
#define ff first
#define ss second
#define MOD 998244353LL
#define INF 1000000001LL
#define POT (1LL<<20)
#define INFL 1000000000000000099LL
#define pii pair<ll,ll>
#define ppi pair<pii,ll>
#define pip pair<ll,pii>
#define ppp pair<pii,pii>
#define vi vector<ll>
#define vii vector<pii>
#define vvi vector<vi>
#define al(x) x.begin(),x.end()
#define rev(x) reverse(al(x))
template<typename T, typename U>
pair<T, U> operator+(const pair<T, U>& a, const pair<T, U>& b) {
    return {a.first + b.first, a.second + b.second};
}
template<typename T, typename U>
pair<T, U> operator-(const pair<T, U>& a, const pair<T, U>& b) {
    return {a.first - b.first, a.second - b.second};
}
template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    os<<"{"<<p.ff<<", "<<p.ss<<"}";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "{";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) os << ", ";
        os << v[i];
    }
    os << "}";
    return os;
}
ll fct[1000007];
ll fp(ll a,ll b){
    ll c=1;while(b){if(b&1)c=(c*a)%MOD;a=(a*a)%MOD;b/=2;}
    return c;
}
ll iv(ll a){
    return fp(a,MOD-2);
}
ll bnm(ll a,ll b){
    if(b>a || a<0)return 0;
    return ((fct[a]*iv(fct[b]))%MOD*iv(fct[a-b]))%MOD;
}
ll dx,dy;
ll n,m;
void wa(ll a,ll b){
    //cout<<a<<" "<<b;
    if(dx<0)a=m+1-a;
    if(dy<0)b=n+1-b;
    b=(b+n-2)%n+1;
    //cout<<"I nie odwiedzasz pola "<<a<<" "<<b<<" startując z 1, "<<n<<" (tak jak w wizualizatorze, lewy dolny rog to 1,1)";
    //exit(0);
}
ll iv2(ll a,ll b){
    ll l=1,r=0;
    ll m=b;
    while(b!=0 && a!=0){
        if(a>b){
            ll x=a/b;
            l=(INF*m+l-r*x)%m;
            a%=b;
        }
        else{
            ll x=b/a;
            r=(INF*m+r-l*x)%m;
            b%=a;
        }
    }
    if(a)
    return l;
    return r;
}
ll nww(ll a,ll b){
    return a*b/gcd(a,b);
}
void jud(string s,ll N,ll M){
    n=N;
    m=M;
    
    ll dfx=0,dfy=0;
    for(auto i : s){
        if(i=='D')dfy--;
        else if(i=='G')dfy++;
        else if(i=='L')dfx--;
        else dfx++;
    }
    dx=dfx;
    dy=dfy;
    dfx=abs(dfx);
    if(dfx)
    dx/=dfx;
    else dx=1;
    dfy=abs(dfy);
    if(dfy)
    dy/=dfy;
    else dy=1;
    ll pw=iv2(dfx,m);

    ll sf=(dfy*pw)%n;
    ll h=gcd((m*dfy/gcd(m,dfx)),n);
    ll w=gcd(dfx,m);
    ll x=0;
    ll y=0;
    bool dw[h][w];
    sf=(n-sf)%h;
    for(ll i=0;i<h;i++){
        for(ll j=0;j<w;j++)dw[i][j]=0;
    }
    for(auto i : s){
        if(i=='D'){
            y-=dy;
        }
        else if(i=='G'){
            y+=dy;
        }
        else if(i=='L'){
            x-=dx;
        }
        else x+=dx;
        y+=h;
        y%=h;
        if(x==-1){
            y=(y+h-sf)%h;
            x+=w;
        }
        if(x==w){
            x=0;
            y=(y+sf)%h;
        }
        dw[y][x]=1;
    }
    for(ll i=0;i<h;i++){
        for(ll j=0;j<w;j++)
            if(dw[i][j]==0)
                {wa(j+1,i+1);return;}
    }
    cout<<"C";
    ll opt=max(2LL,gcd(n,m));
    ll score=floor(100/sqrtl(1+s.size()-opt));
    cout<<" score: "<<score<<"% " << s << endl;
}

int main() {
    mt19937 mt(2);
    string s;
    int n,m;
    cin >> n >> m;

    const int LEN = 16;           // długość kombinacji
    const string LETTERS = "DPGL"; // litery do wyboru

    unsigned long long total = 1ULL << (2*LEN); // 4^LEN

    for (unsigned long long x = 0; x < total; ++x) {
        unsigned long long num = x;
        string napis(LEN, ' ');

        // generowanie kombinacji w systemie 4-arym
        for (int i = LEN-1; i >= 0; --i) {
            napis[i] = LETTERS[num % 4];
            num /= 4;
        }
        //cout << napis << endl;
        jud(napis, n, m); // testowanie kombinacji
        //cout << napis << endl;
    }

    return 0;
}
