#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const ll INF_DUZE = 1e18;

struct Linia {
    ll a, b;
    int id;

    bool operator<(const Linia& o) const {
        if (a != o.a) return a < o.a;
        return b < o.b;
    }
};

bool zla(const Linia& l1, const Linia& l2, const Linia& l3) {
    long double lewa = (long double)(l3.b - l2.b) * (long double)(l2.a - l1.a);
    long double prawa = (long double)(l2.b - l1.b) * (long double)(l3.a - l2.a);
    return lewa >= prawa;
}

void rozwiaz() {
    int n;
    ll dystans_koncowy, maks_przeskok;
    cin >> n >> dystans_koncowy >> maks_przeskok;

    vector<pair<ll,ll>> stacje(n);
    for (int i = 0; i < n; i++) cin >> stacje[i].first >> stacje[i].second;

    sort(stacje.begin(), stacje.end());

    int N = n + 2;
    vector<ll> polozenie(N), koszt(N), dp(N, 2 * INF_DUZE);

    polozenie[0] = 0;
    koszt[0] = 0;

    for (int i = 0; i < n; i++) {
        polozenie[i+1] = stacje[i].first;
        koszt[i+1] = stacje[i].second;
    }

    polozenie[n+1] = dystans_koncowy;
    koszt[n+1] = 0;

    for (int i = 1; i < N; i++) {
        if (polozenie[i] - polozenie[i-1] > maks_przeskok) {
            cout << -1 << "\n";
            return;
        }
    }

    dp[0] = 0;

    set<Linia> kadlub;
    vector<set<Linia>::iterator> gdzie(N);

    ll a = koszt[0];
    ll b = dp[0] - a * polozenie[0];
    Linia start = {a, b, 0};
    gdzie[0] = kadlub.insert(start).first;

    auto najlepsza = kadlub.end();
    najlepsza--;

    int lewy = 0;

    for (int i = 1; i < N; i++) {
        while (polozenie[i] - polozenie[lewy] > maks_przeskok) {
            if (najlepsza == gdzie[lewy]) najlepsza = kadlub.end();
            kadlub.erase(gdzie[lewy]);
            lewy++;
        }

        if (kadlub.empty()) {
            dp[i] = 2 * INF_DUZE;
        } else {
            if (najlepsza == kadlub.end()) {
                najlepsza = kadlub.end();
                najlepsza--;
            }

            while (najlepsza != kadlub.begin()) {
                auto pop = najlepsza; 
                pop--;

                long double v1 = (long double)pop->a * polozenie[i] + pop->b;
                long double v2 = (long double)najlepsza->a * polozenie[i] + najlepsza->b;

                if (v1 < v2) najlepsza = pop;
                else break;
            }

            long double wyn = (long double)najlepsza->a * polozenie[i] + najlepsza->b;
            dp[i] = (ll)wyn;
        }

        if (i < N - 1) {
            a = koszt[i];
            b = dp[i] - a * polozenie[i];
            Linia nowa = {a, b, i};

            bool dodaj = true;

            auto it = kadlub.lower_bound({a, -2 * INF_DUZE, -1});
            if (it != kadlub.end() && it->a == a) {
                if (it->b <= b) dodaj = false;
                else {
                    if (najlepsza == it) najlepsza = kadlub.end();
                    kadlub.erase(it);
                }
            }

            if (dodaj) {
                auto wstaw = kadlub.insert(nowa).first;
                gdzie[i] = wstaw;

                while (wstaw != kadlub.begin() && prev(wstaw) != kadlub.begin()) {
                    auto p = prev(wstaw);
                    auto pp = prev(p);
                    if (zla(*pp, *p, *wstaw)) {
                        if (najlepsza == p) najlepsza = kadlub.end();
                        kadlub.erase(p);
                    } else break;
                }

                while (next(wstaw) != kadlub.end() && next(next(wstaw)) != kadlub.end()) {
                    auto n1 = next(wstaw);
                    auto n2 = next(n1);
                    if (zla(*wstaw, *n1, *n2)) {
                        if (najlepsza == n1) najlepsza = kadlub.end();
                        kadlub.erase(n1);
                    } else break;
                }
            }
        }
    }

    ll wynik = dp[N-1];
    if (wynik >= INF_DUZE) wynik = -1;
    cout << wynik << "\n";
}

int main() {
    fastio;
    rozwiaz();
    return 0;
}
