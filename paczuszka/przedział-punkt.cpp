#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(),a.end()
#define rep(a,b) for(ll a = 0;a<b;a++)
const ll inf = 1e9;
const ll infl = 1e18;

const ll ize = 1000000;
ll tr[ize*2 ];

//numeracja leafs do 1

void add(ll l,ll r, ll v)
{
    l+=ize;
    r+=ize;
    tr[l] += v;
    if(l != r) tr[r] += v;
    while(l/2 != r/2)
    {
        if(l%2==0) tr[l+1] += v;
        if(r%2==1) tr[r-1] += v;
        l/=2;r/=2;
    }
}


ll check(ll p)
{
    p+=ize;
    ll ans = 0;
    ans += tr[p];
    p/=2;
    while(p > 0)
    {
        ans += tr[p];
        p/=2;
    }
    return ans;
}

ll main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll n, q;
    string lampy;

    cin >> n >> q;
    cin >> lampy;

    for(ll i = 0; i < n; i++){
        if(lampy[i] == 'x'){
            add(i+1, i+1, 1);
        }
    }

    

    for(ll i = 0; i < q; i++){
        char a;
        ll b, c;
        cin >> a;
        if(a == 'Q'){
            cin >> b;
            if(check(b) == 0){
                cout << "ON" << "\n";
            }
            else{
                cout << "OFF" << "\n";
            }
        }
        else{
            cin >> b >> c;
            add(b, c, 1);
        }

    }
}


