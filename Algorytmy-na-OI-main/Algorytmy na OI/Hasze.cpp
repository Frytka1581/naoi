#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
using namespace std;
// potrójne haszownie
ll mod  = 998244353;
ll pod  = 257;
ll mod2 = 1000000007;
ll pod2 = 257;
ll mod3 = 1000000009;
ll pod3 = 137;
int n;
// cel haszodw i czyodw to hasz s³owa odwróconego na indeksach l, ..., r
vector<ll> czyt(vector<ll>& hasz, vector<ll>& potegi, vector<ll>& hasz2, vector<ll>& potegi2, vector<ll>& hasz3, vector<ll>& potegi3, ll a, ll b) {
    ll hash1 = (hasz[b] - (hasz[a] * potegi[b - a] % mod) + mod) % mod;
    ll hash2 = (hasz2[b] - (hasz2[a] * potegi2[b - a] % mod2) + mod2) % mod2;
    ll hash3 = (hasz3[b] - (hasz3[a] * potegi3[b - a] % mod3) + mod3) % mod3;
    return {hash1, hash2, hash3};
}
vector<ll> czytodw(vector<ll>& hasz, vector<ll>& potegi, vector<ll>& hasz2, vector<ll>& potegi2, vector<ll>& hasz3, vector<ll>& potegi3, ll a, ll b) {
    ll A = n - b;
    ll B = n - a;
    ll hash1 = (hasz[B] - (hasz[A] * potegi[B - A] % mod) + mod) % mod;
    ll hash2 = (hasz2[B] - (hasz2[A] * potegi2[B - A] % mod2) + mod2) % mod2;
    ll hash3 = (hasz3[B] - (hasz3[A] * potegi3[B - A] % mod3) + mod3) % mod3;
    return {hash1, hash2, hash3};
}
void stworz_hasz(string s,
                vector<ll>& hasz, vector<ll>& haszodw, vector<ll>& potegi
                vector<ll>& hasz2, vector<ll>& haszodw2, vector<ll>& potegi2
                vector<ll>& hasz3, vector<ll>& haszodw3, vector<ll>& potegi3) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        hasz.push_back((hasz.back() * pod + (s[i] - 'a' + 1)) % mod);
        haszodw.push_back((haszodw.back() * pod + (s[n - i - 1] - 'a' + 1)) % mod);
        potegi.push_back((potegi.back() * pod) % mod);

        hasz2.push_back((hasz2.back() * pod2 + (s[i] - 'a' + 1)) % mod2);
        haszodw2.push_back((haszodw2.back() * pod2 + (s[n - i - 1] - 'a' + 1)) % mod2);
        potegi2.push_back((potegi2.back() * pod2) % mod2);

        hasz3.push_back((hasz3.back() * pod3 + (s[i] - 'a' + 1)) % mod3);
        haszodw3.push_back((haszodw3.back() * pod3 + (s[n - i - 1] - 'a' + 1)) % mod3);
        potegi3.push_back((potegi3.back() * pod3) % mod3);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

